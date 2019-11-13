//
// C++ Implementation by Ajay Bhaga
//
// Modified Genetic Algorithm
// Based on design of Samuel Arzt (March 2017)
//

#include "shared_libs.h"
#include "agent_fsm.h"

class EvolutionManager;

int AgentController::idGenerator = 0;

AgentController::AgentController(Agent agent) {
    this->agent = std::make_shared<Agent>(agent);
    this->movement = std::make_shared<AgentMovement>();
    this->fsm = std::make_shared<AgentFSM>();
}

AgentController::~AgentController() {
    if (this->agent) {
        this->agent.reset();
    }

    if (this->movement) {
        this->movement.reset();
    }

    if (this->fsm) {
        this->fsm.reset();
    }
}

void AgentController::awake() {

    // Cache components
    // movement -> CarMovement
    // spriteRender
    // sensors
}

void AgentController::start() {

    // When agent controller hits wall -> die action
//    this->movement->hitWall += die;

    this->name += "Agent (";
    this->name += this->nextId();
    this->name += ")";

    auto start = std::chrono::high_resolution_clock::now();
}

void AgentController::restart() {

    timeSinceLastCheckpoint = 0;
    startTime = std::chrono::high_resolution_clock::now().time_since_epoch().count();

    for (int i = 0; i < this->sensors.size(); i++) {
        sensors[i].show();
    }

    this->agent->reset();
}

void AgentController::update(float duration) {
    timeSinceLastCheckpoint += duration;

    // Get readings from sensors
    double *sensorOutput = new double[sensors.size()];
    for (int i = 0; i < sensors.size(); i++) {
        sensorOutput[i] = sensors[i].output;
    }

    // Process sensor inputs through ffn
    double *controlInputs = this->agent->ffn->processInputs(sensorOutput);
    // Apply inputs to agent movement
    this->movement->setInputs(controlInputs);

    // Agent timed out, death by timeout
    if (timeSinceLastCheckpoint > MAX_CHECKPOINT_DELAY) {
        die();
    }
}

void AgentController::die() {

    this->movement->stop();

    for (int i = 0; i < sensors.size(); i++) {
        sensors[i].hide();
    }

    agent->kill();
}

void AgentController::checkpointCaptured() {
    timeSinceLastCheckpoint = 0;
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

float AgentController::getTimeSinceLastCheckpoint() const {
    return timeSinceLastCheckpoint;
}
