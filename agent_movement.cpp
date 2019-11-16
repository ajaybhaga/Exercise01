//
// C++ Implementation by Ajay Bhaga
//
// Modified Genetic Algorithm
// Based on design of Samuel Arzt (March 2017)
//

#include "shared_libs.h"

// Create the random number generator
static random_d rd{0.0, 1.0};

AgentMovement::AgentMovement(AgentController *agentController) {
    //this->agentController.make_shared(agentController);
    this->agentController = std::make_shared<AgentController>(*agentController);
}

AgentMovement::~AgentMovement() {

}

void AgentMovement::update(float deltaTime) {
    checkInput();
    applyInput(deltaTime);
    applyVelocity(deltaTime);
    applyFriction(deltaTime);

}

void AgentMovement::checkInput() {
}

void AgentMovement::applyInput(float deltaTime) {
    // Clamp input
    if (verticalInput > 1) {
        verticalInput = 1;
    } else if (verticalInput < -1) {
     verticalInput = -1;
    }

    if (horizontalInput > 1) {
        horizontalInput = 1;
    } else if (horizontalInput < -1) {
        horizontalInput = -1;
    }

    // Agent can only accelerate further if velocity is lower than engineForce * MAX_VEL
    bool canAccelerate = true;
    if (verticalInput < 0) {
        canAccelerate = velocity[1] > verticalInput * MAX_VEL;
    } else if (verticalInput > 0) {
        canAccelerate = velocity[1] < verticalInput * MAX_VEL;
    }

    // Set velocity
    if (canAccelerate) {
        velocity[1] += (float) verticalInput * ACCELERATION * deltaTime;

        // Clamp velocity
        if (velocity[1] > MAX_VEL) {
            velocity[1] = MAX_VEL;
        } else if (velocity[1] < -MAX_VEL) {
            velocity[1] = -MAX_VEL;
        }
    }

    // Set rotation
    this->rotation = agentController->agent->getRotation();
    this->rotation *= cyclone::Quaternion((float)-horizontalInput * TURN_SPEED * deltaTime, cyclone::Vector3(0, 0, 1));
}

void AgentMovement::setInputs(double *input) {

    horizontalInput = input[0];
    verticalInput = input[1];
}

// Apply the current velocity to the position of the agent.
void AgentMovement::applyVelocity(float deltaTime) {
    cyclone::Vector3 direction = cyclone::Vector3(0, 1, 0);
    cyclone::Quaternion currRot = this->agentController->agent->getRotation();

    this->agentController->agent->setRotation(rotation);

    cyclone::Quaternion dirQ = cyclone::Quaternion();
    dirQ.addScaledVector(direction, 1.0);
    dirQ.rotateByVector(velocity * deltaTime);

    static random_d rdx{-0.05, 0.05};

    velocity[0] += rdx();
    velocity[1] += rdx();
    velocity[2] += rdx();

    // Update position
    this->agentController->agent->setPosition(cyclone::Vector3(this->agentController->agent->getPosition() + (velocity * deltaTime)));
}

// Apply some friction to the velocity.
void AgentMovement::applyFriction(float deltaTime) {

    if (verticalInput == 0) {
        if (velocity[1] > 0) {
            velocity[1] -= VEL_FRICT * deltaTime;
            if (velocity[1] < 0) {
                velocity[1] = 0;
            }
        }

        if (velocity[1] < 0) {
            velocity[1] += VEL_FRICT * deltaTime;
            if (velocity[1] > 0) {
                velocity[1] = 0;
            }
        }
    }

}

void AgentMovement::stop() {
    velocity = cyclone::Vector3(0, 0, 0);
    rotation = cyclone::Quaternion(0, cyclone::Vector3(0, 0, 1));
}

double AgentMovement::getHorizontalInput() const {
    return horizontalInput;
}

void AgentMovement::setHorizontalInput(double horizontalInput) {
    AgentMovement::horizontalInput = horizontalInput;
}

double AgentMovement::getVerticalInput() const {
    return verticalInput;
}

void AgentMovement::setVerticalInput(double verticalInput) {
    AgentMovement::verticalInput = verticalInput;
}
