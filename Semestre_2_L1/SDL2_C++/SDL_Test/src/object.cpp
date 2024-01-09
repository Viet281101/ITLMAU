
#include "Object.hpp"
#include "Texture.hpp"

Object::Object(const char* name, int x, int y)
{
	objTexture = TextureManager::LoadTexture(name);

	xpos = x;
	ypos = y;
}


void Object::update() {

	xpos++;
	ypos++;

	srcRect.h = 96;
	srcRect.w = 128;
	srcRect.x = 0;
	srcRect.y = 0;

	desRect.x = xpos;
	desRect.y = ypos;
	desRect.w = srcRect.w * 2;
	desRect.h = srcRect.h * 2;
}

void Object::render() {
	SDL_RenderCopy( Game::renderer, objTexture, &srcRect, &desRect );
}


