//
// C++ Implementation by Ajay Bhaga
//
// Modified Genetic Algorithm
// Based on design of Samuel Arzt (March 2017)
//

#include "agent.h"

Agent::Agent() {

}

Agent::Agent(Genotype genotype, NeuralLayer) {

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
    alive = false;
}

int Agent::compareTo(Agent other) {
    // TODO: Implement agent genotype comparison
    return 0;
}

bool Agent::isAlive() {
    return alive;
}
