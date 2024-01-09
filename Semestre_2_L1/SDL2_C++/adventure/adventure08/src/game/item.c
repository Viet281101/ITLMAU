/*
 * Copyright (C) 2021-2022 Parallel Realities. All rights reserved.
 */

#include "../common.h"

#include "../game/entities.h"
#include "../game/hud.h"
#include "../game/inventory.h"
#include "../system/atlas.h"
#include "item.h"

extern Entity *player;

static void touch(Entity *self, Entity *other);

Entity *initItem(char *name, int x, int y, char *texture)
{
	Entity *e;

	e = spawnEntity();
	STRCPY(e->name, name);
	e->x = x;
	e->y = y;
	e->texture = getAtlasImage(texture, 1);

	e->touch = touch;

	return e;
}

static void touch(Entity *self, Entity *other)
{
	char message[64];

	if (other == player)
	{
		if (addToInventory(self))
		{
			memset(message, 0, sizeof(message));

			sprintf(message, "Picked up %s", self->name);

			setInfoMessage(message);
		}
		else
		{
			setInfoMessage("Can't carry anything else.");
		}
	}
}
