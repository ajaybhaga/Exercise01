//
// C++ Implementation by Ajay Bhaga
//
// Modified Genetic Algorithm
// Based on design of Samuel Arzt (March 2017)
//

#ifndef EANN_SIMPLE_AGENT_CONTROLLER_H
#define EANN_SIMPLE_AGENT_CONTROLLER_H

#include "agent.h"

class AgentController {
public:

    AgentController(Agent agent);
    ~AgentController();

    void awake();
    void start();
    void restart();
    void update();
    void fixedUpdate();
    void die();
    void checkpointCaptured();
    float getCurrentCompletionReward();
    void setCurrentCompletionReward(float reward);

    // Maximum delay in seconds between the collection of two checkpoints until this car dies.
    const float MAX_CHECKPOINT_DELAY = 7;

    std::unique_ptr<Agent> agent;
    bool useUserInput = false;
    // AgentMovement movement;

private:

    // Sensor[] sensors;
    float timeSinceLastCheckpoint;
};

#endif //EANN_SIMPLE_AGENT_CONTROLLER_H
