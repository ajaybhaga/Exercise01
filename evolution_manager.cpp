//
// C++ Implementation by Ajay Bhaga
//
// Modified Genetic Algorithm
// Based on design of Samuel Arzt (March 2017)
//

#include "evolution_manager.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include <filesystem>
#include <functional>
#include <string>
#include <map>

#include <chrono> // std::chrono::microseconds
#include <thread> // std::this_thread::sleep_for

#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>

namespace fs = std::__fs::filesystem;

bool directoryExists(const char *dname){
    DIR *di = opendir(dname); // open the directory
    if(di) return true; // can open=>return true
    else return false; // otherwise return false
    closedir(di);
}

EvolutionManager::EvolutionManager() {
}

EvolutionManager::~EvolutionManager() {

    for (auto it = agents.begin(); it != agents.end(); ++it) {
        delete &it;
    }
}


EvolutionManager *EvolutionManager::getInstance() {

    if (instance == 0) {
        instance = new EvolutionManager();
        // Initialize
        getInstance()->statisticsFileName = "stats.txt";

    }
    return instance;
}

// The age of the current generation.
int EvolutionManager::getGenerationCount() {
    return 0;
}

void EvolutionManager::evalFinished() {
    EvolutionManager::getInstance()->getGeneticAlgorithm()->evaluationFinished();
}

void EvolutionManager::startEvolution() {

    // Create neural network to determine parameter count
   // NeuralNetwork nn = new NeuralNetwork(FFNTopology);

    // Setup genetic algorithm
    // nn.WeightCount
    geneticAlgorithm = new GeneticAlgorithm(0, populationSize);
    genotypesSaved = 0;

    geneticAlgorithm->evaluation = startEvaluation;

    if (elitistSelection) {

        // Second configuration
        geneticAlgorithm->selection = geneticAlgorithm->defaultSelectionOperator;
        geneticAlgorithm->recombination = randomRecombination;
        geneticAlgorithm->mutation = mutateAllButBestTwo;

    } else {

        // First configuration
        geneticAlgorithm->selection = remainderStochasticSampling;
        geneticAlgorithm->recombination = randomRecombination;
        geneticAlgorithm->mutation = mutateAllButBestTwo;
    }

    allAgentsDied += evalFinished;

    char buffer[80];
    time_t rawtime;
    struct tm *timeinfo;
    time (&rawtime);
    timeinfo = localtime(&rawtime);

    // Statistics
    if (saveStatistics) {
        strftime(buffer,sizeof(buffer),"%d-%m-%Y %H:%M:%S",timeinfo);
        std::string str(buffer);
        getInstance()->statisticsFileName = std::string("Evaluation - ") + buffer;
        writeStatisticsFileStart();
        geneticAlgorithm->fitnessCalculationFinished += writeStatisticsToFile;
    }

    geneticAlgorithm->fitnessCalculationFinished += checkForTrackFinished;

    //Restart logic
    if (restartAfter > 0) {

        geneticAlgorithm->terminationCriterion += checkGenerationTermination;
        geneticAlgorithm->algorithmTerminated += onGATermination;

    }

    geneticAlgorithm->start();
}


void EvolutionManager::writeStatisticsFileStart() {
    std::string dirPath = TRAINING_DATA_DIR;
    std::string fullPath = dirPath + getInstance()->statisticsFileName;

    std::string outText;
    std::string trackName = "default";

    getInstance()->statisticsFile.open(fullPath);
    if (getInstance()->statisticsFile.is_open())
    {
        outText += "Evaluation of a population with size: ";
        outText += getInstance()->populationSize;
        outText += ", on Track " + trackName + ".\n";
        getInstance()->statisticsFile << outText;
        getInstance()->statisticsFile.close();
    }
}

