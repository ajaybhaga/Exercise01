//
// C++ Implementation by Ajay Bhaga
//
// Modified Genetic Algorithm
// Based on design of Samuel Arzt (March 2017)
//

#include "shared_libs.h"

int AgentController::idGenerator = 0;

AgentController::AgentController(Agent agent) {
    this->agent = std::make_shared<Agent>(agent);
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

    auto start = std::chrono::high_resolution_clock::now();
}

void AgentController::restart() {

    // movement enabled
    timeSinceLastCheckpoint = 0;
    startTime = std::chrono::high_resolution_clock::now().time_since_epoch().count();

    for (int i = 0; i < this->sensors.size(); i++) {
        sensors[i].show();
    }


}

void AgentController::update() {
    long currTime = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    long deltaTime = currTime-startTime;
//    std::this_thread::sleep_for(2s);
//    auto end = std::chrono::high_resolution_clock::now();
//    std::chrono::duration<double, std::milli> elapsed = end-start;
    std::cout << "Delta time: " << deltaTime << " ms\n";

    timeSinceLastCheckpoint += deltaTime;
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
