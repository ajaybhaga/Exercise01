//
// C++ Implementation by Ajay Bhaga
//
// Modified Genetic Algorithm
// Based on design of Samuel Arzt (March 2017)
//

#include "shared_libs.h"

int AgentController::idGenerator = 0;

AgentController::AgentController(Agent agent) {
    //this->agent = std::make_unique<Agent>(agent);//agent->genotype, );
//    std::unique_ptr<EventHandler>(new EventHandler{handler})
}

AgentController::~AgentController() {

}

void AgentController::awake() {

    // Cache components
    // movement -> CarMovement
    // spriteRender
    // sensors
}

void AgentController::start() {

    // movement.hitWall += die

    this->name += "Agent (";
    this->name += this->nextId();
    this->name += ")";
}

void AgentController::restart() {

    // movement enabled
    timeSinceLastCheckpoint = 0;



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
    if (agent)
        return agent->genotype.evaluation;
    else
        return -1.0;
}

void AgentController::setCurrentCompletionReward(float reward) {
    if (agent)
        agent->genotype.evaluation = reward;
}

int AgentController::nextId() {
    return idGenerator++;
}
