
#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "Game.hpp"


class Map {

private:

	SDL_Rect src, dest;

	SDL_Texture* hole_1;
	SDL_Texture* hole_2;
	SDL_Texture* ceramic_tile_1;
	SDL_Texture* ceramic_tile_2;
	SDL_Texture* ceramic_tile_3;
	SDL_Texture* ceramic_tile_4;
	SDL_Texture* ceramic_tile_5;
	SDL_Texture* ceramic_tile_6;
	SDL_Texture* sewer_1;
	SDL_Texture* sewer_2;
	SDL_Texture* sewer_3;
	SDL_Texture* stair_left;
	SDL_Texture* stair_right;

	int map[30][30];

public:
	Map();
	~Map();

	void loadMap(int arr[30][30]);
	void drawMap();

};

