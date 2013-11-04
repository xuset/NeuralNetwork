
#ifndef COLLECTOR_H_
#define COLLECTOR_H_

#include "Coin.h"
#include "Entity.h"
#include "Rect.h"

namespace NeuralNetwork { class Chromosome; }
class Game;

class Collector : public Entity {
	const Game* game;
	vector<Coin>* coins;
	NeuralNetwork::Chromosome* chromo;
	Coin* getClosestCoin();
public:
	float getFitness() { return chromo->fitness; }
	void reset();
	void doLogic();
	Collector(const Game*, vector<Coin>*, NeuralNetwork::Chromosome*);
	~Collector() { }
};

#endif
