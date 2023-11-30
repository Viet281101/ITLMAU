/*
 * Copyright (C) 2021-2022 Parallel Realities. All rights reserved.
 */

#include "../common.h"

#include "../game/hud.h"
#include "../json/cJSON.h"
#include "../system/atlas.h"
#include "silver.h"

extern Entity *player;

static void touch(Entity *self, Entity *other);

void initSilver(Entity *e)
{
	e->texture = getAtlasImage("gfx/entities/silverCoin.png", 1);

	e->touch = touch;
}

static void touch(Entity *self, Entity *other)
{
	Prisoner *p;

	if (other == player)
	{
		p = (Prisoner *)other->data;

		p->silver++;

		self->alive = ALIVE_DEAD;

		setInfoMessage("Picked up a silver coin.");
	}
}
