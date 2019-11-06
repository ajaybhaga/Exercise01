//
// C++ Implementation by Ajay Bhaga
//
// Modified Genetic Algorithm
// Based on design of Samuel Arzt (March 2017)
//

#ifndef EANN_SIMPLE_AGENT_H
#define EANN_SIMPLE_AGENT_H

#include "shared_libs.h"
#include <cyclone.h>

class Agent {
public:

    Agent();
    Agent(Genotype &genotype, NeuralLayer::ActivationFunction defaultActivation, int* topology);
    ~Agent();
    void reset();
    void kill();
    int compareTo(Agent &other);

    // Underlying genotype of this agent.
    Genotype genotype;

    // The feed-forward neural network which was constructed from the genotype of this agent.
    NeuralNetwork *ffn;

    // Flag when the agent died (stopped participating in the simulation).
    Event agentDied;

    // Whether this agent is currently alive (actively participating in the simulation).
    bool isAlive();

private:
    bool alive = false;

    cyclone::Vector3 position;
public:
    const cyclone::Vector3 &getPosition() const;

    void setPosition(const cyclone::Vector3 &position);

    const cyclone::Quaternion &getRotation() const;

    void setRotation(const cyclone::Quaternion &rotation);

private:
    cyclone::Quaternion rotation;
};

#endif //EANN_SIMPLE_AGENT_H
