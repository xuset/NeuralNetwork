#include "Layer.h"

using namespace std;
using namespace NeuralNetwork;

Layer* copyNextLayer(const Layer& copy);

Layer* copyNextLayer(const Layer& copy) {
	if (copy.getNextLayer() != 0)
		return new Layer(*copy.getNextLayer());
	else
		return 0;
}

Layer* Layer::setNextLayer(const int neuronLayers[], int layers) {

	if (layers > 1) {
		int shiftedDown[layers - 1];
		for (int i = 1; i < layers; i++)
			shiftedDown[i - 1] = neuronLayers[i];
		return new Layer(shiftedDown, layers - 1, this);
	}
	return 0;
}

void Layer::allocateNeurons(Layer* previous) {
	int inputs = 1;
	if (previous != 0)
		inputs = previous->neuronCount;

	for (int i = 0; i < neuronCount; i++) {
		neurons.push_back(Neuron(inputs));
	}
}

Layer::Layer(const int neuronLayers[], int layers, Layer* previous) :
		neuronCount(neuronLayers[0]),
		next(setNextLayer(neuronLayers, layers)) {
	allocateNeurons(previous);
}

Layer::Layer(const int neuronLayers[], int layers) :
		neuronCount(neuronLayers[0]),
		next(setNextLayer(neuronLayers, layers)) {

	allocateNeurons(0);
}

Layer::Layer(const Layer& copy) :
		neuronCount(copy.neuronCount),
		next(copyNextLayer(copy)){
	for (int n = 0; n < neuronCount; n++) {
		neurons.push_back(copy.neurons.at(n));
	}
}

void Layer::stimulate(const double inputs[], double output[]) const {
	double layerOutput[neuronCount];


	for (int n = 0; n < neuronCount; n++) {
		layerOutput[n] = neurons.at(n).stimulate(inputs + n);
	}

	if (next != 0)
		return next->feedForwardStimulate(layerOutput, output);

	//if there are no more layers to stimulate, fill the output array
	for (int n = 0; n < neuronCount; n++) {
		output[n] = layerOutput[n];
	}
}

void Layer::feedForwardStimulate(const double inputs[], double output[]) const {
	double layerOutput[neuronCount];

	for (int n = 0; n < neuronCount; n++)
		layerOutput[n] = neurons.at(n).stimulate(inputs);

	if (next != 0)
		return next->stimulate(layerOutput, output);

	//if there are no more layers to stimulate, fill the output array
	for (int n = 0; n < neuronCount; n++) {
		output[n] = layerOutput[n];
	}
}

Layer::~Layer() {
	delete next;
}
