//
// C++ Implementation by Ajay Bhaga
//

#include "sensor.h"
#include "evolution_manager.h"

// TODO: Add sensor types (multiple types can diversify the mutation process).

Sensor::Sensor() {
    this->center = cyclone::Vector3(0.0, 0.0, 0.0);
    this->target = cyclone::Vector3(0.0, -1.0, 0.0);
}

Sensor::~Sensor() {

}

void Sensor::start() {
    show();
}

void Sensor::update() {


    std::vector<Agent*> agents = EvolutionManager::getInstance()->getAgents();
    std::vector<AgentController*> controllers = EvolutionManager::getInstance()->getAgentControllers();

    // Calculate direction of sensor
    this->direction = this->target - this->center;
    this->direction.normalize();

    // Calculate hit distance
    float hitDistance = 0.0;

    cyclone::CollisionSphere sphere = cyclone::CollisionSphere();
    sphere.body = new cyclone::RigidBody();
    sphere.body->setPosition(this->center);
    sphere.radius = (this->target-this->center).magnitude();

    cyclone::CollisionSphere sphereB = cyclone::CollisionSphere();
    sphereB.body = new cyclone::RigidBody();
    for (int i = 0; i < agents.size(); i++) {
        sphereB.body->setPosition(agents[i]->getPosition());
        sphereB.radius = 1.0f;

        if (cyclone::IntersectionTests::sphereAndSphere(sphere, sphereB)) {
            // Hit another agent
            hitDistance = (sphere.body->getPosition()-sphereB.body->getPosition()).magnitude();
        }
    }

    /*
    // Send raycast into direction of sensor
    cyclone::CollisionPlane plane = cyclone::CollisionPlane();
    plane.direction = cyclone::Vector3(0.0, 1.0f, 0.0);
    plane.offset = -100.0;


    if (cyclone::IntersectionTests::sphereAndHalfSpace(sphere, plane)) {
        hitDistance = sphere.radius;
    }*/

    if (hitDistance < MIN_DIST) {
        hitDistance = MIN_DIST;
    }

    // Transform to percent of max distance
    this->output = hitDistance;

    // Set position of sensor target
    this->target = this->center + (this->direction * hitDistance);
}

// Hides the visual representation of the sensor
void Sensor::hide() {
    visibility = false;
}

// Shows the visual representation of the sensor
void Sensor::show() {
    visibility = true;
}