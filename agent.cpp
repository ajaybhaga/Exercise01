//
// C++ Implementation by Ajay Bhaga
//
// Modified Genetic Algorithm
// Based on design of Samuel Arzt (March 2017)
//

#include "agent.h"

Agent::Agent() {

}

// Initializes a new agent from given genotype, constructing a new feed-forward neural network from
// the parameters of the genotype.
Agent::Agent(Genotype &genotype, NeuralLayer::ActivationFunction defaultActivation, int *topology) {

    alive = false;
    this->genotype = genotype;
    ffn = new NeuralNetwork(topology, NUM_NEURAL_LAYERS);

    for (int i = 0; i < NUM_NEURAL_LAYERS; i++) {
        ffn->layers[i]->neuronActivationFunction = defaultActivation;
    }

    // Check if topology is valid
    if (ffn->weightCount != genotype.parameterCount) {
        std::cout << "Error: the given genotype's parameter count must match the neural network topology's weight count." << std::endl;
    } else {
        std::cout << "Success: the given genotype's parameter count matches the neural network topology's weight count." << std::endl;
    }

    // Construct FFN from genotype
    for (int k = 0; k < NUM_NEURAL_LAYERS; k++) {

        for (int i = 0; i < ffn->layers[k]->neuronCount; i++) {
            for (int j = 0; j < ffn->layers[k]->outputCount; j++) {
                // Retrieve parameters for genotype
                float *parameters = this->genotype.getParameterCopy();

                // Set weights to parameter values
                for (int p = 0; p < this->genotype.parameterCount; p++) {
                    ffn->layers[k]->weights[i][j] = parameters[p];
                }
            }
        }
    }
}

Agent::~Agent() {

}

// Reset this agent to be alive again.
void Agent::reset() {
    genotype.evaluation = 0;
    genotype.fitness = 0;
    alive = true;
}

void Agent::kill() {
    agentDied();
    alive = false;
}

int Agent::compareTo(Agent &other) {
    // TODO: Implement agent genotype comparison

    bool match = true;

    // Construct FFN from genotype
    for (int k = 0; k < NUM_NEURAL_LAYERS; k++) {

        for (int i = 0; i < ffn->layers[k]->neuronCount; i++) {
            for (int j = 0; j < ffn->layers[k]->outputCount; j++) {
                // Retrieve parameters for genotype
                float *parametersA = this->genotype.getParameterCopy();
                float *parametersB = other.genotype.getParameterCopy();

                // Compare genotypes
                for (int p = 0; p < this->genotype.parameterCount; p++) {

                    if (parametersA[p] != parametersB[p]) {
                        match = false;
                        std::cout << "Agent.compareTo -> Match failed on parameter #: " << p << std::endl;
                    }
                }
            }
        }
    }

    if (match) {
        return 0;
    } else {
        return -1;
    }
}

bool Agent::isAlive() {
    return alive;
}

