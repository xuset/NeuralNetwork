#include <cmath>
#include "Game.h"
#include "../NNetwork/GeneticAlg/Chromosome.h"
#include "Sprite.h"
#include "Collector.h"
#include "Util.h"

using namespace std;
using namespace NeuralNetwork;

double clampAngle(double);

Collector::Collector(const Game* g, vector<Coin>* _coins, Chromosome* _chromo) :
			Entity(Sprite::GET("collector.bmp")->image, Point(0, 0)),
			game(g),
			coins(_coins),
			chromo(_chromo) {
	angle = getRandomFloat() * 2 * PI;
}

Coin* Collector::getClosestCoin() {
	Coin* closest = 0;
	double distance = 9999999;
	for (size_t i = 0; i < coins->size(); i++) {
		Coin& c = coins->at(i);
		double d = getCenter().distance(c.getCenter());
		if (!c.found && d < distance) {
			closest = &c;
			distance = d;
		}
	}
	return closest;
}

void Collector::doLogic() {
	Coin* closest = getClosestCoin();
	if (closest == NULL)
		return;
	Point relative = (location - closest->location).normalize();

	double nnOutput[2];
	double nnInput[4];
	nnInput[0] = cos(angle);
	nnInput[1] = sin(angle);
	nnInput[2] = relative.x;
	nnInput[3] = relative.y;
	chromo->network.stimulate(nnInput, nnOutput);

	double rotForce = clampAngle(nnOutput[1] - nnOutput[0]);
	angle += rotForce;
	double moveDistance = (nnOutput[0] + nnOutput[1]);
	moveForward(moveDistance);

	//if (!game->gameBoard.isInside(getCenter()))
	//	moveForward(-1 * distance);

	if (collided(*closest)) {
		closest->found = true;
		chromo->fitness += 1.0f;
		//closest->reset(); //comment out for non respawning mines
	}
}

void Collector::reset() {
	angle = getRandomFloat() * 2 * PI;
	chromo->fitness = 1.0 / game->getCollectors().size();
	location = Point::RANDOM().scale(game->dimensions);
}

double clampAngle(double a) {
	while (a >= 2 * PI)
		a -= 2 * PI;
	while (a <= -2 * PI)
		a += 2 * PI;
	return a;
}
