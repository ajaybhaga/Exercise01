//
// Created by Bad Zindagi on 2019-10-25.
//

#ifndef EANN_SIMPLE_GENETIC_ALGORITHM_H
#define EANN_SIMPLE_GENETIC_ALGORITHM_H

#include <vector>
#include <list>
#include "genotype.h"
#include "random_d.h"

class GeneticAlgorithm {
public:

    GeneticAlgorithm(int genotypeParamCount, int populationSize);
    ~GeneticAlgorithm();

    void Start();
    void EvaluationFinished();
    void Terminate();

    static void DefaultPopulationInitialization(std::vector<Genotype> population);
    static void AsyncEvaluation(std::vector<Genotype> currentPopulation);
    static void DefaultFitnessCalculation(std::vector<Genotype> currentPopulation);
    static std::list<Genotype> DefaultSelectionOperator(std::list<Genotype> currentPopulation);
    static std::list<Genotype> DefaultRecombinationOperator(std::list<Genotype> intermediatePopulation, int newPopulationSize);
    static void DefaultMutationOperator(std::list<Genotype> newPopulation);
    static void CompleteCrossover(Genotype parent1, Genotype parent2, float swapChance, Genotype* offspring1, Genotype* offspring2);
    static void MutateGenotype(Genotype genotype, float mutationProb, float mutationAmount);

    // Use to initialize the initial population.
    typedef std::function<void (std::vector<Genotype> initialPopulation)> InitializationOperator;

    // Used to evaluate (or start the evaluation process of) the current population.
    typedef std::function<void (std::vector<Genotype> currentPopulation)> EvaluationOperator;

    // Used to calculate the fitness value of each genotype of the current population.
    typedef std::function<void (std::vector<Genotype> currentPopulation)> FitnessCalculation;

    // Used to select genotypes of the current population and create the intermediate population.
    typedef std::function<std::list<Genotype> (std::list<Genotype> currentPopulation)> SelectionOperator;

    // Used to recombine the intermediate population to generate a new population.
    typedef std::function<std::list<Genotype> (std::list<Genotype> intermediatePopulation, int newPopulationSize)> RecombinationOperator;

    // Used to mutate the new population.
    typedef std::function<void (std::list<Genotype> newPopulation)> MutationOperator;

    // Used to check whether any termination criterion has been met.
    typedef std::function<bool (std::list<Genotype> currentPopulation)> CheckTerminationCriterion;

    // Default min value of initial population parameters.
    const float DefInitParamMin = -1.0f;

    // Default max value of initial population parameters.
    const float DefInitParamMax = 1.0f;

    // Default probability of a parameter being swapped during crossover.
    const float DefCrossSwapProb = 0.6f;

    // Default probability of a parameter being mutated.
    const float DefMutationProb = 0.3f;

    // Default amount by which parameters may be mutated.
    const float DefMutationAmount = 2.0f;

    // Default percent of genotypes in a new population that are mutated.
    const float DefMutationPerc = 1.0f;

    // Operators
    InitializationOperator InitializePopulation = DefaultPopulationInitialization;
    EvaluationOperator Evaluation = AsyncEvaluation;
    FitnessCalculation FitnessCalculationMethod = DefaultFitnessCalculation;
    SelectionOperator Selection = DefaultSelectionOperator;
    RecombinationOperator Recombination = DefaultRecombinationOperator;
    MutationOperator Mutation = DefaultMutationOperator;
    CheckTerminationCriterion TerminationCriterion = NULL;

    // The amount of genotypes in a population.
    int populationSize;

    // The amount of generations that have already passed.
    int generationCount;

    // Whether the current population shall be sorted before calling the termination criterion operator.
    bool sortPopulation;

    // Whether the genetic algorithm is currently running.
    bool running;

private:
    std::vector<Genotype, std::allocator<Genotype>> currentPopulation;
};

#endif //EANN_SIMPLE_GENETIC_ALGORITHM_H
