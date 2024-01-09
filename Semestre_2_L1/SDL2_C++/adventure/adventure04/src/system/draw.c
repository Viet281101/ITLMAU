/*
 * Copyright (C) 2021-2022 Parallel Realities. All rights reserved.
 */

#include "../common.h"

#include "../system/text.h"
#include "draw.h"

extern App app;

static void showFPS(void);

void prepareScene(void)
{
	SDL_SetRenderDrawColor(app.renderer, 16, 16, 32, 255);
	SDL_RenderClear(app.renderer);
}

void presentScene(void)
{
	if (0)
	{
		showFPS();
	}

	SDL_RenderPresent(app.renderer);
}

static void showFPS(void)
{
	char fps[8];

	memset(fps, 0, sizeof(fps));

	sprintf(fps, "%d", app.dev.fps);

	drawText(fps, SCREEN_WIDTH - 10, 0, 255, 255, 255, TEXT_ALIGN_RIGHT, 0);
}

void blit(SDL_Texture *texture, int x, int y, int center)
{
	SDL_Rect dest;

	dest.x = x;
	dest.y = y;
	SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);

	if (center)
	{
		dest.x -= dest.w / 2;
		dest.y -= dest.h / 2;
	}

	SDL_RenderCopy(app.renderer, texture, NULL, &dest);
}

void blitAtlasImage(AtlasImage *atlasImage, int x, int y, int center, SDL_RendererFlip flip)
{
	SDL_Rect dest;

	dest.x = x;
	dest.y = y;
	dest.w = atlasImage->rect.w;
	dest.h = atlasImage->rect.h;

	if (center)
	{
		dest.x -= dest.w / 2;
		dest.y -= dest.h / 2;
	}

	SDL_RenderCopyEx(app.renderer, atlasImage->texture, &atlasImage->rect, &dest, 0, NULL, flip);
}
