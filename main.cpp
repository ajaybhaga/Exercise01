//
// MayaBrain - built on EANN
//
// C++ Implementation by Ajay Bhaga
//
// Modified Genetic Algorithm
// Based on design of Samuel Arzt (March 2017)
//

#include "shared_libs.h"

EvolutionManager *EvolutionManager::instance = 0;

int main() {
    std::cout << "MayaBrain" << std::endl;

    std::cout << "Evolution Manager -> starting..." << std::endl;
    EvolutionManager::getInstance()->startEvolution();

    // Test Case 1
    auto genotype = new Genotype();
    std::cout << "Generating random genotype..." << std::endl;
    genotype = genotype->generateRandom(10, 0.4, 20.4);
    genotype->outputToConsole();
    genotype->saveToFile("genotype01.data");
    std::cout << "Genotype saved to disk." << std::endl;

    std::cout << "Loading genotype from disk..." << std::endl;
    genotype = genotype->loadFromFile("genotype01.data");
    std::cout << "Loaded genotype from disk." << std::endl;

    return 0;
}