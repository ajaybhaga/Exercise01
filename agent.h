//
// C++ Implementation by Ajay Bhaga
//
// Modified Genetic Algorithm
// Based on design of Samuel Arzt (March 2017)
//

#ifndef EANN_SIMPLE_AGENT_H
#define EANN_SIMPLE_AGENT_H

#include <string>
#include <vector>
#include <list>
#include "random_d.h"
#include "genotype.h"
#include "neural_layer.h"

class Agent {
public:

    Agent();

    //
    Agent(Genotype genotype, NeuralLayer::ActivationFunction defaultActivation, int* topology);
    ~Agent();
    void reset();
    void kill();
    int compareTo(Agent other);

    // Underlying genotype of this agent.
    Genotype genotype;

    // The feed-forward neural network which was constructed from the genotype of this agent.
//    NeuralNetwork ffn;

    // Flag when the agent died (stopped participating in the simulation).
    bool agentDied;

    // Whether this agent is currently alive (actively participating in the simulation).
    bool isAlive();

private:
    bool alive = false;
};

#endif //EANN_SIMPLE_AGENT_H
