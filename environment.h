//
// Created by Bad Zindagi on 2019-11-08.
//

#ifndef EANN_SIMPLE_ENVIRONMENT_H
#define EANN_SIMPLE_ENVIRONMENT_H

#include <cyclone/cyclone.h>
#include "gl/ogl_headers.h"
#include "../app.h"
#include "cyclone/timing.h"
#include "block.h"

// MunvoAgentSim shared libs
#include "shared_libs.h"

/**
 * The main demo class definition.
 */
class Environment : public Application
{
private:
    /** Tracks if a block has been hit. */
    bool hit;
    unsigned fracture_contact;

    /** Handle random numbers. */
    cyclone::Random random;

    /** Holds the bodies. */
    Block blocks[MAX_BLOCKS];

    /** Holds the agent collision sphere. */
    std::vector<cyclone::CollisionSphere> agentCollSpheres;

    /** Processes the contact generation code. */
    virtual void generateContacts();

    /** Processes the objects in the simulation forward in time. */
    virtual void updateObjects(cyclone::real duration);

    /** Resets the position of all the blocks. */
    virtual void reset();

    /** Processes the physics. */
    virtual void update();

    void showText();

public:
    /** Creates a new demo object. */
    Environment();

    /** Returns the window title for the demo. */
    virtual const char* getTitle();

    /** Display the particle positions. */
    virtual void display();
};

#endif //EANN_SIMPLE_ENVIRONMENT_H
