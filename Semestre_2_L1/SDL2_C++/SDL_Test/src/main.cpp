
//// to import the sdl2 library
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>

#include "Game.hpp"
#include "Texture.hpp"
#include "Object.hpp"
#include "Map.hpp"

using namespace std;



Game *game = nullptr;


int main(int argc, char *args[])
{
	//// to limiting frames time 
	const int FPS = 60;
	const int delay = 1;
	const int frameDelay = 1000 * delay / FPS;
	Uint32 frameStart;
	int frameTime;

	//// main loop 
	game = new Game();
	game -> init("Warriors vs Undead", 960, 720, false);

	while ( game -> running() ) {

		frameStart = SDL_GetTicks();

		game -> handleEvents();
		game -> update();
		game -> render();

		//// delay limit frame time
		frameTime = SDL_GetTicks() - frameStart;
		if (frameDelay > frameTime) {
			SDL_Delay(frameDelay - frameTime);
		}
	}

	game -> clean();

	return 0;
}
