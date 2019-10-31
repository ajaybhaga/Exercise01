//
// C++ Implementation by Ajay Bhaga
//
// Modified Genetic Algorithm
// Based on design of Samuel Arzt (March 2017)
//

#include "genetic_algorithm.h"

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

}

void GeneticAlgorithm::start() {
    // Init
    running = true;
    initializePopulation(currentPopulation);
    evaluation(currentPopulation);
}

void GeneticAlgorithm::evaluationFinished() {
    // Calculate fitness from evaluation
    fitnessCalculationMethod(currentPopulation);

    // Sort population if flag was set
    if (sortPopulation) {
        // TODO: sort currentPopulation -> unsure if this sorting is correct;
       // currentPopulation.sort();
    }

    // Fire fitness calculation finished event
    fitnessCalculationFinished();

    // Check termination criterion
    if (checkTermination) {
        terminate();
        return;
    }

    // Apply selection
    std::list<Genotype> *intermediatePopulation = selection(currentPopulation);

    // Apply recombination
    std::list<Genotype> *newPopulation = recombination(*intermediatePopulation, populationSize);

    // Apply mutation
    mutation(*newPopulation);

    // Set current population to newly generated one and start evaluation again
    currentPopulation = *newPopulation;
    generationCount++;

    evaluation(currentPopulation);
}

void GeneticAlgorithm::terminate() {

    running = false;
    algorithmTerminated();

}

void GeneticAlgorithm::defaultPopulationInitialization(std::list<Genotype> population) {

    int popCount = 0;
    // Set parameters to random values in set range
    for (std::list<Genotype>::iterator it = population.begin(); it != population.end(); ++it) {
        /* std::cout << *it; ... */
        it->setRandomParameters(DefInitParamMin, DefInitParamMax);
        std::cout << "Generating genotype [" << (popCount + 1) << "]." << std::endl;
//        it->outputToConsole();
        popCount++;
    }
}

void GeneticAlgorithm::asyncEvaluation(std::list<Genotype> currentPopulation) {
    // At this point the async evaluation should be started and after it is finished EvaluationFinished should be called
    std::cout << "Reached async evaluation." << std::endl;
}

void GeneticAlgorithm::defaultFitnessCalculation(std::list<Genotype> currentPopulation) {

    // First calculate average evaluation of whole population
    int populationSize = 0;
    float overallEvaluation = 0;
    for (std::list<Genotype>::iterator it = currentPopulation.begin(); it != currentPopulation.end(); ++it) {
        overallEvaluation += it->evaluation;
        populationSize++;
    }

    float averageEvaluation = overallEvaluation / populationSize;

    // Now assign fitness with formula fitness = evaluation / averageEvaluation
    for (std::list<Genotype>::iterator it = currentPopulation.begin(); it != currentPopulation.end(); ++it) {
        it->fitness = it->evaluation / averageEvaluation;
    }
}

std::list<Genotype>* GeneticAlgorithm::defaultSelectionOperator(std::list<Genotype> currentPopulation) {

    std::list<Genotype>* intermediatePopulation = new std::list<Genotype>();

    // Get first 3 list items (top 3)
    size_t n = 3;
    auto end = std::next(currentPopulation.begin(), std::min(n, currentPopulation.size()));
    std::list<Genotype> b(currentPopulation.begin(), end);
    // Selects best three genotypes of the current population and copies them to the intermediate population.
    for (std::list<Genotype>::iterator it = b.begin(); it != b.end(); ++it) {
        intermediatePopulation->push_back(*it);
    }

    return intermediatePopulation;
}

// Simply crosses the first with the second genotype of the intermediate population until the new population is of desired size.
std::list<Genotype> *GeneticAlgorithm::defaultRecombinationOperator(std::list<Genotype> intermediatePopulation, int newPopulationSize) {

    if (intermediatePopulation.size() < 2) {
        std::cout << "Intermediate population size must be greater than 2 for this operator.";
        return nullptr;
    }

    std::list<Genotype> *newPopulation = new std::list<Genotype>();

    if (newPopulation->size() < newPopulationSize) {

        Genotype *offspring1;
        Genotype *offspring2;

        // Get first 2 list items (top 2)
        size_t n = 2;
        auto end = std::next(intermediatePopulation.begin(), std::min(n, intermediatePopulation.size()));
        std::list<Genotype> b(intermediatePopulation.begin(), end);

        Genotype intermediatePopulation0;
        Genotype intermediatePopulation1;

        int count = 0;
        for (std::list<Genotype>::iterator it = b.begin(); it != b.end(); ++it) {
//            intermediatePopulation->push_back(*it);
            switch (count) {
                case 0:
                    intermediatePopulation0 = *it;
                    break;
                case 1:
                    intermediatePopulation1 = *it;
                    break;

            }
            count++;
        }

        completeCrossover(intermediatePopulation0, intermediatePopulation1, DefCrossSwapProb, offspring1, offspring2);

        newPopulation->push_back(*offspring1);
        if (newPopulation->size() < newPopulationSize) {
            newPopulation->push_back(*offspring2);
        }
    }

    return newPopulation;
}

void GeneticAlgorithm::defaultMutationOperator(std::list<Genotype> newPopulation) {

    // Create the random number generator
    random_d rd{0, 1};

    for (std::list<Genotype>::iterator it = newPopulation.begin(); it != newPopulation.end(); ++it) {

        for (Genotype& genotype : newPopulation) {
            if (rd() < DefMutationPerc) {
                mutateGenotype(genotype, DefMutationProb, DefMutationAmount);
            }
        }

    }
}

void GeneticAlgorithm::completeCrossover(Genotype parent1, Genotype parent2, float swapChance, Genotype *offspring1,
                                         Genotype *offspring2) {

    // Create the random number generator
    random_d rd{0, 1};

    // Initialize new parameter vectors
    int parameterCount = parent1.parameterCount;
    float *off1Parameters = new float[parameterCount];
    float *off2Parameters = new float[parameterCount];

    // Iterate over all parameters randomly swapping
    for (int i = 0; i < parameterCount; i++) {

        if (rd() < swapChance) {
            // Swap parameters
            off1Parameters[i] = parent2.getParameter(i);
            off2Parameters[i] = parent1.getParameter(i);
        } else {
            // Dont swap parameters
            off1Parameters[i] = parent1.getParameter(i);
            off2Parameters[i] = parent2.getParameter(i);
        }
    }

    Genotype *offspring1_out = new Genotype(off1Parameters, parameterCount);
    Genotype *offspring2_out = new Genotype(off2Parameters, parameterCount);

    offspring1 = offspring1_out;
    offspring2 = offspring2_out;
}

void GeneticAlgorithm::mutateGenotype(Genotype genotype, float mutationProb, float mutationAmount) {

    // Create the random number generator
    random_d rd{0, 1};

    for (int i = 0; i < genotype.parameterCount; i++) {

        if (rd() < mutationProb) {
            // Mutate by random amount in range [-mutationAmount, mutationAmount]
            genotype.setParameter(i, genotype.getParameter(i) + (float)rd() * (mutationAmount * 2) - mutationAmount);
        }
    }
}

bool GeneticAlgorithm::defaultTermination(std::list<Genotype> currentPopulation) {
    return false;
}

const std::list<Genotype> &GeneticAlgorithm::getCurrentPopulation() const {
    return currentPopulation;
}
