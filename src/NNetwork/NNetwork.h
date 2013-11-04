#ifndef NETWORKHUB_H
	#define NETWORKHUB_H

	#include <vector>
	#include "Neuron.h"
	#include "Layer.h"
	
	namespace NeuralNetwork {
		
		class NNetwork {
			Layer inputLayer;
			int inputCount;  //number of input neurons
			int outputCount; //number of output neurons
			int layerCount;  //total number of layers
			int weightCount; //total number of weights. Includes bias

			public:

			NNetwork(const int*, int);
			NNetwork(const NNetwork&);
			void print() const;
			void stimulate(const double*, double*) const;
			std::vector<double> getWeights() const;
			void setWeights(std::vector<double>&);
			int getInputCount() const { return inputCount; }
			int getOutputCount() const { return outputCount; }
			int getLayerCount() const { return layerCount; }
			int getWeightCount() const { return weightCount; }
			void setSigmoidOutput(bool);

		};
	}
#endif
