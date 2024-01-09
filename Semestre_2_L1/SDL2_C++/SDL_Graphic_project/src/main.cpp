
//// call the library c++
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>

//// import the header files
#include "RenderWindow.hpp"
#include "Entity.hpp"
#include "Utils.hpp"

//// ignore the unusual warning
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-variable"

using namespace std;


int main(int argc, char *args[]){
	//// check error sdl initialize
	if (SDL_Init(SDL_INIT_VIDEO) > 0)
		cout << "HEY !! SDL_Init HAS FAILED. SDL_ERROR: " << SDL_GetError() << endl;
	//// check error sdl image initialize
	if (!(IMG_Init(IMG_INIT_PNG)))
		cout << "IMG_Init has failed. Error: " << SDL_GetError() << endl;

	//// create window
	RenderWindow window("Graphics Demo", 1280, 720);


	//// load texture image
	SDL_Texture * grassTexture = window.loadTexture("res/gfx/ground_grass_1.png");

	//// create entity , exemple : Entity object(0, 0, grassTexture);
/*	Entity entities[3] = {Entity(0, 0, grassTexture),
						Entity(30, 0, grassTexture),
						Entity(30, 30, grassTexture),
					};*/
	//// create entities with : std::vector<Entity> entities;
	vector<Entity> entities = {Entity(Vector2f(0, 0), grassTexture),
								Entity(Vector2f(30, 0), grassTexture),
								Entity(Vector2f(30, 30), grassTexture),
							};
	//// add new entity to vector entities 
	{
		Entity addEntity(Vector2f(100, 50), grassTexture);
		entities.push_back(addEntity);
	}

	const float timeStep = 0.01f;
	float accumulator = 0.0f;
	float currentTime = utils::hireTimeInSeconds();

	//// application loop
	bool gameRuning = true;
	SDL_Event event;
	while (gameRuning){

		int startTicks = SDL_GetTicks();

		float newTime = utils::hireTimeInSeconds();
		float frameTime = newTime - currentTime;
		currentTime = newTime;
		accumulator += frameTime;

		while (accumulator >= timeStep) {
			//// Get our controls and events
			while (SDL_PollEvent(&event)){
				if (event.type == SDL_QUIT)
					gameRuning = false;
			}

			accumulator -= timeStep;
		}

		const float alpha = accumulator / timeStep; // 50%?


		window.clear();
		//// rendering objects with: window.render(object);
		for (Entity& e : entities){
			window.render(e);
		}

		window.display();

		int frameTicks = SDL_GetTicks() - startTicks;
		if ( frameTicks < (1000 / window.getRefreshRate()) )
			SDL_Delay( (1000 / window.getRefreshRate()) - frameTicks );

	}



	window.cleanUp();
	SDL_Quit();

	return 0;
}
