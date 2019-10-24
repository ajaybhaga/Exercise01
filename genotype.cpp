//
// Genotype represents one member of population
//

#include <iostream>
#include <string>
#include <cassert>
#include <fstream>      // std::ifstream, std::ofstream
#include <stdlib.h>     /* atoi */
#include <stdio.h>
#include <cstring>

#include "genotype.h"
#include "random_d.h"

Genotype::Genotype() {
    parameterCount = 0;
}

Genotype::Genotype(float* parameters, int parameterCount) {

    this->parameters = parameters;
    if (!parameters) {
        this->parameterCount = 0;
    } else {
        this->parameterCount = parameterCount;

//        parameterCount  = sizeof(parameters)/sizeof(parameters[0]);
//        parameterCount  = sizeof(parameters)/sizeof(parameters[0]);


    }
    fitness = 0;
}

Genotype::~Genotype() {

    // Deallocate Heap memory
    delete[] parameters;
}

void Genotype::SetRandomParameters(float minValue, float maxValue) {
    assert(minValue < maxValue);

    // create the random number generator:
    random_d rd{minValue, maxValue};

    // Generate random parameter vector
    float range = maxValue - minValue;
    for (int i = 0; i < parameterCount; i++) {
        parameters[i] = rd();
    }
}

float* Genotype::GetParameterCopy() {

    float* copy = new float[parameterCount];
    for (int i = 0; i < parameterCount; i++) {
        copy[i] = parameters[i];
    }

    return copy;
}

void Genotype::SaveToFile(const char* filePath) {

        std::string dirPath = "C:\\dev\\git\\trainingData\\";
        std::string fullPath = dirPath + filePath;

        GenotypeFile *file = new GenotypeFile();

        file->record.agentName = "agent01";
        file->record.evaluation = 2.3;
        file->record.fitness = 1.5;
        file->record.parameterCount = 5;
        file->record.parameters = new float[5];
        file->record.parameters[0] = file->record.parameters[1] = file->record.parameters[2] = file->record.parameters[3] = file->record.parameters[4] = 0.1;

        std::ofstream outfile(fullPath, std::ios::binary);
        outfile.write(reinterpret_cast<char*>(&file->record), sizeof(file->record));

        std::cout << "Writing file: " << std::endl;
        std::cout << "[agentName: "
                  << file->record.agentName
                  << ", evaluation: "
                  <<  file->record.evaluation
                  << ", fitness: "
                  << file->record.fitness
                  << ", parameterCount: "
                  << file->record.parameterCount
                  << ", parameters: "
                  << file->record.parameters
                  << "]" << std::endl;

        std::cout << "Genotype record has been successfully saved." << std::endl;
}

Genotype* Genotype::LoadFromFile(const char* filePath) {
    std::string dirPath = "C:\\dev\\git\\trainingData\\";
    std::string fullPath = dirPath + filePath;
    std::ifstream dimensionsInFile;

    GenotypeFile *file = new GenotypeFile();

    // Read struct data from file
    std::ifstream infile(fullPath, std::ios::binary);
    infile.read( reinterpret_cast<char*>(&file->record), sizeof(file->record));

    std::cout << "Loading file: " << std::endl;
    std::cout << "[agentName: "
        << file->record.agentName
            << ", evaluation: "
            <<  file->record.evaluation
            << ", fitness: "
            << file->record.fitness
            << ", parameterCount: "
            << file->record.parameterCount
            << ", parameters: "
            << file->record.parameters
            << "]" << std::endl;

    std::cout <<  "Genotype has been successfully loaded." << std::endl;
    dimensionsInFile.close();
}

float Genotype::getParameter(int index) {
    if (parameters) {
        return parameters[index];
    } else {
        return -1;
    }
}

Genotype* Genotype::GenerateRandom(int parameterCount, float minValue, float maxValue) {

    if (parameterCount == 0) {
        return new Genotype(new float[0], 0);
    }

    Genotype* randomGenotype = new Genotype(new float[parameterCount], parameterCount);
    randomGenotype->SetRandomParameters(minValue, maxValue);
    return randomGenotype;
}

void Genotype::OutputToConsole() {
    for (int i = 0; i < parameterCount; i++) {
        std::cout << "parameters[" << i << "] -> " << parameters[i] << std::endl;
    }
}