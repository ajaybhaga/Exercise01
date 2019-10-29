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
Agent::Agent(Genotype genotype, NeuralLayer::ActivationFunction defaultActivation, int *topology) {

    alive = false;
    this->genotype = genotype;
//    ffn = new NeuralNetwork(topology);

    // TODO: Finish implementation once Neural Network classes are implemented.


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

int Agent::compareTo(Agent other) {
    // TODO: Implement agent genotype comparison
    return 0;
}

bool Agent::isAlive() {
    return alive;
}

