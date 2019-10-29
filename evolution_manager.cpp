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
#include <dirent.h>

namespace fs = std::__fs::filesystem;


bool directoryExists(const char *dname){
    DIR *di = opendir(dname); // open the directory
    if(di) return true; // can open=>return true
    else return false; // otherwise return false
    closedir(di);
}

EvolutionManager::EvolutionManager() {
    std::list<Agent> *agents = new std::list<Agent>();
}

EvolutionManager::~EvolutionManager() {
    delete[] agents;
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

            if (directoryExists(saveFolder.data())) {
                fs::create_directory(saveFolder.data());
//                std::ofstream("sandbox/file"); // create regular file
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

void EvolutionManager::restartAlgorithm(float wait) {
    std::invoke(startEvolution, 2);
}

 void EvolutionManager::startEvaluation(std::list<Genotype> currentPopulation) {
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
