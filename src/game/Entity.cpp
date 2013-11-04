
#include "SDL/SDL.h"
#include "Display.h"
#include "Entity.h"
#include "Rect.h"

Entity::Entity(SDL_Surface* _image, const Point& p) :
		location(p.x, p.y) {
	image = _image;
	angle = 0;
}

Entity::~Entity() {

}

void Entity::draw(Display& display) {
	display.draw(location.getIntX(), location.getIntY(), image);
}

void Entity::doLogic() {

}

void Entity::moveForward(double distance) {
	location.x += distance * cos(angle);
	location.y += distance * sin(angle);
}

bool Entity::collided(const Entity& e) const {
	Rect r1(location.x, location.y, getWidth(), getHeight());
	Rect r2(e.location.x, e.location.y, e.getWidth(), e.getHeight());
	return (r1.collided(r2));
}

int Entity::getWidth() const {
	 return image->w;
}

int Entity::getHeight() const {
	return image->h;
}
