//
// C++ Implementation by Ajay Bhaga
//
// Modified Genetic Algorithm
// Based on design of Samuel Arzt (March 2017)
//

#include "shared_libs.h"

AgentMovement::AgentMovement() {

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
    // Nothing to do right now
    horizontalInput = 0.0f;
    verticalInput = 0.0f;
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
    bool canAccelerate = false;
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

    cyclone::Matrix4 transform = cyclone::Matrix4();
    transform.setOrientationAndPos(dirQ, this->agentController->agent->getPosition());
//    this->agentController->agent->getPosition().
    cyclone::Matrix4 position = cyclone::Matrix4();
    position.transform(this->agentController->agent->getPosition());
    position = transform * position;
    this->agentController->agent->setPosition(position.getAxisVector(2));
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