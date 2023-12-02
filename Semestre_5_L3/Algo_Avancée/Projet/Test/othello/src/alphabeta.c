#include "../includes/alphabeta.h"

void action_joueur_alphabeta(Jeu *jeu, const int couleur,
                             const int profondeur) {
    int ligne, colonne, score = INT_MAX;
    _action_joueur_alphabeta(jeu, profondeur, couleur, couleur, &ligne,
                             &colonne, &score, 0, VIDE);

    jeu_joueur(jeu, ligne, colonne, couleur);
}

void _action_joueur_alphabeta(Jeu *jeu, int profondeur, int couleur,
                              const int gagnant, int *ligne, int *colonne,
                              int *score, const int note, const int qui) {
    Coups *possibilites = action_possible_joueur(jeu->plateau, couleur);

    if (!possibilites->taille_liste) {
        free_coups(possibilites);
        couleur = couleur_ennemi(couleur);
        possibilites = action_possible_joueur(jeu->plateau, couleur);

        if (!possibilites->taille_liste) {
            *score = heuristique(jeu, gagnant);
            free_coups(possibilites);

            return;
        }
    }

    if (couleur == gagnant) {
        *score = INT_MIN;
    } else {
        *score = INT_MAX;
    }

    profondeur--;
    int score_tmp, i_tmp, j_tmp;
    for (Element *i = possibilites->coups->premier; i; i = i->suivant) {
        Jeu *jeu_copie = copie_jeu(jeu);
        if (!jeu_joueur(jeu_copie, i->jeton->pos_i, i->jeton->pos_j, couleur)) {
            fprintf(stderr, "Coup illégal.\n");
            exit(EXIT_FAILURE);
        }
        if (profondeur) {
            _action_joueur_alphabeta(jeu_copie, profondeur,
                                     couleur_ennemi(couleur), gagnant, &i_tmp,
                                     &j_tmp, &score_tmp, *score, couleur);
        } else {
            score_tmp = heuristique(jeu_copie, gagnant);
        }

        if (couleur == gagnant) {
            if (qui == couleur_ennemi(gagnant) && score_tmp >= note) {
                while (i->suivant) {
                    if (i->suivant->suivant) {
                        i = i->suivant;
                    } else {
                        break;
                    }
                }
                *score = INT_MAX;
            } else {
                if (score_tmp >= *score) {
                    *score = score_tmp;
                    *ligne = i->jeton->pos_i;
                    *colonne = i->jeton->pos_j;
                    if (*score == INT_MAX) {
                        while (i->suivant) {
                            if (i->suivant->suivant) {
                                i = i->suivant;
                            } else {
                                break;
                            }
                        }
                    }
                }
            }
        } else {
            if (qui == gagnant && score_tmp <= note) {
                while (i->suivant) {
                    if (i->suivant->suivant) {
                        i = i->suivant;
                    } else {
                        break;
                    }
                }
                *score = INT_MIN;
            } else {
                if (score_tmp <= *score) {
                    *score = score_tmp;
                    *ligne = i->jeton->pos_i;
                    *colonne = i->jeton->pos_j;
                    if (*score == INT_MIN) {
                        while (i->suivant) {
                            if (i->suivant->suivant) {
                                i = i->suivant;
                            } else {
                                break;
                            }
                        }
                    }
                }
            }
        }

        free_jeu(jeu_copie);
    }

    free_coups(possibilites);
}
