#ifndef OTHELLO_HUMAN_H
#define OTHELLO_HUMAN_H 1

#include "joueur.h"

typedef struct jeu Jeu;

/* Joue le tour d'un joueur humain */
void action_joueur_humain(Jeu *jeu, const int couleur);

/* Auxiliaire : Demande au joueur où placer son jeton */
void _action_joueur_humain(int *ligne, int *colonne);

#endif
