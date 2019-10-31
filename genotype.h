//
// Genotype represents one member of population
//
//
// C++ Implementation by Ajay Bhaga
//
// Modified Genetic Algorithm
// Based on design of Samuel Arzt (March 2017)
//


#ifndef EANN_SIMPLE_GENOTYPE_H
#define EANN_SIMPLE_GENOTYPE_H

#include <string>
#include <iostream>
#include <string>
#include <cassert>
#include <fstream>      // std::ifstream, std::ofstream
#include "random_d.h"

#define TRAINING_DATA_DIR "data/"

class Genotype {
public:

    Genotype();
    Genotype(float *parameters, int parameterCount);
    ~Genotype();
    void setRandomParameters(float minValue, float maxValue);
    float* getParameterCopy();
    void saveToFile(const char *filePath);
    Genotype *loadFromFile(const char *filePath);
    float getParameter(int index);
    void setParameter(int index, float value);
    Genotype *generateRandom(int parameterCount, float minValue, float maxValue);
    void outputToConsole();

    float evaluation;
    float fitness;
    int parameterCount;

private:
    float* parameters;
};


struct genotype_record
{
    std::string agentName;
    float evaluation;
    float fitness;
    int parameterCount;
    float* parameters;
};

class GenotypeFile {
public:
    genotype_record record;
};

#endif //EANN_SIMPLE_GENOTYPE_H
