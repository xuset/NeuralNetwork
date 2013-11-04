#include "Coin.h"
#include "Sprite.h"

Coin::Coin(const Point& _gameDimensions) :
		Entity(Sprite::GET("coin.bmp")->image, Point(0, 0)),
		gameDimensions(_gameDimensions) {
	reset();
}
void Coin::reset() {
	Point p = Point::RANDOM().scale(gameDimensions);
	location = p;
	found = false;
}

void Coin::draw(Display& display) {
	if (!found)
		Entity::draw(display);
}
