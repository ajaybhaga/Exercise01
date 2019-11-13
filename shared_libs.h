//
// C++ Implementation by Ajay Bhaga
//

#ifndef EANN_SIMPLE_SHARED_LIBS_H
#define EANN_SIMPLE_SHARED_LIBS_H

#include <string>
#include <list>
#include <iostream>
#include <fstream>
#include <ctime>
#include <filesystem>
#include <functional>
#include <string>
#include <map>
#include <chrono> // std::chrono::microseconds
#include <thread> // std::this_thread::sleep_for
#include <vector>
#include <cassert>

#include <stdlib.h>     /* atoi */
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <cyclone.h>

#include "random_d.h"
#include "event.h"
#include "genotype.h"
#include "neural_layer.h"
#include "genetic_algorithm.h"
#include "neural_network.h"
#include "sensor.h"
#include "agent.h"
//#include "agent_movement.h"
//#include "agent_controller.h"
#include "evolution_manager.h"

//#include "evolution_manager.h"

// Config variables
#define TRAINING_DATA_DIR "data/"
#define NUM_NEURAL_LAYERS 4

// Get current date/time, format is YYYY-MM-DD.HH:mm:ss
static const std::string currentDateTime() {
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    // Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
    // for more information about date/time format
    strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

    return buf;
}

#endif //EANN_SIMPLE_SHARED_LIBS_H
