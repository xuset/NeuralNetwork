#include "SDL/SDL.h"
#include "Display.h"
#include <stdio.h>

#define PIXEL_DEPTH 32

Display::Display(int _width, int _height) :
		width(_width), height(_height) {
	initErrorCode = 0;
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		fprintf(stderr, "An error occurred while initializing SDL");
		initErrorCode = 1;
		return;
	}

	screen = SDL_SetVideoMode(width, height, PIXEL_DEPTH, SDL_SWSURFACE);
	if (screen == NULL) {
		fprintf(stderr, "An error occurred while setting the video mode");
		initErrorCode = 1;
		return;
	}

	SDL_WM_SetCaption("Neural network and genetic algorithm visual", NULL);
}


void Display::draw(int x, int y, SDL_Surface* image) {
	SDL_Rect rect;
	rect.x = x;
	rect.y = y;

	SDL_BlitSurface(image, NULL, screen, &rect);
}

int Display::flip() {
	return SDL_Flip(screen);
}

void Display::clear() {
	SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
}

Display::~Display() {
	SDL_Quit();
}
