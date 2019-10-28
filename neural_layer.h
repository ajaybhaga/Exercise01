//
// C++ Implementation by Ajay Bhaga
//
// Modified Genetic Algorithm
// Based on design of Samuel Arzt (March 2017)
//

#ifndef EANN_SIMPLE_NEURAL_LAYER_H
#define EANN_SIMPLE_NEURAL_LAYER_H

#include "random_d.h"

#include <string>
#include "math_helper.h"

class NeuralLayer {
public:

    NeuralLayer(int nodeCount, int outputCount);
    ~NeuralLayer();

    void setWeights(double *weights);
    double *processInputs(double *inputs);
    NeuralLayer deepCopy();
    void setRandomWeights(double minValue, double maxValue);
    std::string toString();

    // Function to activation function of artificial neuron.
    typedef std::function<double (double xValue)> ActivationFunction;

    // Operators
    ActivationFunction neuronActivationFunction = MathHelper::sigmoidFunction;

    // The amount of neurons in this layer.
    int neuronCount;

    // The amount of neurons this layer is connected to, i.e. the amount of neurons of the next layer.
    int outputCount;

    // The weights of the connections of this layer to the next layer.
    // e.g. weight [i, j] is the weight of the connection from the i-th weight of this layer to the
    // j-th weight of the next layer.
    double **weights;


private:
};

#endif //EANN_SIMPLE_NEURAL_LAYER_H
