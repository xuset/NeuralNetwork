#include "Point.h"

class Rect {
public:
	Point points[4];

	Rect() { }

	Rect(double x, double y, double width, double height) {
		points[0] = Point(x, y);
		points[1] = Point(x + width, y);
		points[2] = Point(x, y + height);
		points[3] = Point(x + width, y + height);
	}

	double getX() const      { return points[0].x; }
	double getY() const      { return points[1].y; }
	double getWidth() const  { return points[1].x - points[0].x; }
	double getHeight() const { return points[2].y - points[0].y; }
	Point& topLeft()     { return points[0]; }
	Point& topRight()    { return points[1]; }
	Point& bottomLeft()  { return points[2]; }
	Point& bottomRight() { return points[3]; }

	bool isInside(const Point& p) const {
		return (p.x >= getX() && p.x <= getX() + getWidth() &&
				p.y >= getY() && p.y <= getY() + getHeight());
	}

	bool collided(const Rect& r) const {
		for (int i = 0; i < 4; i++) {
			if (isInside(r.points[i]))
				return true;
			if (r.isInside(points[i]))
				return true;
		}
		return false;
	}
};
