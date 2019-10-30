//
// C++ Implementation by Ajay Bhaga
//
// Modified Genetic Algorithm
// Based on design of Samuel Arzt (March 2017)
//

#include "agent_controller.h"

AgentController::AgentController() {

}

AgentController::~AgentController() {

}

void AgentController::awake() {

}

void AgentController::start() {

}

void AgentController::restart() {

}

void AgentController::update() {

}

void AgentController::fixedUpdate() {

}

void AgentController::die() {

}

void AgentController::checkpointCaptured() {

}

float AgentController::getCurrentCompletionReward() {
    return agent.genotype.evaluation;
}

void AgentController::setCurrentCompletionReward(float reward) {
    agent.genotype.evaluation = reward;
}
