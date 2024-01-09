/*
 * Copyright (C) 2021-2022 Parallel Realities. All rights reserved.
 */

#include "../common.h"

#include "../game/chest.h"
#include "../game/entities.h"
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

	initEntities();

	initPlayer();

	initHud();

	initInventory();

	initItem("Rusty key", 8, 11, "gfx/entities/rustyKey.png");

	e = initItem("Eyeball", 8, 11, "gfx/entities/eyeball.png");

	initChest(21, 14, e);

	e = initItem("Red potion", 8, 11, "gfx/entities/redPotion.png");

	initChest(24, 17, e);

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

void initDungeonView(void)
{
	app.delegate.logic = &logic;
	app.delegate.draw = &draw;
}
