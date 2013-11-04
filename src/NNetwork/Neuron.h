
#ifndef NEURON_H
	#define NEURON_H

	#include <vector>

	namespace NeuralNetwork {

		class Neuron {
			double determineOutput(double) const;
			int inputCount;
			double* weights;
			double bias;

			public:
			bool sigmoidOutput;
	
			Neuron(int);
			Neuron(const Neuron&);
			~Neuron();
			double stimulate(const double*) const;
			void getWeights(double*) const;
			void setWeights(const double*);
			int getInputCount() const { return inputCount + 1; }
	
		};
	}

#endif
