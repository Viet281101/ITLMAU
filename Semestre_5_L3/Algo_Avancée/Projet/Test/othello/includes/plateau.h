#ifndef OTHELLO_PLATEAU_H
#define OTHELLO_PLATEAU_H 1

#include "jeu.h"
#include "utils.h"

/* Remplie le plateau avec la configuration de départ */
void remplissage_debut(Jeu *jeu);

/* Affiche le plateau */
void affiche_plateau(Jeton *plateau[LONGEUR][LARGEUR]);

/* Auxiliaire : Affiche une suite de lettres pour l'affichage du plateau */
void _affiche_lettres(void);

/* Vérifie si une case est jouable par un joueur */
int case_jouable(Jeton *plateau[LONGEUR][LARGEUR], const int case_i,
                 const int case_j, const int couleur);

/* Auxiliaire : Vérifie pour une direction si le coup est légal */
int _case_jouable(Jeton *plateau[LONGEUR][LARGEUR], const int case_i,
                  const int case_j, const int case_i_direction,
                  const int case_j_direction, const int couleur);

/* Vérifie si le plateau est rempli */
int plateau_rempli(Jeton *plateau[LONGEUR][LARGEUR]);

#endif
