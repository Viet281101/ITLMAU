
#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "Game.hpp"


class Object {

private:

	int xpos;
	int ypos;

	SDL_Texture* objTexture;
	SDL_Rect srcRect, desRect;

public:
	Object(const char* name, int x, int y);
	~Object();

	void update();
	void render();

};


