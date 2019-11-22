//
// C++ Implementation by Ajay Bhaga
//
// Modified Genetic Algorithm
// Based on design of Samuel Arzt (March 2017)
//

#ifndef EANN_SIMPLE_AGENT_H
#define EANN_SIMPLE_AGENT_H

#include "shared_libs.h"

class Agent {
public:

    Agent(Genotype *genotype, NeuralLayer::ActivationFunction defaultActivation, int *topology);
    ~Agent();
    void reset();
    void kill();
    int compareTo(Agent &other);

    // Agent id
    unsigned int id;
    std::string name;

    // Underlying genotype of this agent.
    Genotype *genotype;

    // The feed-forward neural network which was constructed from the genotype of this agent.
    NeuralNetwork *ffn;

    // Flag when the agent died (stopped participating in the simulation).
    Event agentDied;

    // Whether this agent is currently alive (actively participating in the simulation).
    bool isAlive();

    const cyclone::Vector3 &getPosition() const;
    void setPosition(const cyclone::Vector3 &position);
    const cyclone::Quaternion &getRotation() const;
    void setRotation(const cyclone::Quaternion &rotation);
    const cyclone::Vector3 &getWinPos() const;
    void setWinPos(const cyclone::Vector3 &winPos);
    const cyclone::Vector3 &getColour() const;
    void setColour(const cyclone::Vector3 &colour);
    const char* getName();
    unsigned generateId();
    bool isHit() const;
    void setHit(bool hit);
    long getLastHit() const;
    void setLastHit(long lastHit);

private:
    bool alive = false;
    bool hit = false;
    long lastHit = 0;

    cyclone::Vector3 position;
    cyclone::Vector3 winPos;
    cyclone::Quaternion rotation;
    cyclone::Vector3 colour;

};

#endif //EANN_SIMPLE_AGENT_H
