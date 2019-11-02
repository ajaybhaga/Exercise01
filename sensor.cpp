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
   // Vector2 direction = Cross.tranform.position - this.transform.position;
   // direction.Normalize();

    // Check distance
  /*  if (hit.collider == null) {
        hit.distance = MAX_DIST;
    } else if (hit.distance < MIN_DIST) {
        hit.distance = MIN_DIST;
    }
*/
    // Transform to percent of max distance
//    this->output = hit.distance;

    // Set position of visual cross
    // cross.transform.position = (Vector2) this->transform.position + direction * hit.distance;

}

// Hides the visual representation of the sensor
void Sensor::hide() {


}

// Shows the visual representation of the sensor
void Sensor::show() {

}