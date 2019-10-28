//
// C++ Implementation by Ajay Bhaga
//
// Modified Genetic Algorithm
// Based on design of Samuel Arzt (March 2017)
//

#ifndef EANN_SIMPLE_GENETIC_ALGORITHM_H
#define EANN_SIMPLE_GENETIC_ALGORITHM_H

#include <vector>
#include <list>
#include "genotype.h"
#include "random_d.h"

// Default min value of initial population parameters.
static const float DefInitParamMin = -1.0f;

// Default max value of initial population parameters.
static const float DefInitParamMax = 1.0f;

// Default probability of a parameter being swapped during crossover.
static const float DefCrossSwapProb = 0.6f;

// Default probability of a parameter being mutated.
static const float DefMutationProb = 0.3f;

// Default amount by which parameters may be mutated.
static const float DefMutationAmount = 2.0f;

// Default percent of genotypes in a new population that are mutated.
static const float DefMutationPerc = 1.0f;

class GeneticAlgorithm {
public:

    GeneticAlgorithm(int genotypeParamCount, int populationSize);
    ~GeneticAlgorithm();

    void start();
    void fitnessCalculationFinished(std::list<Genotype> currentPopulation);
    void evaluationFinished();
    void terminate();

    static void defaultPopulationInitialization(std::list<Genotype> population);
    static void asyncEvaluation(std::list<Genotype> currentPopulation);
    static void defaultFitnessCalculation(std::list<Genotype> currentPopulation);
    static std::list<Genotype> *defaultSelectionOperator(std::list<Genotype> currentPopulation);
    static std::list<Genotype> *defaultRecombinationOperator(std::list<Genotype> intermediatePopulation, int newPopulationSize);
    static void defaultMutationOperator(std::list<Genotype> newPopulation);
    static void completeCrossover(Genotype parent1, Genotype parent2, float swapChance, Genotype *offspring1, Genotype *offspring2);
    static void mutateGenotype(Genotype genotype, float mutationProb, float mutationAmount);
    static bool defaultTermination(std::list<Genotype> currentPopulation);

    // Use to initialize the initial population.
    typedef std::function<void (std::list<Genotype> initialPopulation)> InitializationOperator;

    // Used to evaluate (or start the evaluation process of) the current population.
    typedef std::function<void (std::list<Genotype> currentPopulation)> EvaluationOperator;

    // Used to calculate the fitness value of each genotype of the current population.
    typedef std::function<void (std::list<Genotype> currentPopulation)> FitnessCalculation;

    // Used to select genotypes of the current population and create the intermediate population.
    typedef std::function<std::list<Genotype> *(std::list<Genotype> currentPopulation)> SelectionOperator;

    // Used to recombine the intermediate population to generate a new population.
    typedef std::function<std::list<Genotype> *(std::list<Genotype> intermediatePopulation, int newPopulationSize)> RecombinationOperator;

    // Used to mutate the new population.
    typedef std::function<void (std::list<Genotype> newPopulation)> MutationOperator;

        // Used to check whether any termination criterion has been met.
    typedef std::function<bool (std::list<Genotype> currentPopulation)> CheckTerminationCriterion;

    // Operators
    InitializationOperator InitializePopulation = defaultPopulationInitialization;
    EvaluationOperator Evaluation = asyncEvaluation;
    FitnessCalculation FitnessCalculationMethod = defaultFitnessCalculation;
    SelectionOperator Selection = defaultSelectionOperator;
    RecombinationOperator Recombination = defaultRecombinationOperator;
    MutationOperator Mutation = defaultMutationOperator;
    CheckTerminationCriterion TerminationCriterion = defaultTermination;

    // The amount of genotypes in a population.
    int populationSize;

    // The amount of generations that have already passed.
    int generationCount;

    // Whether the current population shall be sorted before calling the termination criterion operator.
    bool sortPopulation;

    // Whether the genetic algorithm is currently running.
    bool running;

    bool algorithmTerminated;

private:
    std::list<Genotype> currentPopulation;
};

#endif //EANN_SIMPLE_GENETIC_ALGORITHM_H
