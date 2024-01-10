
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

#include "RenderWindow.hpp"
#include "Entity.hpp"

using namespace std;



RenderWindow::RenderWindow(const char* p_title, int p_width, int p_height)
	:window(NULL), renderer(NULL)
{
	window = SDL_CreateWindow(p_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, p_width, p_height, SDL_WINDOW_SHOWN);

	if (window == NULL){
		cout << "Window failed to init. Error: " << SDL_GetError() << endl;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

SDL_Texture * RenderWindow::loadTexture(const char *filePath){
	SDL_Texture* texture = NULL;
	texture = IMG_LoadTexture(renderer, filePath);

	if (texture == NULL)
		cout << "Failed to load texture. Error: " << SDL_GetError() << endl;

	return texture;
}

int RenderWindow::getRefreshRate(){
	int displayIndex = SDL_GetWindowDisplayIndex( window );

	SDL_DisplayMode mode;

	SDL_GetDisplayMode(displayIndex, 0, &mode);

	return mode.refresh_rate;
}

void RenderWindow::cleanUp(){
	SDL_DestroyWindow(window);
}

void RenderWindow::clear(){
	SDL_RenderClear(renderer);
}

void RenderWindow::render(Entity& p_entity){
	SDL_Rect src;
	src.x = p_entity.getCurrentFrame().x;
	src.y = p_entity.getCurrentFrame().y;
	src.w = p_entity.getCurrentFrame().w;
	src.h = p_entity.getCurrentFrame().h;

	SDL_Rect dst;
	int dst_scale = 4;
	dst.x = p_entity.getPos().x * dst_scale;
	dst.y = p_entity.getPos().y * dst_scale;
	dst.w = p_entity.getCurrentFrame().w * dst_scale;
	dst.h = p_entity.getCurrentFrame().h * dst_scale;

	SDL_RenderCopy(renderer, p_entity.getTexture(), &src, &dst);
}

void RenderWindow::display(){
	SDL_RenderPresent(renderer);
}
