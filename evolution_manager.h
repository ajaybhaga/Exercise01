//
// C++ Implementation by Ajay Bhaga
//
// Modified Genetic Algorithm
// Based on design of Samuel Arzt (March 2017)
//

#ifndef EANN_SIMPLE_EVOLUTION_MANAGER_H
#define EANN_SIMPLE_EVOLUTION_MANAGER_H

#include <string>
#include <list>
#include "agent.h"
#include "random_d.h"
#include "genetic_algorithm.h"


// Singleton class for managing the evolutionary processes.
class EvolutionManager {
public:

    static EvolutionManager *GetInstance();
    ~EvolutionManager();

    int getGenerationCount();
    void startEvolution();
    void writeStatisticsFileStart();
    void writeStatisticsToFile(std::list<Genotype> currentPopulation);
    void checkForTrackFinished(std::list<Genotype> currentPopulation);
    bool checkGenerationTermination(std::list<Genotype> currentPopulation);
    void onGATermination(GeneticAlgorithm ga);
    void restartAlgorithm(float wait);
    static void startEvaluation(std::list<Genotype> currentPopulation);
    void onAgentDied(Agent agent);
    static std::list<Genotype> remainderStochasticSampling(std::list<Genotype> currentPopulation);
    static std::list<Genotype> randomRecombination(std::list<Genotype> intermediatePopulation, int newPopulationSize);
    static void mutateAllButBestTwo(std::list<Genotype> newPopulation);
    static void mutateAll(std::list<Genotype> newPopulation);

        // The amount of agents that are currently alive.
    int agentsAliveCount = 0;

    // Event for when all agents have died.
    bool allAgentsDied = false;

private:

    static EvolutionManager *instance;
    EvolutionManager();

    // Whether or not the results of each generation shall be written to file.
    bool saveStatistics = false;
    std::string statisticsFileName;

    // How many of the first to finish the course should be saved to file
    int saveFirstGenotype = 0;
    int genotypesSaved = 0;

    // Population size
    int populationSize = 30;

    // After how many generations should the genetic algorithm be restarted (0 for never)
    int restartAfter = 100;

    // Whether to use elitist selection or remainder stochastic sampling
    bool elitistSelection = false;

    // Topology of the agent's FNN
    int* FNNTopology;

    // The current population agents.
    std::list<Agent> *agents;

    GeneticAlgorithm *geneticAlgorithm;
};

#endif //EANN_SIMPLE_EVOLUTION_MANAGER_H