void EvolutionManager::writeStatisticsToFile() {

    std::string outText;

    std::list<Genotype> currentPopulation = getInstance()->getGeneticAlgorithm()->getCurrentPopulation();
    for (std::list<Genotype>::iterator it = currentPopulation.begin(); it != currentPopulation.end(); ++it) {
        outText += "Generation Count -> ";
        outText += getInstance()->getGeneticAlgorithm()->generationCount;
        outText += "\n";
        outText += "Genotype Evaluation: ";
        outText += it->evaluation;
        outText += "\n";
    }
}

// Checks the current population and saves genotypes to a file if their evaluation is greater than or equal to 1.
void EvolutionManager::checkForTrackFinished() {

    if (getInstance()->genotypesSaved >= getInstance()->saveFirstNGenotype) return;

    std::string saveFolder = getInstance()->statisticsFileName + "/";
    std::list<Genotype> currentPopulation = getInstance()->getGeneticAlgorithm()->getCurrentPopulation();

    for (std::list<Genotype>::iterator it = currentPopulation.begin(); it != currentPopulation.end(); ++it) {

        if (it->evaluation >= 1) {

            // Check if directory exist
            if (directoryExists(saveFolder.data())) {

                // Create directory
                const int dir_err = mkdir(saveFolder.data(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
                if (-1 == dir_err)
                {
                    printf("Error creating directory!n");
                    exit(1);
                }

                std::string a = saveFolder;
                a += "Genotype - Finished as ";
                a += (++(getInstance()->genotypesSaved));
                a += ".txt";
                it->saveToFile(a.data());

//                std::ofstream("sandbox/file"); // create regular file

                if (getInstance()->genotypesSaved >= getInstance()->saveFirstNGenotype) return;
            }
        } else
            return; // List should be sorted, so we can exit here.
    }
}

bool EvolutionManager::checkGenerationTermination() {
    return getInstance()->getGenerationCount() >= getInstance()->restartAfter;
}

void EvolutionManager::onGATermination() {

    getInstance()->allAgentsDied -= evalFinished;
    getInstance()->restartAlgorithm(5.0f);
}

// Restart the algorithm after a specific wait time
void EvolutionManager::restartAlgorithm(float wait) {

    // ignore wait, use 2 seconds for now
    using namespace std::chrono_literals;
    std::cout << "Hello waiter\n" << std::flush;
    auto start = std::chrono::high_resolution_clock::now();
    std::this_thread::sleep_for(2s);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> elapsed = end-start;
    std::cout << "Waited " << elapsed.count() << " ms\n";

    startEvolution();
}

// Starts the evaluation by first creating new agents from the current population and then restarting the track manager.
 void EvolutionManager::startEvaluation(std::list<Genotype> currentPopulation) {

    // Create new agents from currentPopulation
    getInstance()->agents.clear();
    getInstance()->agentsAliveCount = 0;

    for (auto it = currentPopulation.begin(); it != currentPopulation.end(); ++it) {
        getInstance()->agents.emplace_back(new Agent(*it, MathHelper::softSignFunction, getInstance()->ffnTopology));
    }

    // TrackManager.Instance.setCarAmount(agents.Count);
    // TODO: Retrieve agent controllers from track manager (this is where we tie into world actions).
    for (auto it = getInstance()->agents.begin(); it != getInstance()->agents.end(); ++it) {

        // Iterate through agent controller, update agent reference



    }


}

void EvolutionManager::onAgentDied(Agent agent) {

}

void EvolutionManager::mutateAllButBestTwo(std::list<Genotype> newPopulation) {

}

void EvolutionManager::mutateAll(std::list<Genotype> newPopulation) {

}

std::list<Genotype> *EvolutionManager::randomRecombination(std::list<Genotype> intermediatePopulation, int newPopulationSize) {
    return nullptr;
}

std::list<Genotype> *EvolutionManager::remainderStochasticSampling(std::list<Genotype> currentPopulation) {
    return nullptr;
}

GeneticAlgorithm *EvolutionManager::getGeneticAlgorithm() {
    return this->geneticAlgorithm;
}
