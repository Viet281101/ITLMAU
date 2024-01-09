/*
 * Copyright (C) 2021-2022 Parallel Realities. All rights reserved.
 */

void	activateEntities(char *name);
void	removeEntityFromDungeon(Entity *remove);
void	addEntityToDungeon(Entity *e);
Entity *getEntityAt(int x, int y);
void	drawEntities(void);
void	doEntities(void);
Entity *spawnEntity(void);
void	initEntities(void);
