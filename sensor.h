//
// C++ Implementation by Ajay Bhaga
//

#ifndef EANN_SIMPLE_SENSOR_H
#define EANN_SIMPLE_SENSOR_H

#include <string>
#include <stdlib.h>     /* abs */
#include "math_helper.h"
#include "random_d.h"

// Class representing a sensor reading the distance to the nearest obstacle in a specified direction.
class Sensor {
public:
    Sensor();
    Sensor(int nodeCount, int outputCount);
    ~Sensor();

    void start();
    void fixedUpdate();
    void hide();
    void show();

    // The current sensor readings in percent of maximum distance.
    float output;

private:

    const float MAX_DIST = 10.0f;
    const float MIN_DIST = 0.01f;


};

#endif //EANN_SIMPLE_SENSOR_H