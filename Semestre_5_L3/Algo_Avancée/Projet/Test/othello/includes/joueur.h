#ifndef OTHELLO_JOUEUR_H
#define OTHELLO_JOUEUR_H 1

#include "plateau.h"

typedef struct jeu Jeu;

/* Joueur possédant un nom, une couleur ainsi que sa liste de jeton
 * placé sur le plateau */
struct joueur {
    char *nom;
    int couleur;
    Liste *liste_jeton;
    int nb_jeton; // permet de facilement savoir qui a gagné
};
typedef struct joueur Joueur;

/* Créer un nouveau joueur */
Joueur *nouveau_joueur(const int pion);

/* Ajoute un jeton à un joueur */
void ajoute_jeton_joueur(Joueur *joueur, Jeton *jeton);

/* Retire un jeton à un joueur */
void retire_jeton_joueur(Joueur *joueur, Jeton *jeton);

/* Renvoie la couleur de l'ennemi */
int couleur_ennemi(const int couleur);

/* Gère le coup d'un joueur en faisant les changements nécessaire au jeu
 * Renvoie 0 en cas de coup illégal */
int jeu_joueur(Jeu *jeu, const int case_i, const int case_j, const int couleur);

/* Auxiliaire : S'occupe de faire les changements de jetons récursivement
 * lorsqu'un joueur joue */
void _jeu_joueur(Jeu *jeu, const int case_i, const int case_j,
                 const int case_i_direction, const int case_j_direction,
                 const int couleur);

#endif
