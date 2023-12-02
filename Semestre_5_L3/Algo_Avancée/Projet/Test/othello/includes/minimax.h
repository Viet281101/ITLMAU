#ifndef OTHELLO_MINIMAX_H
#define OTHELLO_MINIMAX_H 1

#include <limits.h>

#include "joueur.h"

/* Joue le tour d'après l'algorithme minimax */
void action_joueur_minimax(Jeu *jeu, const int couleur, const int profondeur);

/* Décide d'une case à jouer via l'algorithme minimax */
void _action_joueur_minimax(Jeu *jeu, int profondeur, const int couleur,
                            const int gagnant, int *ligne, int *colonne,
                            int *score);

/* Calcule la valeur heuristique pour un coup */
int heuristique(const Jeu *jeu, const int couleur);

#endif
