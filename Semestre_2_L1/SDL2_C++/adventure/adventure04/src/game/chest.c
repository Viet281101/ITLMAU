/*
 * Copyright (C) 2021-2022 Parallel Realities. All rights reserved.
 */

#include "../common.h"

#include "../game/entities.h"
#include "../game/hud.h"
#include "../system/atlas.h"
#include "chest.h"

extern Entity *player;

static void touch(Entity *e, Entity *other);

void initChest(int x, int y)
{
	Entity *e;

	e = spawnEntity();
	e->x = x;
	e->y = y;
	e->texture = getAtlasImage("gfx/entities/chest.png", 1);
	e->solid = SOLID_SOLID;

	e->touch = touch;
}

static void touch(Entity *self, Entity *other)
{
	if (other == player)
	{
		setInfoMessage("It's locked and I don't have a key.");
	}
}
