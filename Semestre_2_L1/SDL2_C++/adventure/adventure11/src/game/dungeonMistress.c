/*
 * Copyright (C) 2021-2022 Parallel Realities. All rights reserved.
 */

#include "../common.h"

#include "../game/inventory.h"
#include "../game/messageBox.h"
#include "../json/cJSON.h"
#include "../system/atlas.h"
#include "dungeonMistress.h"

extern Entity *player;

static void touch(Entity *self, Entity *other);

static SDL_Color mbColor;

void initDungeonMistress(Entity *e)
{
	DungeonMistress *dungeonMistress;
	dungeonMistress = malloc(sizeof(DungeonMistress));
	memset(dungeonMistress, 0, sizeof(DungeonMistress));

	e->texture = getAtlasImage("gfx/entities/dungeonMistress.png", 1);
	e->solid = SOLID_SOLID;
	e->facing = FACING_RIGHT;
	e->data = dungeonMistress;

	e->touch = touch;

	mbColor.r = 64;
	mbColor.g = 0;
	mbColor.b = 64;
}

static void touch(Entity *self, Entity *other)
{
	DungeonMistress *d;

	if (other == player)
	{
		self->facing = (other->x > self->x) ? FACING_RIGHT : FACING_LEFT;

		d = (DungeonMistress *)self->data;

		if (hasInventoryItem("Icon"))
		{
			removeInventoryItem("Icon");

			d->iconsFound++;

			switch (d->iconsFound)
			{
				case 1:
					addMessageBox("Prisoner", "I got one of the icons!", 64, 64, 64);
					addMessageBox("Dungeon Mistress", "You found one? Beginner's luck, I guess. Well, don't expect the others to come so easily. I'll just take that from you ...", mbColor.r, mbColor.g, mbColor.b);
					break;

				case 2:
					addMessageBox("Prisoner", "Here you go ...", 64, 64, 64);
					addMessageBox("Dungeon Mistress", "Another one? No, you're cheating. This has got to be a fake. I'll have it checked ...", mbColor.r, mbColor.g, mbColor.b);
					break;

				default:
					break;
			}
		}
		else
		{
			switch (d->iconsFound)
			{
				case 0:
					addMessageBox("Dungeon Mistress", "Not found any yet? Aw, poor baby. Going to be here at while, aren't you? Heh heh heh!", mbColor.r, mbColor.g, mbColor.b);
					break;

				case 1:
					addMessageBox("Dungeon Mistress", "Don't get excited, hon. You've only found one icon so far.", mbColor.r, mbColor.g, mbColor.b);
					break;

				case 2:
					addMessageBox("Dungeon Mistress", "Halfway there, but you'll never find the rest. You'll starve to death down here. Ha ha ha!", mbColor.r, mbColor.g, mbColor.b);
					break;

				default:
					break;
			}
		}
	}
}
