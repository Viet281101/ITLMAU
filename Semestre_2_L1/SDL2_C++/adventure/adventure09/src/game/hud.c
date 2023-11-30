/*
 * Copyright (C) 2021-2022 Parallel Realities. All rights reserved.
 */

#include "../common.h"

#include "../system/atlas.h"
#include "../system/draw.h"
#include "../system/text.h"
#include "hud.h"

#define INFO_MESSAGE_LENGTH 64

extern App	   app;
extern Entity *player;

static void drawMessages(void);
static void drawGold(void);
static void drawInventory(void);
static void drawLocation(void);

static double	   infoMessageTimer;
static char		   infoMessage[INFO_MESSAGE_LENGTH];
static AtlasImage *inventorySlotFame;

void initHud(void)
{
	memset(infoMessage, 0, sizeof(infoMessage));

	inventorySlotFame = getAtlasImage("gfx/hud/inventorySlotFrame.png", 1);

	infoMessageTimer = 0;
}

void doHud(void)
{
	infoMessageTimer = MAX(infoMessageTimer - app.deltaTime, 0);
}

void drawHud(void)
{
	drawMessages();

	drawGold();

	drawInventory();

	if (0)
	{
		drawLocation();
	}
}

static void drawMessages(void)
{
	if (infoMessageTimer > 0)
	{
		drawText(infoMessage, 10, SCREEN_HEIGHT - 50, 255, 255, 255, TEXT_ALIGN_LEFT, 0);
	}
}

static void drawGold(void)
{
	char message[16];

	memset(message, 0, sizeof(message));

	sprintf(message, "Gold: %d", ((Prisoner *)player->data)->gold);

	drawText(message, SCREEN_WIDTH - 15, SCREEN_HEIGHT - 50, 255, 200, 32, TEXT_ALIGN_RIGHT, 0);
}

static void drawInventory(void)
{
	int		  i, x;
	Prisoner *p;

	p = (Prisoner *)player->data;

	for (i = 0; i < NUM_INVENTORY_SLOTS; i++)
	{
		x = (SCREEN_WIDTH - 250) - (i * 80);

		blitAtlasImage(inventorySlotFame, x, SCREEN_HEIGHT - 28, 1, SDL_FLIP_NONE);

		if (p->inventorySlots[i] != NULL)
		{
			blitAtlasImage(p->inventorySlots[i]->texture, x, SCREEN_HEIGHT - 28, 1, SDL_FLIP_NONE);
		}
	}
}

void setInfoMessage(char *message)
{
	infoMessageTimer = FPS * 2.5;

	STRCPY(infoMessage, message);
}

static void drawLocation(void)
{
	char message[16];

	sprintf(message, "%d,%d", player->x, player->y);

	drawText(message, 5, 5, 255, 255, 255, TEXT_ALIGN_LEFT, 0);
}
