#include <cmath>
#include "Neuron.h"

using namespace std;
using namespace NeuralNetwork;

Neuron::Neuron(int _inputs) {
	inputCount = _inputs;
	weights = new double[_inputs];
	bias = 0.0;
	sigmoidOutput = false;
}

Neuron::Neuron(const Neuron& copy) {
	inputCount = copy.inputCount;
	weights = new double[copy.inputCount];
	bias = copy.bias;
	sigmoidOutput = copy.sigmoidOutput;

	copy.getWeights(weights);
}

Neuron::~Neuron() {
	delete[] weights;
}

double Neuron::stimulate(const double inputs[]) const{
	double activation = -1 * bias;
	for (int i = 0; i < inputCount; i++) {
		activation += weights[i] * inputs[i];
	}
	return determineOutput(activation);
}

double Neuron::determineOutput(double activation) const {
	if (sigmoidOutput) {
		return ( 1 / ( 1 + exp(-activation)));
	} else {
		if (activation >= 0.0)
			return 1.0;
		return 0.0;
	}
}

void Neuron::setWeights(const double newWeights[]) { //DOES NOT INCLUDE BIAS
	for (int i = 0; i < inputCount; i++)
		weights[i] = newWeights[i];
	bias = newWeights[inputCount];
}

void Neuron::getWeights(double output[]) const { //DOES NOT INCLUDE BIAS
	for (int i = 0; i < inputCount; i++)
		output[i] = weights[i];
	output[inputCount] = bias;
}
