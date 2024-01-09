
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

#include "Entity.hpp"

using namespace std;

Entity::Entity(Vector2f p_pos, SDL_Texture * p_texture) 
	:pos(p_pos), texture(p_texture)
{
	currentFrame.x = 0;
	currentFrame.y = 0;
	currentFrame.w = 32;
	currentFrame.h = 32;
};



SDL_Texture* Entity::getTexture() {
	return texture;
}
SDL_Rect Entity::getCurrentFrame() {
	return currentFrame;
}

