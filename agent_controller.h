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

    int nextId();

    std::shared_ptr<Agent> agent;
    bool useUserInput = false;
    // AgentMovement movement;



private:

    static int idGenerator;

    // Maximum delay in seconds between the collection of two checkpoints until this agent dies.
    const float MAX_CHECKPOINT_DELAY = 7;

    // Sensor[] sensors;
    float timeSinceLastCheckpoint;

    std::string name;
};

#endif //EANN_SIMPLE_AGENT_CONTROLLER_H
