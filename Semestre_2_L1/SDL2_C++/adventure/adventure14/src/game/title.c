/*
 * Copyright (C) 2021-2022 Parallel Realities. All rights reserved.
 */

#include "../common.h"

#include "../game/dungeon.h"
#include "../system/atlas.h"
#include "../system/draw.h"
#include "../system/text.h"
#include "title.h"

extern App app;

static void logic(void);
static void draw(void);
static void drawLogo(void);

static AtlasImage *logo1;
static AtlasImage *logo2;
static double	   logoAlpha;
static int		   gotoDungeon;
static double	   gotoDungeonTimer;
static double	   tickVal;

void initTitle(void)
{
	logo1 = getAtlasImage("gfx/misc/logo1.png", 1);
	logo2 = getAtlasImage("gfx/misc/logo2.png", 1);

	logoAlpha = 0;

	gotoDungeon = 0;

	tickVal = 0;

	gotoDungeonTimer = FPS / 2;

	app.delegate.logic = logic;
	app.delegate.draw = draw;
}

static void logic(void)
{
	if (!gotoDungeon)
	{
		logoAlpha = MIN(logoAlpha + app.deltaTime * 2, 255);

		tickVal += app.deltaTime;

		if (app.keyboard[SDL_SCANCODE_SPACE])
		{
			app.keyboard[SDL_SCANCODE_SPACE] = 0;

			gotoDungeon = 1;
		}
	}
	else
	{
		gotoDungeonTimer -= app.deltaTime;

		if (gotoDungeonTimer <= 0)
		{
			initDungeon();
		}
	}
}

static void draw(void)
{
	int c;

	if (!gotoDungeon)
	{
		drawRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 32, 32, 32, 255);

		drawLogo();

		c = ((int)tickVal % (int)FPS < FPS / 2) ? 255 : 192;

		drawText("Press Space!", SCREEN_WIDTH / 2, 400, c, c, c, TEXT_ALIGN_CENTER, 0);

		drawText("Copyright Parallel Realities, 2021. All Rights Reserved.", SCREEN_WIDTH / 2, SCREEN_HEIGHT - 50, 128, 128, 128, TEXT_ALIGN_CENTER, 0);
	}
}

static void drawLogo(void)
{
	int x, y;

	x = (SCREEN_WIDTH - (logo1->rect.w + logo2->rect.w)) / 2;
	y = 150;

	SDL_SetTextureAlphaMod(logo1->texture, logoAlpha);

	blitAtlasImage(logo1, x, y, 0, SDL_FLIP_NONE);
	blitAtlasImage(logo2, x + logo1->rect.w, y, 0, SDL_FLIP_NONE);

	SDL_SetTextureAlphaMod(logo1->texture, 255);
}
