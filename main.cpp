//
// MayaBrain - built on EANN
//
// C++ Implementation by Ajay Bhaga
//
// Modified Genetic Algorithm
// Based on design of Samuel Arzt (March 2017)
//


#include <iostream>
#include "random_d.h"
#include "genotype.h"

int main() {
    std::cout << "MayaBrain" << std::endl;

    auto genotype = new Genotype();

    std::cout << "Generating random genotype..." << std::endl;
    genotype = genotype->GenerateRandom(10, 0.4, 20.4);
    genotype->OutputToConsole();
    genotype->SaveToFile("genotype01.data");
    std::cout << "Genotype saved to disk." << std::endl;

    std::cout << "Loading genotype from disk..." << std::endl;
    genotype = genotype->LoadFromFile("genotype01.data");
    std::cout << "Loaded genotype from disk." << std::endl;

    return 0;
}