#include "../includes/minimax.h"

void action_joueur_minimax(Jeu *jeu, const int couleur, const int profondeur) {
    int ligne, colonne, score = INT_MAX;
    _action_joueur_minimax(jeu, profondeur, couleur, couleur, &ligne, &colonne,
                           &score);

    jeu_joueur(jeu, ligne, colonne, couleur);
}

void _action_joueur_minimax(Jeu *jeu, int profondeur, int couleur,
                            const int gagnant, int *ligne, int *colonne,
                            int *score) {
    Coups *possibilites = action_possible_joueur(jeu->plateau, couleur);

    // Pas de coups possibles
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
            _action_joueur_minimax(jeu_copie, profondeur,
                                   couleur_ennemi(couleur), gagnant, &i_tmp,
                                   &j_tmp, &score_tmp);
        } else {
            score_tmp = heuristique(jeu_copie, gagnant);
        }
        if (couleur == gagnant) { // MAX
            if (score_tmp >= *score) {
                // On change notre coup s'il est meilleur
                *score = score_tmp;
                *ligne = i->jeton->pos_i;
                *colonne = i->jeton->pos_j;
            }

        } else { // MIN
            if (score_tmp <= *score) {
                // On change notre coup s'il est + désavantageux pour
                // l'adversaire
                *score = score_tmp;
                *ligne = i->jeton->pos_i;
                *colonne = i->jeton->pos_j;
            }
        }

        free_jeu(jeu_copie);
    }

    free_coups(possibilites);
}

int heuristique(const Jeu *jeu, const int couleur) {
    if (jeu->j1->couleur == couleur) {
        // Si on est le joueur 1
        return jeu->j1->nb_jeton - jeu->j2->nb_jeton;
    }
    return jeu->j2->nb_jeton - jeu->j1->nb_jeton;
}
