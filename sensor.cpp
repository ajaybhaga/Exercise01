//
// C++ Implementation by Ajay Bhaga
//

#include "sensor.h"

Sensor::Sensor() {

}

Sensor::~Sensor() {

}

void Sensor::start() {
    show();
}

void Sensor::fixedUpdate() {

    // Calculate direction of sensor
    this->direction = this->target - this->center;
    this->direction.normalize();

    // Check distance
  /*  if (hit.collider == null) {
        hit.distance = MAX_DIST;
    } else if (hit.distance < MIN_DIST) {
        hit.distance = MIN_DIST;
    }
*/

    // Calculate hit distance
    float hitDistance = 1.0;

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