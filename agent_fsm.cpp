//
// C++ Implementation by Ajay Bhaga
//

#include "agent_fsm.h"

void AgentFSM::halt() {

    // Given the halt event, transition to a new state based upon the current state of the state machine
    BEGIN_TRANSITION_MAP
        TRANSITION_MAP_ENTRY(EVENT_IGNORED)
        TRANSITION_MAP_ENTRY(CANNOT_HAPPEN)
        TRANSITION_MAP_ENTRY(ST_STOP)
        TRANSITION_MAP_ENTRY(ST_STOP)
    END_TRANSITION_MAP(NULL)

}

void AgentFSM::setSpeed(AgentData *pData) {

    BEGIN_TRANSITION_MAP
        TRANSITION_MAP_ENTRY(ST_START)
        TRANSITION_MAP_ENTRY(CANNOT_HAPPEN)
        TRANSITION_MAP_ENTRY(ST_CHANGE_SPEED)
        TRANSITION_MAP_ENTRY(ST_CHANGE_SPEED)
    END_TRANSITION_MAP(pData)

}

// State machine sits here when agent is idle
void AgentFSM::stIdle() {

}

void AgentFSM::stStop() {

    // Perform the stop agent processing
    // Transition to ST_IDLE via an internal event
    internalEvent(ST_IDLE, NULL);
}

void AgentFSM::stStart(AgentData *) {

}

void AgentFSM::stChangeSpeed(AgentData *) {

}
