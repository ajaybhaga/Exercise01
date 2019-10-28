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
    instance = 0;
}

EvolutionManager::~EvolutionManager() {
    delete[] agents;
}

// The age of the current generation.
int EvolutionManager::getGenerationCount() {
    return 0;
}

void EvolutionManager::startEvolution() {

    // Create neural network to determine parameter count
   // NeuralNetwork nn = new NeuralNetwork(FFNTopology);

    // Setup genetic algorithm
    // nn.WeightCount
    geneticAlgorithm = new GeneticAlgorithm(0, populationSize);
    genotypesSaved = 0;

    geneticAlgorithm->Evaluation = startEvaluation;

    if (elitistSelection) {

        // Second configuration
        geneticAlgorithm->Selection = geneticAlgorithm->defaultSelectionOperator;
        geneticAlgorithm->Recombination = randomRecombination;
        geneticAlgorithm->Mutation = mutateAllButBestTwo;

    } else {

        // First configuration
        geneticAlgorithm->Selection = remainderStochasticSampling;
        geneticAlgorithm->Recombination = randomRecombination;
        geneticAlgorithm->Mutation = mutateAllButBestTwo;
    }

    // TODO: EvolutionManager - implement conditions below, based on action -> event
    //allAgentsDied +=
//    geneticAlgorithm->EvaluationFinished();
//    all agents died then evaluation finished
//    AllAgentsDied += geneticAlgorithm.EvaluationFinished;

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
//        geneticAlgorithm->fitnessCalculationFinished(pop);
        // on FitnessCalculationFinished then WriteStatisticsToFile
    }

    // on FitnessCalculationFinished then CheckForTrackFinished

    //Restart logic
    if (restartAfter > 0)
    {
     //   on geneticAlgorithm.TerminationCriterion then CheckGenerationTermination;
     //   on geneticAlgorithm.AlgorithmTerminated then OnGATermination;
    }

    geneticAlgorithm->start();
}

void EvolutionManager::writeStatisticsFileStart() {

}

void EvolutionManager::writeStatisticsToFile(std::list<Genotype> currentPopulation) {

}

void EvolutionManager::checkForTrackFinished(std::list<Genotype> currentPopulation) {

}

bool EvolutionManager::checkGenerationTermination(std::list<Genotype> currentPopulation) {
    return false;
}

void EvolutionManager::onGATermination(GeneticAlgorithm ga) {

}

void EvolutionManager::restartAlgorithm(float wait) {

}

 void EvolutionManager::startEvaluation(std::list<Genotype> currentPopulation) {
}

void EvolutionManager::onAgentDied(Agent agent) {

}

std::list<Genotype> EvolutionManager::remainderStochasticSampling(std::list<Genotype> currentPopulation) {
    return std::list<Genotype>();
}

std::list<Genotype>
EvolutionManager::randomRecombination(std::list<Genotype> intermediatePopulation, int newPopulationSize) {
    return std::list<Genotype>();
}

void EvolutionManager::mutateAllButBestTwo(std::list<Genotype> newPopulation) {

}

void EvolutionManager::mutateAll(std::list<Genotype> newPopulation) {

}

EvolutionManager *EvolutionManager::GetInstance() {

    if (instance == 0) {
        instance = new EvolutionManager();
    }
    return instance;
}
