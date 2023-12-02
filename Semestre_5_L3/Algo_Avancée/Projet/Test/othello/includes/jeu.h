#ifndef OTHELLO_JEU_H
#define OTHELLO_JEU_H 1

#include <stdio.h>
#include <stdlib.h>

#include "liste.h"
#include "test.h"

typedef struct joueur Joueur;

/* Une case est soit vide, soit occupé par un des joueurs, noir ou blanc */
enum CASE { VIDE = ' ', BLANC = 'B', NOIR = 'N' };

/* Propriété globale du jeu */
enum PLATEAU { LONGEUR = 8, LARGEUR = 8 };

/* Type de joueurs */
enum PLAYER_TYPE { HUMAIN, MINIMAX, ALPHABETA };

/* Renvoie un string comportant le nom du type du joueur */
const char *joueur_type_str(const enum PLAYER_TYPE type);

/* Jeton contenant le type de case (cf. enum CASE) ainsi que la position */
struct jeton {
    int couleur;
    int pos_i;
    int pos_j;
};
typedef struct jeton Jeton;

/* Ajoute un nouveau jeton */
Jeton *ajoute_jeton(const int position_i, const int position_j,
                    const int couleur);

void affiche_jeton(FILE *stream, const Jeton *jeton);

/* Jeu contenant nos 2 joueurs et le plateau de jeu */
struct jeu {
    Joueur *j1;
    Joueur *j2;
    Jeton *plateau[LONGEUR][LARGEUR];
};
typedef struct jeu Jeu;

/* Créer une nouvelle partie */
Jeu *nouvelle_partie(void);

/* Lance et joue une partie */
enum CASE deroulement_partie(Jeu *jeu, const enum PLAYER_TYPE noir,
                             const enum PLAYER_TYPE blanc,
                             const Test_Data *test);

/* Coups possibles d'un joueur */
struct coups {
    Liste *coups;
    int taille_liste;
};
typedef struct coups Coups;

/* Vérifie si un joueur peut jouer */
Coups *action_possible_joueur(Jeton *plateau[LONGEUR][LARGEUR],
                              const int couleur);

/* Libère les coups possibles de la mémoire  */
void free_coups(Coups *coups);

/* Vérifie si une partie est terminée */
int partie_finie(Jeu *jeu);

/* Compte les points, change le résultat avec le gagnant ainsi que les points de
 * chacun des joueurs (Gagnant, Perdant)
 * Renvoie 0 si égalité entre les 2 joueurs */
int selection_gagnant(const Jeu *jeu, int *resultat);

/* Copie le jeu */
Jeu *copie_jeu(const Jeu *jeu_source);

/* Libère le jeu de la mémoire */
void free_jeu(Jeu *jeu);

#endif
