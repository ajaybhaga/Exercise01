//
// C++ Implementation by Ajay Bhaga
//
// Modified Genetic Algorithm
// Based on design of Samuel Arzt (March 2017)
//

#include "evolution_manager.h"

namespace fs = std::__fs::filesystem;

bool directoryExists(const char *dname){
    DIR *di = opendir(dname); // open the directory
    if(di) return true; // can open=>return true
    else return false; // otherwise return false
    closedir(di);
}

EvolutionManager::EvolutionManager() {
    saveStatistics = true;
}

EvolutionManager::~EvolutionManager() {

    for (auto it = agents.begin(); it != agents.end(); ++it) {
        delete &it;
    }

    for (auto it = agentControllers.begin(); it != agentControllers.end(); ++it) {
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
    return getInstance()->getGeneticAlgorithm()->generationCount;
}

void EvolutionManager::evalFinished() {
    EvolutionManager::getInstance()->getGeneticAlgorithm()->evaluationFinished();
}

void EvolutionManager::startEvolution() {

    // Build Neural Network.

    // Create neural layer array (NUM_NEURAL_LAYERS = 4)
    getInstance()->ffnTopology = new int[NUM_NEURAL_LAYERS+1];

    // It comprises 4 layers: an input layer with 5 neurons, two hidden layers with 4 and 3 neurons respectively
    // and an output layer with 2 neurons.

    // Input layer
    getInstance()->ffnTopology[0] = 5;

    // Hidden layers
    getInstance()->ffnTopology[1] = 4;
    getInstance()->ffnTopology[2] = 3;

    // Output layer
    getInstance()->ffnTopology[3] = 2;
    getInstance()->ffnTopology[4] = 2;

    // Create neural network to determine parameter count
    NeuralNetwork *nn = new NeuralNetwork(getInstance()->ffnTopology, NUM_NEURAL_LAYERS);

    // Setup genetic algorithm
    getInstance()->geneticAlgorithm = new GeneticAlgorithm(nn->weightCount, getInstance()->populationSize);
    getInstance()->genotypesSaved = 0;

    getInstance()->geneticAlgorithm->evaluation = startEvaluation;

    if (getInstance()->elitistSelection) {

        // Second configuration
        getInstance()->geneticAlgorithm->selection = getInstance()->geneticAlgorithm->defaultSelectionOperator;
        getInstance()->geneticAlgorithm->recombination = randomRecombination;
        getInstance()->geneticAlgorithm->mutation = mutateAllButBestTwo;

    } else {

        // First configuration
        getInstance()->geneticAlgorithm->selection = remainderStochasticSampling;
        getInstance()->geneticAlgorithm->recombination = randomRecombination;
        getInstance()->geneticAlgorithm->mutation = mutateAllButBestTwo;
    }

    getInstance()->allAgentsDied += evalFinished;

    char buffer[80];
    time_t rawtime;
    struct tm *timeinfo;
    time (&rawtime);
    timeinfo = localtime(&rawtime);

    // Statistics
    if (getInstance()->saveStatistics) {
        strftime(buffer,sizeof(buffer),"%d-%m-%Y_%H:%M:%S",timeinfo);
        std::string str(buffer);
        getInstance()->statisticsFileName = std::string("evaluation-") + buffer;
        writeStatisticsFileStart();
        getInstance()->geneticAlgorithm->fitnessCalculationFinished += writeStatisticsToFile;
    }

    getInstance()->geneticAlgorithm->fitnessCalculationFinished += checkForTrackFinished;

    //Restart logic
    if (getInstance()->restartAfter > 0) {

        getInstance()->geneticAlgorithm->terminationCriterion += checkGenerationTermination;
        getInstance()->geneticAlgorithm->algorithmTerminated += onGATermination;

    }

    getInstance()->geneticAlgorithm->start();
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
        outText += std::to_string(getInstance()->populationSize);
        outText += " on Track " + trackName + ".\n";
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
    getInstance()->agentControllers.clear();
    getInstance()->agentsAliveCount = 0;

    // Iterate through genotypes
    for (auto it = currentPopulation.begin(); it != currentPopulation.end(); ++it) {
        Agent *agent = new Agent(*it, MathHelper::softSignFunction, getInstance()->ffnTopology);
        AgentController *agentController = new AgentController(*agent);
        getInstance()->agents.emplace_back(agent);
        getInstance()->agentControllers.emplace_back(agentController);
        getInstance()->agentsAliveCount++;

    }

    // TrackManager.Instance.setCarAmount(agents.Count);

    // Iterate through agents
    for (auto it = getInstance()->agents.begin(); it != getInstance()->agents.end(); ++it) {
        // Iterate through agent controller, update agent reference
       // getInstance()->agentControllers.emplace_back(new AgentController(*it));
        getInstance()->agentsAliveCount++;
       // getInstance()->agents.push_back(new Agent(*it, MathHelper::softSignFunction, getInstance()->ffnTopology));

//        std::list<Genotype>::iterator it



    }


}

void EvolutionManager::onAgentDied() {

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
    return getInstance()->geneticAlgorithm;
}
