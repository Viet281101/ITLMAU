/*
 * Copyright (C) 2021-2022 Parallel Realities. All rights reserved.
 */

#include "../common.h"

#include "../game/chest.h"
#include "../game/entities.h"
#include "../game/goldCoin.h"
#include "../game/goldCoins.h"
#include "../game/hud.h"
#include "../game/map.h"
#include "../game/player.h"
#include "dungeon.h"

extern App	   app;
extern Dungeon dungeon;

static void logic(void);
static void draw(void);

void initDungeon(void)
{
	initMap();

	initEntities();

	initPlayer();

	initHud();

	initGoldCoin(18, 17);

	initGoldCoin(23, 14);

	initGoldCoins(56, 0);

	initChest(12, 12);

	dungeon.renderOffset.x = (SCREEN_WIDTH - (MAP_RENDER_WIDTH * TILE_SIZE)) / 2;
	dungeon.renderOffset.y = 20;

	app.delegate.logic = &logic;
	app.delegate.draw = &draw;
}

static void logic(void)
{
	doPlayer();

	doEntities();

	doHud();
}

static void draw(void)
{
	drawMap();

	drawEntities();

	drawHud();
}
