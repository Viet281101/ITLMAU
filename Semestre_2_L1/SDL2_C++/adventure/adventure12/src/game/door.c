/*
 * Copyright (C) 2021-2022 Parallel Realities. All rights reserved.
 */

#include "../common.h"

#include "../game/hud.h"
#include "../json/cJSON.h"
#include "../system/atlas.h"
#include "door.h"

extern Entity *player;

static void touch(Entity *self, Entity *other);
static void load(Entity *e, cJSON *root);

void initDoor(Entity *e)
{
	Door *door;

	door = malloc(sizeof(Door));
	memset(door, 0, sizeof(Door));

	e->texture = getAtlasImage("gfx/entities/door.png", 1);
	e->solid = SOLID_SOLID;
	e->data = door;

	e->touch = touch;
	e->load = load;
}

static void touch(Entity *self, Entity *other)
{
	Door *door;

	if (other == player)
	{
		door = (Door *)self->data;

		if (door->locked)
		{
			setInfoMessage("The door's locked.");
		}
		else
		{
			self->alive = ALIVE_DEAD;
		}
	}
}

static void load(Entity *e, cJSON *root)
{
	Door *door;

	door = (Door *)e->data;

	door->locked = cJSON_GetObjectItem(root, "locked")->valueint;
}
