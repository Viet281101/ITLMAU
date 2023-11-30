/*
 * Copyright (C) 2021-2022 Parallel Realities. All rights reserved.
 */

#include "../common.h"

#include "../game/entities.h"
#include "../game/messageBox.h"
#include "../system/atlas.h"
#include "signpost.h"

extern Entity *player;

static void touch(Entity *e, Entity *other);

void initSignPost(int x, int y, char *message)
{
	Entity   *e;
	Signpost *signpost;

	signpost = malloc(sizeof(Signpost));
	memset(signpost, 0, sizeof(Signpost));
	STRCPY(signpost->message, message);

	e = spawnEntity();
	e->x = x;
	e->y = y;
	e->texture = getAtlasImage("gfx/entities/signpost.png", 1);
	e->solid = SOLID_SOLID;
	e->data = signpost;

	e->touch = touch;
}

static void touch(Entity *self, Entity *other)
{
	Signpost *signpost;

	if (other == player)
	{
		signpost = (Signpost *)self->data;

		addMessageBox("Signpost", signpost->message, 90, 70, 30);
	}
}
