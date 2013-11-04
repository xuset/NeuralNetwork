#include <vector>
#include <iostream>
#include "NNetwork.h"

using namespace std;
using namespace NeuralNetwork;

int numOfWeights(const int neurons[], int layers);

int numOfWeights(const int neurons[], int layers) {
	int weights = neurons[0] * 2;
	for (int i = 1; i < layers; i++) {
		weights += (1 + neurons[i -1]) * neurons[i];
			// (bias + inputs) * numOfNeuronsInLayer
	}
	return weights;
}

NNetwork::NNetwork(const int neuronLayers[], int layers) :
		inputLayer(neuronLayers, layers),
		inputCount(neuronLayers[0]),
		outputCount(neuronLayers[layers - 1]),
		layerCount(layers),
		weightCount(numOfWeights(neuronLayers, layers)) {
}

NNetwork::NNetwork(const NNetwork& nn) :
		inputLayer(nn.inputLayer),
		inputCount(nn.inputCount),
		outputCount(nn.outputCount),
		layerCount(nn.layerCount),
		weightCount(nn.weightCount) {

}

void NNetwork::stimulate(const double input[], double output[]) const {
	inputLayer.stimulate(input, output);
}

vector<double> NNetwork::getWeights() const {
	vector<double> weights;

	const Layer* layer = &inputLayer;
	do {
		for (int n = 0; n < layer->getNeuronCount(); n++) {
			const Neuron& neuron = layer->getNeuron(n);
			double temp[neuron.getInputCount()];
			neuron.getWeights(temp);
			for (int w = 0; w < neuron.getInputCount(); w++)
				weights.push_back(temp[w]);
		}
		layer = layer->getNextLayer();
	} while (layer != 0);

	return weights;
}

void NNetwork::setWeights(vector<double>& weights) {
	int count = 0;
	Layer* layer = &inputLayer;
	do {
		for (int n = 0; n < layer->getNeuronCount(); n++) {
			Neuron& neuron = layer->getNeuron(n);
			double temp[neuron.getInputCount()];
			for (int w = 0; w < neuron.getInputCount(); w++)
				temp[w] = weights[count++];
			neuron.setWeights(temp);
		}
		layer = layer->getNextLayer();
	} while (layer != 0);
	//print();
}

void NNetwork::print() const {
	const Layer* layer = &inputLayer;
	int l = 0;
	do {
		std::cout << "Layer " << l << "\n";
		for (int n = 0; n < layer->getNeuronCount(); n++) {
			std::cout << "	Neuron " << n << "\n";
			const Neuron& neuron = layer->getNeuron(n);
			double temp[neuron.getInputCount()];
			neuron.getWeights(temp);
			for (int w = 0; w < neuron.getInputCount(); w++) {
				std::cout << "		Weight " << w << " = " << temp[w] << "\n";
			}
			//std::cout << "		bias = " << neuron.bias << "\n";
		}

		l++;
		layer = layer->getNextLayer();
	} while (layer != 0);
}

void NNetwork::setSigmoidOutput(bool useSigmoid) {

	Layer* layer = &inputLayer;
	do {
		if (layer->getNextLayer() == 0) {
			for (int n = 0; n < layer->getNeuronCount(); n++) {
				Neuron& neuron = layer->getNeuron(n);
				neuron.sigmoidOutput = useSigmoid;
			}
		}
		layer = layer->getNextLayer();
	} while (layer != 0);
}
