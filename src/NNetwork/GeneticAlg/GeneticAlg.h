
#ifndef NEURALGENETIC_H
	#define NEURALGENETIC_H

	#include <vector>
	#include <math.h>
	#include <time.h>
	#include <stdlib.h>
	#include "../NNetwork.h"
	#include "Chromosome.h"

	namespace NeuralNetwork {

		inline double randomFloat() { return rand() /( RAND_MAX + 1.0); }
		inline double randomClamped() { return randomFloat() - randomFloat(); }
		inline int randomRange(int a, int b) { return rand() % (b - a + 1) + a; }
		//returns an integer between a and b inclusively

		class GeneticAlg {
			Chromosome* bestChromo;
			double fitnessSum;
			double minFitness;
			double avgFitness;
			double maxFitness;
			int generation;

			bool calculateStats();

		protected:
			std::vector<Chromosome> population;

			double getFitnessSum() { return fitnessSum; }
			virtual void postEpoch() { };
			virtual bool isSolution(Chromosome&);
			virtual Chromosome& grabChromo();
			virtual float determineFitness(Chromosome& c);
			virtual void mutate(std::vector<double>&);
			virtual void cross(const std::vector<double>&, const std::vector<double>&,
					std::vector<double>&, std::vector<double>&);

		public:
			float mutationRate;
			float crossOverRate;
			float maxPerturbation;
			int eliteCopies;

			GeneticAlg(const NNetwork& hub, int);
			virtual ~GeneticAlg() { }
			void reset();
			void reset(const NNetwork&);
			int start(int);
			bool epoch();
			virtual void randomizePopulation();
			int getGeneration()    const { return generation; }
			double getMinFitness() const { return minFitness; }
			double getMaxFitness() const { return maxFitness; }
			double getAvgFitness() const { return avgFitness; }
			Chromosome* getMostFit() const   { return bestChromo; }
			Chromosome& getChromo(int index) { return population.at(index); }
			size_t getPopulationSize() const    { return population.size(); }
			const Chromosome& getChromo(int index) const { return population.at(index); }
		};

	}

#endif
