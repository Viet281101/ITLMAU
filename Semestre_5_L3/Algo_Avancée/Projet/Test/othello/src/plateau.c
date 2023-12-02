#include "../includes/joueur.h"

void remplissage_debut(Jeu *jeu) {
    if (LONGEUR * LONGEUR <= 4) {
        fprintf(stderr, "Impossible de jouer dans un plateau aussi petit.");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < LONGEUR; ++i) {
        for (int j = 0; j < LARGEUR; ++j) {
            jeu->plateau[i][j] = ajoute_jeton(i, j, VIDE);
        }
    }

    ajoute_jeton_joueur(jeu->j2,
                        jeu->plateau[LONGEUR / 2 - 1][LARGEUR / 2 - 1]);

    ajoute_jeton_joueur(jeu->j1, jeu->plateau[LONGEUR / 2 - 1][LARGEUR / 2]);

    ajoute_jeton_joueur(jeu->j2, jeu->plateau[LONGEUR / 2][LARGEUR / 2]);

    ajoute_jeton_joueur(jeu->j1, jeu->plateau[LONGEUR / 2][LARGEUR / 2 - 1]);
}

void affiche_plateau(Jeton *plat[LONGEUR][LARGEUR]) {
    // TODO (enhancement): Instead of print instantly, store everything in a
    // table and print the whole thing once?
    _affiche_lettres();

    for (int i = 0; i < LONGEUR * 2 + 1; ++i) {
        for (int j = 0; j < LARGEUR; ++j) {
            int alterne = i % 2;
            int num_ligne = (i / 2) + 1;
            if (j == 0) {
                if (alterne) {
                    printf("%d ", num_ligne);
                } else {
                    printf("  ");
                }
            }

            if (!alterne)
                printf("+---");
            else {
                printf("| %c ", plat[i / 2][j]->couleur);
            }

            if (j == LARGEUR - 1) {
                printf(alterne ? "%c %d\n" : "%c\n", alterne ? '|' : '+',
                       num_ligne);
            }
        }
    }

    _affiche_lettres();
}

void _affiche_lettres(void) {
    printf("  ");
    for (int debut = 'A', i = debut; i < LARGEUR + debut; ++i) {
        printf("  %c ", i);
    }
    printf("\n");
}

int case_jouable(Jeton *plat[LONGEUR][LARGEUR], const int case_i,
                 const int case_j, const int couleur) {
    int flag = 0;

    // Coup illégal
    if (plat[case_i][case_j]->couleur == NOIR ||
        plat[case_i][case_j]->couleur == BLANC) {
        return flag;
    }

    // Regarde dans toutes les directions
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            if (i != 0 || j != 0) {
                if (_case_jouable(plat, case_i, case_j, i, j, couleur) &&
                    plat[case_i + i][case_j + j]->couleur ==
                        couleur_ennemi(couleur)) {
                    flag = 1;
                }
            }
        }
    }

    return flag;
}

int _case_jouable(Jeton *plat[LONGEUR][LARGEUR], const int case_i,
                  const int case_j, const int case_i_direction,
                  const int case_j_direction, const int couleur) {
    if (case_i + case_i_direction < 0 || case_i + case_i_direction >= LONGEUR ||
        case_j + case_j_direction < 0 || case_j + case_j_direction >= LARGEUR) {
        // Après une suite de pion ennemi, si l'on arrive à l'extérieur du
        // plateau ce n'est pas valide
        return 0;
    }

    // S'il y a un pion ennemi
    if (plat[case_i + case_i_direction][case_j + case_j_direction]->couleur ==
        (couleur_ennemi(couleur))) {
        return _case_jouable(plat, case_i + case_i_direction,
                             case_j + case_j_direction, case_i_direction,
                             case_j_direction, couleur);
    }

    // Si c'est bon
    if (plat[case_i + case_i_direction][case_j + case_j_direction]->couleur ==
        couleur) {
        return 1;
    }

    // Couleur vide
    return 0;
}

int plateau_rempli(Jeton *plat[LONGEUR][LARGEUR]) {
    for (int i = 0; i < LONGEUR; ++i) {
        for (int j = 0; j < LARGEUR; ++j) {
            if (plat[i][j]->couleur == VIDE) {
                return 0;
            }
        }
    }

    return 1;
}
