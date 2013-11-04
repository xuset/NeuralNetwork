
#ifndef COLLECTOR_H_
#define COLLECTOR_H_

#include "Coin.h"
#include "Entity.h"
#include "Rect.h"

namespace NeuralNetwork { class Chromosome; }
class Demo;

class Collector : public Entity {
	const Demo* demo;
	vector<Coin>* coins;
	NeuralNetwork::Chromosome* chromo;
	Coin* getClosestCoin();
public:
	float getFitness() { return chromo->fitness; }
	void reset();
	void doLogic();
	Collector(const Demo*, vector<Coin>*, NeuralNetwork::Chromosome*);
	~Collector() { }
};

#endif
