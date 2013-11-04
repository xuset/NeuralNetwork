#include <algorithm>
#include <iostream>
#include "GeneticAlg.h"

using namespace std;
using namespace NeuralNetwork;

void randomizeVector(vector<double>&);

GeneticAlg::GeneticAlg(const NNetwork& hub, int populationSize) {
	crossOverRate = 0.7f;
	mutationRate = 0.1f;
	maxPerturbation = 0.3f;
	eliteCopies = 1;

	srand(time(0));

	for (int i = 0; i < populationSize; i++)
		population.push_back(Chromosome(hub));

	reset();
}

int GeneticAlg::start(int maxGenerations) {
	reset();

	for (int i = 0; i < maxGenerations; i++) {
		if (epoch())
			return i;
	}
	return -1;
}

bool GeneticAlg::epoch() {

	vector< vector<double> > temp;

	for (int i = 0; i < eliteCopies; i++)
		temp.push_back(bestChromo->getWeights());

	while (temp.size() < population.size()) {
		Chromosome& parent1 = grabChromo();
		Chromosome& parent2 = grabChromo();

		vector<double> child1, child2;
		cross(parent1.getWeights(), parent2.getWeights(), child1, child2);
		mutate(child1);
		mutate(child2);

		temp.push_back(child1);
		temp.push_back(child2);
	}

	for (unsigned int i = 0; i < population.size(); i++) {
		Chromosome& c = population[i];
		c.setWeights(temp[i]);
		c.fitness = determineFitness(c);
	}

	bool solutionFound = calculateStats();
	generation++;
	postEpoch();
	return solutionFound;

}

bool GeneticAlg::calculateStats() {
	double minF = population[0].fitness;
	double maxF = population[0].fitness;
	double summed = 0.0;
	bool foundSolution = false;
	Chromosome* best = &population[0];

	for (unsigned int i = 0; i < population.size(); i++) {
		Chromosome& c = population[i];

		summed += c.fitness;
		if (c.fitness < minF)
			minF = c.fitness;
		if (c.fitness > maxF)
			maxF = c.fitness;

		if (c.fitness > best->fitness)
			best = &c;

		if (isSolution(c))
			foundSolution =  true;
	}
	minFitness = minF;
	maxFitness = maxF;
	avgFitness = summed / population.size();
	fitnessSum = summed;
	bestChromo = best;

	return foundSolution;
}

Chromosome& GeneticAlg::grabChromo() {
	double slice = (double)(randomFloat() * fitnessSum);
	double summedFitness = 0;
	for (unsigned int i=0; i<population.size(); i++) {
		summedFitness += population[i].fitness;
		if (summedFitness >= slice)
			return population[i];
	}
	return population.back();
}

void GeneticAlg::mutate(vector<double>& chromo) {
	for (unsigned int i = 0; i < chromo.size(); i++) {
		if (randomFloat() < mutationRate) {
			chromo[i] += randomClamped() * maxPerturbation;
		}
	}
}

void GeneticAlg::cross(const vector<double>& p1, const vector<double>& p2, vector<double>& c1, vector<double>& c2) {
	if ((randomFloat() > crossOverRate) || (p1 == p2)) {
			c1 = p1;
			c2 = p2;
			return;
	}

	int point = randomRange(0, p1.size() - 1);
	for (int i = 0; i < point; i++) {
		c1.push_back(p1[i]);
		c2.push_back(p2[i]);
	}

	for (unsigned int i = point; i < p1.size(); i++) {
		c1.push_back(p2[i]);
		c2.push_back(p1[i]);
	}
}

float GeneticAlg::determineFitness(Chromosome& c) {
	return c.fitness;
}

bool GeneticAlg::isSolution(Chromosome& c) {
	return false;
}

void randomizeVector(vector<double>& v) {
	for (unsigned int i = 0; i < v.size(); i++) {
		v[i] = randomClamped();
	}
}

void GeneticAlg::randomizePopulation() {
	for (unsigned int i = 0; i < population.size(); i++) {
		Chromosome& c = population[i];
		vector<double> newGenes = c.getWeights();
		randomizeVector(newGenes);
		c.setWeights(newGenes);
		c.fitness = determineFitness(c);
	}
	calculateStats();
}

void GeneticAlg::reset() {
	bestChromo = 0;
	generation = 0;
	fitnessSum = 0.0;
	maxFitness = 0.0;
	minFitness = 0.0;
	avgFitness = 0.0;
	randomizePopulation();
}
