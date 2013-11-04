
#ifndef SPRITESTORE_H_
#define SPRITESTORE_H_

#include <vector>
#include <string>

class SDL_Surface;
class Sprite;

class Sprite {
	Sprite(const std::string&, SDL_Surface*);

public:
	static std::vector<Sprite*>* sprites;

	static Sprite* GET(const std::string&);
	static Sprite* ADD(const std::string&);
	static SDL_Surface* LOAD_BMP(const std::string&);
	static void DESTROY_ALL();

	~Sprite();
	const std::string url;
	SDL_Surface* const image;
};



#endif
