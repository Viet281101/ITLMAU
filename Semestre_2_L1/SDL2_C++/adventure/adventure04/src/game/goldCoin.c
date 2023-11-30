/*
 * Copyright (C) 2021-2022 Parallel Realities. All rights reserved.
 */

#include "../common.h"

#include "../game/entities.h"
#include "../game/hud.h"
#include "../system/atlas.h"
#include "goldCoin.h"

extern Entity *player;

static void touch(Entity *e, Entity *other);

void initGoldCoin(int x, int y)
{
	Entity *e;

	e = spawnEntity();
	e->x = x;
	e->y = y;
	e->texture = getAtlasImage("gfx/entities/goldCoin.png", 1);

	e->touch = touch;
}

static void touch(Entity *self, Entity *other)
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
