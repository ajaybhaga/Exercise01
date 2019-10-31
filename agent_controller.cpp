//
// C++ Implementation by Ajay Bhaga
//
// Modified Genetic Algorithm
// Based on design of Samuel Arzt (March 2017)
//

#include "agent_controller.h"

AgentController::AgentController(Agent agent) {
    //this->agent = std::make_unique<Agent>(agent);//agent->genotype, );
//    std::unique_ptr<EventHandler>(new EventHandler{handler})
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
    if (agent)
        return agent->genotype.evaluation;
    else
        return -1.0;
}

void AgentController::setCurrentCompletionReward(float reward) {
    if (agent)
        agent->genotype.evaluation = reward;
}
