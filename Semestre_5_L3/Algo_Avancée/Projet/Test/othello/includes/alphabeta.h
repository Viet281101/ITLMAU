#ifndef OTHELLO_ALPHABETA_H
#define OTHELLO_ALPHABETA_H 1

#include "minimax.h"

/* Joue le tour d'après l'algorithme alpha-beta */
void action_joueur_alphabeta(Jeu *jeu, const int couleur, const int profondeur);

/* Décide d'une case à jouer via l'algorithme alpha-beta */
void _action_joueur_alphabeta(Jeu *jeu, int profondeur, int couleur,
                              const int gagnant, int *ligne, int *colonne,
                              int *score, const int note, const int qui);

#endif
