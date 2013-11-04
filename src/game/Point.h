#ifndef POINT_H_
#define POINT_H_

#include <cmath>
#include "Util.h"

class Point {
public:
	double x, y;
	Point() : x(0.0), y(0.0) { }
	Point(double _x, double _y) : x(_x), y(_y) { }
	Point(const Point& p) : x(p.x), y(p.y) { }
	Point& scale(const Point& p) { x *= p.x; y *= p.y; return *this; }
	Point& scale(double p) { x *= p; y *= p; return *this; };
	Point& scale(double dx, double dy) { x *= dx; y *= dy; return *this; }
	int getIntX() const { return (int) x; }
	int getIntY() const { return (int) y; }

	double distance(const Point& p) const {
		return distance(p.x, p.y);
	}

	double distance(double x1, double y1) const {
		double dx = x - x1;
		double dy = y - y1;
		return sqrt(dx * dx + dy * dy);
	}

	Point& normalize() {
		double d = distance(0, 0);
		x = x / d;
		y = y / d;
		return *this;
	}

	static Point RANDOM() { return Point(getRandomFloat(), getRandomFloat()); }
};

inline Point operator-(const Point& rhs, const Point& lhs) {
	Point result(rhs);
	result.x -= lhs.x;
	result.y -= lhs.y;
	return result;
}

inline Point operator+(const Point& rhs, const Point& lhs) {
	Point result(rhs);
	result.x += lhs.x;
	result.y += lhs.y;
	return result;
}

#endif
