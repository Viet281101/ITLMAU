

#ifndef Game_hpp
#define Game_hpp

#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

using namespace std;

class Game {

private:
	int count = 0;
	bool isRunning;
	SDL_Window *window;


public:
	Game();
	~Game();

	void init(const char* title, int width, int height, bool fullscreen);

	void handleEvents();
	void update();
	void render();
	void clean();

	bool running() {
		return isRunning;
	};

	static SDL_Renderer *renderer;
	static SDL_Event event;

};


#endif /* Game_hpp */
