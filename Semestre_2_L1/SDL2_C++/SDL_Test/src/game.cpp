
#include "Game.hpp"
#include "Texture.hpp"
#include "Map.hpp"
#include "Components.hpp"
#include "Vector2d.hpp"
#include "Collision.hpp"

using namespace std;

Map* map;
Manager manager;

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;


auto& player(manager.addEntity());
auto& wall(manager.addEntity());


Game::Game() {};

Game::~Game() {};

void Game::init(const char *title, int width, int height, bool fullscreen)
{
	//// check fullscreen
	int flags = 0;
	if (fullscreen)
		flags = SDL_WINDOW_FULLSCREEN;

	//// Init window screen
	if( SDL_Init(SDL_INIT_EVERYTHING) == 0 ) {
		cout << "Subsystem Initialised !... " << endl;

		//// create window screen
		window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
		if (window)
			cout << "Window created ! " << endl;

		//// create renderer screen
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
		if (renderer) {
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			cout << "Renderer created ! " << endl;
		}

		isRunning = true;
	} else {
		//// check error init
		isRunning = false;
		cout << "SDL_Init HAS FAILED !! SDL_ERROR: " << SDL_GetError() << endl;
	}

	//// Load object texture:
	map = new Map();

	//// ECS implementation
	player.addComponent<TransformComponent>(2);
	player.addComponent<SpriteComponent>("res/archer/idle/idle1.png");
	player.addComponent<KeyboardController>();
	player.addComponent<ColliderComponent>("player");

	wall.addComponent<TransformComponent>(300.0f, 300.0f, 300, 20, 1);
	wall.addComponent<SpriteComponent>("res/world/ceramic_tiles/7.png");
	wall.addComponent<ColliderComponent>("wall");
}

void Game::handleEvents()
{
	

	SDL_PollEvent(&event);

	switch (event.type) 
	{
		case SDL_QUIT:
			isRunning = false;
			break;

		default:
			break;
	}
}

void Game::update()
{
	manager.refresh();
	manager.update();
	
	if ( Collision::AABB(player.getComponent<ColliderComponent>().collider,
						wall.getComponent<ColliderComponent>().collider) )
	{
		/*player.getComponent<TransformComponent>().scale = 1;*/
		player.getComponent<TransformComponent>().velocity * -1;
		cout << "Wall Hit !" << endl;
	}

	/*player.getComponent<TransformComponent>().position.Add(Vector2D(3, 3));

	if (player.getComponent<TransformComponent>().position.x > 100)
	{
		player.getComponent<SpriteComponent>().setTex("res/skeleton/idle/idle-1.png");
	}*/
}

void Game::render()
{
	SDL_RenderClear(renderer);
	
	//// add render objects
	map -> drawMap();
	manager.draw();


	SDL_RenderPresent(renderer);
}

void Game::clean() 
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	cout << "Game Cleaned !" << endl;
}


