/*
 * Copyright (C) 2021-2022 Parallel Realities. All rights reserved.
 */

#include "../common.h"

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
	initMap();

	initEntities();

	initPlayer();

	initHud();

	initInventory();

	initItem("Rusty key", 18, 17, "gfx/entities/rustyKey.png");

	initItem("Eyeball", 23, 14, "gfx/entities/eyeball.png");

	initItem("Red Potion", 27, 15, "gfx/entities/redPotion.png");

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
