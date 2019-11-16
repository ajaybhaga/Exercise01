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

// Create the random number generator
static random_d rd{0.0, 1.0};

AgentController::AgentController(Agent *agent) {
    this->agent = agent;
    this->movement = new AgentMovement(this);
    this->fsm = new AgentFSM();

    int numSensors = 3;
    for (int i = 0; i < numSensors; i++) {
        Sensor *s = new Sensor();
        sensors.emplace_back(*s);
    }
}

AgentController::~AgentController() {
    if (this->agent) {
        delete[] this->agent;
    }

    if (this->movement) {
        delete[] this->movement;
    }

    if (this->fsm) {
        delete[] this->fsm;
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
        sensors[i].update();
        sensorOutput[i] = sensors[i].output;
    }

    // Process sensor inputs through ffn
    double *controlInputs = this->agent->ffn->processInputs(sensorOutput);

    std::cout << "controlInputs[0]:" << controlInputs[0] << "," << "controlInputs[1]:" << controlInputs[1] << std::endl;
    // Apply inputs to agent movement (two dimension array)
    this->movement->setInputs(controlInputs);
    this->movement->update(duration);


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
        return agent->genotype->evaluation;
    else
        return -1.0;
}

void AgentController::setCurrentCompletionReward(float reward) {
    if (agent)
        agent->genotype->evaluation = reward;
}

int AgentController::nextId() {
    return idGenerator++;
}

float AgentController::getTimeSinceLastCheckpoint() const {
    return timeSinceLastCheckpoint;
}
