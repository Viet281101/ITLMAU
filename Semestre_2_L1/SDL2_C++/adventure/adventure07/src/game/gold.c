/*
 * Copyright (C) 2021-2022 Parallel Realities. All rights reserved.
 */

#include "../common.h"

#include "../game/entities.h"
#include "../game/hud.h"
#include "../system/atlas.h"
#include "gold.h"

extern Entity *player;

static void touchGoldCoin(Entity *e, Entity *other);
static void touchGoldCoins(Entity *e, Entity *other);

// == Gold Coin

void initGoldCoin(int x, int y)
{
	Entity *e;

	e = spawnEntity();
	e->x = x;
	e->y = y;
	e->texture = getAtlasImage("gfx/entities/goldCoin.png", 1);

	e->touch = touchGoldCoin;
}

static void touchGoldCoin(Entity *self, Entity *other)
{
	Prisoner *p;

	if (other == player)
	{
		p = (Prisoner *)other->data;

		p->gold++;

		self->alive = ALIVE_DEAD;

		setInfoMessage("Picked up a gold coin.");
	}
}

// == Gold Coins

void initGoldCoins(int x, int y)
{
	Entity *e;

	e = spawnEntity();
	e->x = x;
	e->y = y;
	e->texture = getAtlasImage("gfx/entities/goldCoins.png", 1);

	e->touch = touchGoldCoins;
}

static void touchGoldCoins(Entity *self, Entity *other)
{
	Prisoner *p;

	if (other == player)
	{
		p = (Prisoner *)other->data;

		p->gold += 5;

		self->alive = ALIVE_DEAD;

		setInfoMessage("Found 5 gold coins!");
	}
}
