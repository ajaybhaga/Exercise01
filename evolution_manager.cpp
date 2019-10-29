//
// C++ Implementation by Ajay Bhaga
//
// Modified Genetic Algorithm
// Based on design of Samuel Arzt (March 2017)
//

#include "evolution_manager.h"
#include <iostream>
#include <ctime>

EvolutionManager::EvolutionManager() {
    std::list<Agent> *agents = new std::list<Agent>();
}

EvolutionManager::~EvolutionManager() {
    delete[] agents;
}


EvolutionManager *EvolutionManager::getInstance() {

    if (instance == 0) {
        instance = new EvolutionManager();
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
        statisticsFileName = std::string("Evaluation - ") + buffer;
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

}

void EvolutionManager::writeStatisticsToFile() {

}

void EvolutionManager::checkForTrackFinished() {

}

void EvolutionManager::checkGenerationTermination() {

}

void EvolutionManager::onGATermination() {

}

void EvolutionManager::restartAlgorithm(float wait) {

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
