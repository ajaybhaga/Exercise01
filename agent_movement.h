//
// C++ Implementation by Ajay Bhaga
//
// Modified Genetic Algorithm
// Based on design of Samuel Arzt (March 2017)
//

#ifndef EANN_SIMPLE_AGENT_MOVEMENT_H
#define EANN_SIMPLE_AGENT_MOVEMENT_H

#include "agent_controller.h"

// Forward declaration
class AgentController;

class AgentMovement {
public:

    AgentMovement();
    ~AgentMovement();

    void fixedUpdate(float deltaTime);
    void checkInput();
    void applyInput(float deltaTime);
    void setInputs(double *input);
    void applyVelocity(float deltaTime);
    void applyFriction(float deltaTime);
    void stop();

    std::shared_ptr<AgentController> agentController;

    // Event for when agent hits wall.
    Event hitWall;

private:

    // Movement constants
    const float MAX_VEL = 20.0f;
    const float ACCELERATION = 8.0f;
    const float VEL_FRICT = 2.0f;
    const float TURN_SPEED = 100.0f;

    // The current velocity of the agent.
    cyclone::Vector3 velocity;
    // The current rotation of the agent.
    cyclone::Quaternion rotation;

    // Horizontal = engine force
    double horizontalInput;

    // Vertical = turning force
    double verticalInput;
};

#endif //EANN_SIMPLE_AGENT_MOVEMENT_H
