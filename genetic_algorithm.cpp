//
// Modified Genetic Algorithm
// Based on design of Samuel Arzt (March 2017)
//

#include "genetic_algorithm.h"

#include <iostream>
#include <string>
#include <list>
#include <cassert>
#include <fstream>      // std::ifstream, std::ofstream
#include <stdlib.h>     /* atoi */
#include <stdio.h>
#include <cstring>


GeneticAlgorithm::GeneticAlgorithm(int genotypeParamCount, int populationSize) {

    this->populationSize = populationSize;
    for (int i = 0; i < populationSize; i++) {
        Genotype* genotype = new Genotype(new float[genotypeParamCount], genotypeParamCount);
        currentPopulation.push_back(*genotype);
    }

    generationCount = 1;
    sortPopulation = true;
    running = false;
}

GeneticAlgorithm::~GeneticAlgorithm() {

    // Deallocate Heap memory
//    delete[] parameters;
}

void GeneticAlgorithm::Start() {

    running = true;
    InitializePopulation(currentPopulation);


}

void GeneticAlgorithm::EvaluationFinished() {

}

void GeneticAlgorithm::Terminate() {

}

void GeneticAlgorithm::DefaultPopulationInitialization(std::vector<Genotype> population) {

    //        foreach (Genotype genotype in population)

    // Set parameters to random values in set range
    for(std::vector<Genotype>::iterator it = population.begin(); it != population.end(); ++it) {
        /* std::cout << *it; ... */
    }
}

void GeneticAlgorithm::AsyncEvaluation(std::vector<Genotype> currentPopulation) {

}

void GeneticAlgorithm::DefaultFitnessCalculation(std::vector<Genotype> currentPopulation) {

}

std::list<Genotype> GeneticAlgorithm::DefaultSelectionOperator(std::list<Genotype> currentPopulation) {

}

std::list<Genotype> GeneticAlgorithm::DefaultRecombinationOperator(std::list<Genotype> intermediatePopulation, int newPopulationSize) {

}

void GeneticAlgorithm::DefaultMutationOperator(std::list<Genotype> newPopulation) {

}

void GeneticAlgorithm::CompleteCrossover(Genotype parent1, Genotype parent2, float swapChance, Genotype *offspring1,
                                         Genotype *offspring2) {

}

void GeneticAlgorithm::MutateGenotype(Genotype genotype, float mutationProb, float mutationAmount) {

}

