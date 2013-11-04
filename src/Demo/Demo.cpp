#include <iostream>
#include "SDL/SDL.h"
#include "Demo.h"
#include "Sprite.h"
#include "Point.h"
#include "../NNetwork/GeneticAlg/Chromosome.h"
#include "../NNetwork/GeneticAlg/GeneticAlg.h"

using namespace NeuralNetwork;

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define MAX_COLLECTORS 30
#define MAX_COINS 40
#define TICKS_PER_GA_EPOCH 500
#define INITIAL_FPS 20

static GeneticAlg& createGA();

Demo::Demo() :
		display(SCREEN_WIDTH, SCREEN_HEIGHT),
		alg(createGA()),
		dimensions(SCREEN_WIDTH, SCREEN_HEIGHT),
		board(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT) {

	if (display.getInitErrCode() == 1)
		exit(1);

	alg.reset();
	ticksPerFrame = 1;
	aKeyPressed = false;
	drawFrames = true;
	stopDemo = false;
	ticks = 0;
	lastGaEpoch = 0;
	Sprite::ADD("collector.bmp");
	Sprite::ADD("coin.bmp");

	for (size_t i = 0; i < MAX_COLLECTORS; i++) {
		NeuralNetwork::Chromosome* chromo = &alg.getChromo(i);
		collectors.push_back(Collector(this, &coins, chromo));
	}

	for (size_t i = 0; i < MAX_COINS; i++)
		coins.push_back(Coin(dimensions));
}

void Demo::start() {
	lastGaEpoch = 0;
	ticks = 0;
	stopDemo = false;
	drawFrames = true;

	for (size_t i = 0; i < collectors.size(); i++)
		collectors[i].reset();
	for (size_t i = 0; i < coins.size(); i++)
		coins[i].reset();

	loop();
}

void Demo::loop() {
	unsigned int nextDrawTick = 0;
	while (!stopDemo) {
		processEvents();
		doLogic();
		if (drawFrames && nextDrawTick < ticks) {
			draw();
			nextDrawTick += ticksPerFrame;
			SDL_Delay(10);
		}
		ticks++;
	}
}

void Demo::processEvents() {
	SDL_Event event;
	while(SDL_PollEvent(&event)) {
		switch(event.type) {
		case SDL_QUIT:
			stopDemo = true;
			break;
		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_a && !aKeyPressed) {
				aKeyPressed = true;
				drawFrames = !drawFrames;
			}
			break;
		case SDL_KEYUP:
			if (event.key.keysym.sym == SDLK_a)
				aKeyPressed = false;
			break;
		}
	}
}

void Demo::draw() {
	display.clear();

	for (size_t i = 0; i < collectors.size(); i++)
		collectors[i].draw(display);
	for (size_t i = 0; i < coins.size(); i++)
		coins[i].draw(display);

	display.flip();
}

void Demo::doLogic() {
	for (size_t i = 0; i < collectors.size(); i++) {
		collectors[i].doLogic();
	}

	if (lastGaEpoch + TICKS_PER_GA_EPOCH < ticks ) {
		alg.epoch();
		cout << "Generation: " << alg.getGeneration() << "\n";
		cout << "Average fitness: " << alg.getAvgFitness() <<
				" Max fitness: " << alg.getMaxFitness() << "\n";

		for (size_t i = 0; i < collectors.size(); i++)
			collectors[i].reset();
		for (size_t i = 0; i < coins.size(); i++)
			coins[i].reset();

		lastGaEpoch = ticks;
	}
}

Demo::~Demo() {
	Sprite::DESTROY_ALL();
	delete Sprite::sprites;
}

#define MUTATION_RATE 0.3f
#define CROSS_OVER_RATE 0.8f
#define PERTURBATION_RATE 0.3f
#define ELITE_COPIES 2

GeneticAlg& createGA() {
	int layers[] = { 4, 10, 10, 2 };
	int depth = sizeof(layers) / sizeof(int);
	NNetwork nn(layers, depth);
	nn.setSigmoidOutput(true);
	GeneticAlg* alg = new GeneticAlg(nn, MAX_COLLECTORS);
	alg->crossOverRate = CROSS_OVER_RATE;
	alg->mutationRate = MUTATION_RATE;
	alg->maxPerturbation = PERTURBATION_RATE;
	alg->eliteCopies = ELITE_COPIES;
	alg->reset();
	return *alg;
}
