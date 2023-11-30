/*
 * Copyright (C) 2021-2022 Parallel Realities. All rights reserved.
 */

Entity *removeInventoryItem(char *name);
int		hasInventoryItem(char *name);
int		addToInventory(Entity *e);
void	initInventoryView(void);
void	initInventory(void);
