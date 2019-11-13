//
// C++ Implementation by Ajay Bhaga
//
// Modified Genetic Algorithm
// Based on design of Samuel Arzt (March 2017)
//

#ifndef EANN_SIMPLE_AGENT_CONTROLLER_H
#define EANN_SIMPLE_AGENT_CONTROLLER_H

#include <cyclone.h>

#include "random_d.h"
#include "event.h"
#include "genotype.h"
#include "neural_layer.h"
#include "genetic_algorithm.h"
#include "neural_network.h"
#include "sensor.h"
#include "agent_fsm.h"
#include "agent.h"
#include "agent_movement.h"
#include "shared_libs.h"

class AgentController {
public:

    AgentController(Agent agent);
    ~AgentController();

    void awake();
    void start();
    void restart();
    void update(float duration);
    void die();
    void checkpointCaptured();
    float getCurrentCompletionReward();
    void setCurrentCompletionReward(float reward);

    int nextId();

    std::shared_ptr<Agent> agent;
    std::shared_ptr<AgentMovement> movement;
    std::shared_ptr<AgentFSM> fsm;

    bool useUserInput = false;

    // Event for when all agents have died.
//    Event allAgentsDied;


private:

    static int idGenerator;

    // Maximum delay in seconds between the collection of two checkpoints until this agent dies.
    const float MAX_CHECKPOINT_DELAY = 7;

    std::vector<Sensor> sensors;
    float timeSinceLastCheckpoint = 0.0;
public:
    float getTimeSinceLastCheckpoint() const;

private:
    long startTime;
    long lastTime = 0;

    std::string name;
};

#endif //EANN_SIMPLE_AGENT_CONTROLLER_H
