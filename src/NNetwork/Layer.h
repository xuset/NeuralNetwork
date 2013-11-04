#ifndef LAYER_H
	#define LAYER_H

	#include <vector>
	#include "Neuron.h"

	namespace NeuralNetwork {

		class Layer {
			std::vector<Neuron> neurons;
			int neuronCount;
			Layer* next;
			Layer(const int*, int, Layer*);
			void allocateNeurons(Layer*);
			Layer* setNextLayer(const int*, int);
			void feedForwardStimulate(const double*, double*) const;

		public:

			Layer(const int*, int);
			Layer(const Layer&);
			void stimulate(const double*, double*) const;
			~Layer();
			int getNeuronCount() const { return neuronCount; }
			const Neuron& getNeuron(int index) const { return neurons[index]; }
			Neuron& getNeuron(int index) { return neurons[index]; }
			Layer* getNextLayer() { return next; }
			const Layer* getNextLayer() const { return next; }
		};

	}

#endif
