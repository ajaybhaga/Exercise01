//
// Genotype represents one member of population
//

#ifndef EANN_SIMPLE_GENOTYPE_H
#define EANN_SIMPLE_GENOTYPE_H

class Genotype {
public:

    Genotype();
    Genotype(float* parameters, int parameterCount);
    ~Genotype();
    void SetRandomParameters(float minValue, float maxValue);
    float* GetParameterCopy();
    void SaveToFile(const char* filePath);
    Genotype* LoadFromFile(const char* filePath);
    float getParameter(int index);
    Genotype* GenerateRandom(int parameterCount, float minValue, float maxValue);
    void OutputToConsole();

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
