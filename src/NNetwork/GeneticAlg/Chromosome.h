
#ifndef CHROMOSOME_H
	#define CHROMOSOME_H

	#include <vector>
	#include "../NNetwork.h"

	namespace NeuralNetwork {

		class Chromosome {
		public:
			NNetwork network;
			float fitness;

			Chromosome(const NNetwork& _network) : network(_network), fitness(0.0) { }
			std::vector<double> getWeights() const { return network.getWeights(); }
			void setWeights(std::vector<double>& weights) { network.setWeights(weights); }
			friend bool operator<(const Chromosome& lhs, const Chromosome& rhs) {
				return (lhs.fitness < rhs.fitness);
			}
		};
	}



#endif
