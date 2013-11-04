#ifndef COIN_H_
#define COIN_H_

#include "Entity.h"

class Coin : public Entity{
	Point gameDimensions;
public:
	bool found;

	void reset();
	Coin(const Point&);
	void draw(Display&);

};

#endif
