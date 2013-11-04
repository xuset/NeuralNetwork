#include <string>
#include "SDL/SDL.h"
#include "Sprite.h"

using namespace std;

vector<Sprite*>* Sprite::sprites = new vector<Sprite*>();



Sprite::Sprite(const string& _url, SDL_Surface* _image) :
	url(_url),
	image(_image) {
}

Sprite::~Sprite() {
	SDL_FreeSurface(image);
}

SDL_Surface* Sprite::LOAD_BMP(const string& filename) {
	SDL_Surface* image = NULL;
	SDL_Surface* optimized = NULL;
	image = SDL_LoadBMP(filename.c_str());
	if (image != NULL) {
		optimized = SDL_DisplayFormat(image);
		SDL_FreeSurface(image);
		return optimized;
	}
	return image;
}

Sprite* Sprite::GET(const string& url) {
	for (size_t i = 0; i < Sprite::sprites->size(); i++) {
		Sprite& s = *Sprite::sprites->at(i);
		if (url.compare(s.url) == 0) {
			return &s;
		}
	}
	return NULL;
}

Sprite* Sprite::ADD(const string& url) {
	Sprite* s = GET(url);
	if (s != NULL)
		return s;

	SDL_Surface* img = LOAD_BMP(url);
	if (img != NULL) {
		s = new Sprite(url, img);
		Sprite::sprites->push_back(s);
		return s;
	}

	return NULL;
}

void Sprite::DESTROY_ALL() {
	for (size_t i = 0; i < sprites->size(); i++) {
		delete sprites->at(i);
	}
}
