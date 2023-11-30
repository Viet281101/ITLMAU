/*
 * Copyright (C) 2021-2022 Parallel Realities. All rights reserved.
 */

#include "../common.h"

#include "../game/entities.h"
#include "../game/hud.h"
#include "../system/atlas.h"
#include "goldCoins.h"

extern Entity *player;

static void touch(Entity *e, Entity *other);

void initGoldCoins(int x, int y)
{
	Entity *e;

	e = spawnEntity();
	e->x = x;
	e->y = y;
	e->texture = getAtlasImage("gfx/entities/goldCoins.png", 1);

	e->touch = touch;
}

static void touch(Entity *self, Entity *other)
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
