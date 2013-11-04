
#ifndef DISPLAY_H
#define DISPLAY_H

using namespace std;

class SDL_Surface;

class Display {
	SDL_Surface* screen;
	int initErrorCode;

public:
	const int width;
	const int height;

	Display(int width, int height);
	void draw(int x, int y, SDL_Surface* image);
	int flip();
	void clear();
	~Display();
	int getInitErrCode() { return initErrorCode; }
};

#endif
