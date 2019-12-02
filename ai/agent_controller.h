//
// C++ Implementation by Ajay Bhaga
//
// Modified Genetic Algorithm
// Based on design of Samuel Arzt (March 2017)
//

#ifndef EANN_SIMPLE_AGENT_CONTROLLER_H
#define EANN_SIMPLE_AGENT_CONTROLLER_H

#include <cyclone.h>

#include "util/random_d.h"
#include "util/event.h"
#include "ai/genotype.h"
#include "ai/neural_layer.h"
#include "ai/genetic_algorithm.h"
#include "ai/neural_network.h"
#include "ai/sensor.h"
#include "ai/agent_fsm.h"
#include "ai/agent.h"
#include "ai/agent_movement.h"
#include "shared_libs.h"

// Forward declaration
class Agent;
class Sensor;

class AgentController {
public:

    AgentController(Agent *agent);
    ~AgentController();

    void awake();
    void start();
    void restart();
    void update(float duration);
    void die();
    void checkpointCaptured();
    float getCurrentCompletionReward();
    void setCurrentCompletionReward(float reward);
    const std::vector<Sensor> &getSensors() const;

    Agent *agent;
    AgentMovement *movement;
    AgentFSM *fsm;

    bool useUserInput = false;
    float getTimeSinceLastCheckpoint() const;

    // Event for when all agents have died.
//    Event allAgentsDied;

private:
    // Maximum delay in seconds between the collection of two checkpoints until this agent dies.
    const float MAX_CHECKPOINT_DELAY = 7;
    std::vector<Sensor> sensors;
    float timeSinceLastCheckpoint = 0.0;
    long startTime;
    long lastTime = 0;

};

#endif //EANN_SIMPLE_AGENT_CONTROLLER_H
