#ifndef GAME_H_
#define GAME_H_

#include <vector>
#include "SDL/SDL.h"
#include "Display.h"
#include "../NNetwork/GeneticAlg/GeneticAlg.h"
#include "Collector.h"
#include "Coin.h"

class Game {
	unsigned int ticksPerFrame;
	unsigned int ticks;
	unsigned int lastGaEpoch;
	bool stopGame;
	bool drawFrames;
	bool aKeyPressed;
	Display display;
	NeuralNetwork::GeneticAlg alg;
	vector<Collector> collectors;
	vector<Coin> coins;

	void draw();
	void doLogic();
	void loop();
	void processEvents();

public:
	const Point dimensions;
	const Rect gameBoard;
	unsigned getTicks() { return ticks; }
	const vector<Collector>& getCollectors() const { return collectors; }
	const vector<Coin>& getCoins() const { return coins; }
	const Display& getDisplay() const { return display; }
	void quit() { stopGame = true; }
	void start();
	Game();
	~Game();

};

#endif
