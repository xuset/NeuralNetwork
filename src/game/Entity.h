
#ifndef ENTITY_H_
#define ENTITY_H_

#include "Point.h"

class SDL_Surface;
class Display;

class Entity {
public:
	SDL_Surface* image;
	Point location;
	double angle;

	Entity(SDL_Surface*, const Point&);
	virtual ~Entity();
	virtual void doLogic();
	virtual void draw(Display&);
	int getWidth() const;
	int getHeight() const;
	void moveForward(double distance);
	virtual bool collided(const Entity&) const;
	Point getCenter() const { return Point(location.x + getWidth() / 2, location.y + getHeight() / 2); }
};

#endif
