/*
 * Copyright (C) 2021-2022 Parallel Realities. All rights reserved.
 */

#include "../common.h"

#include "../system/text.h"
#include "hud.h"

#define INFO_MESSAGE_LENGTH 64

extern App	   app;
extern Entity *player;

static double infoMessageTimer;
static char	  infoMessage[INFO_MESSAGE_LENGTH];

void initHud(void)
{
	memset(infoMessage, 0, sizeof(infoMessage));

	infoMessageTimer = 0;
}

void doHud(void)
{
	infoMessageTimer = MAX(infoMessageTimer - app.deltaTime, 0);
}

void drawHud(void)
{
	char message[64];

	if (infoMessageTimer > 0)
	{
		drawText(infoMessage, 10, SCREEN_HEIGHT - 50, 255, 255, 255, TEXT_ALIGN_LEFT, 0);
	}

	sprintf(message, "Gold: %d", ((Prisoner *)player->data)->gold);

	drawText(message, SCREEN_WIDTH - 15, SCREEN_HEIGHT - 50, 255, 200, 32, TEXT_ALIGN_RIGHT, 0);
}

void setInfoMessage(char *message)
{
	infoMessageTimer = FPS * 2.5;

	STRCPY(infoMessage, message);
}
