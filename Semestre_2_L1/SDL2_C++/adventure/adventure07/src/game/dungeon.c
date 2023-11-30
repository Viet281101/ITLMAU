/*
 * Copyright (C) 2021-2022 Parallel Realities. All rights reserved.
 */

#include "../common.h"

#include "../game/chest.h"
#include "../game/entities.h"
#include "../game/fogOfWar.h"
#include "../game/gold.h"
#include "../game/hud.h"
#include "../game/inventory.h"
#include "../game/item.h"
#include "../game/map.h"
#include "../game/player.h"
#include "dungeon.h"

extern App	   app;
extern Dungeon dungeon;

static void logic(void);
static void draw(void);

void initDungeon(void)
{
	Entity *e;

	initMap();

	initFogOfWar();

	initEntities();

	initPlayer();

	initHud();

	initInventory();

	initItem("Rusty key", 51, 23, "gfx/entities/rustyKey.png");

	initGoldCoin(1, 19);

	initGoldCoin(27, 0);

	initGoldCoin(19, 9);

	initGoldCoins(7, 3);

	e = initItem("Eyeball", 0, 0, "gfx/entities/eyeball.png");

	initChest(21, 14, e);

	e = initItem("Red potion", 0, 0, "gfx/entities/redPotion.png");

	initChest(18, 14, e);

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

	drawFogOfWar();

	drawHud();
}

void initDungeonView(void)
{
	app.delegate.logic = &logic;
	app.delegate.draw = &draw;
}
