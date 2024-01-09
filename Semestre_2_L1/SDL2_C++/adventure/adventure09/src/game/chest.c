/*
 * Copyright (C) 2021-2022 Parallel Realities. All rights reserved.
 */

#include "../common.h"

#include "../game/entities.h"
#include "../game/hud.h"
#include "../game/inventory.h"
#include "../json/cJSON.h"
#include "../system/atlas.h"
#include "chest.h"

extern Entity *player;

static void touch(Entity *self, Entity *other);
static void load(Entity *e, cJSON *root);

void initChest(Entity *e)
{
	Chest *chest;

	chest = malloc(sizeof(Chest));
	memset(chest, 0, sizeof(Chest));

	STRCPY(e->name, "Chest");
	e->texture = getAtlasImage("gfx/entities/chest.png", 1);
	e->solid = SOLID_SOLID;
	e->data = chest;

	e->touch = touch;
	e->load = load;
}

static void touch(Entity *self, Entity *other)
{
	Chest  *chest;
	Entity *e;
	char	message[64];

	if (other == player)
	{
		chest = (Chest *)self->data;

		if (!chest->isOpen)
		{
			if (hasInventoryItem("Rusty key"))
			{
				chest->isOpen = 1;

				self->texture = getAtlasImage("gfx/entities/openChest.png", 1);

				e = removeInventoryItem("Rusty key");

				e->alive = ALIVE_DEAD;

				addEntityToDungeon(e);

				addToInventory(chest->item);

				sprintf(message, "Got %s", chest->item->name);

				setInfoMessage(message);

				chest->item = NULL;
			}
			else
			{
				setInfoMessage("It's locked and I don't have a key.");
			}
		}
	}
}

static void load(Entity *e, cJSON *root)
{
	Chest *chest;

	chest = (Chest *)e->data;

	chest->itemId = cJSON_GetObjectItem(root, "itemId")->valueint;
}
