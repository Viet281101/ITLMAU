#include "../includes/joueur.h"

Joueur *nouveau_joueur(const int pion) {
    Joueur *joueur = malloc(sizeof(Joueur));
    joueur->nom = pion == NOIR ? "noir" : "blanc";
    joueur->couleur = pion;
    joueur->liste_jeton = nouvelle_liste();
    joueur->nb_jeton = 0;

    return joueur;
}

void ajoute_jeton_joueur(Joueur *joueur, Jeton *jeton) {
    // Change le jeton
    jeton->couleur = joueur->couleur;

    // Ajoute le jeton à la liste des jetons du joueur
    Element *element = nouvel_element(jeton);
    ajoute_liste(joueur->liste_jeton, element);
    joueur->nb_jeton++;
}

void retire_jeton_joueur(Joueur *joueur, Jeton *jeton) {
    Element *tmp = joueur->liste_jeton->premier;
    if (tmp->jeton->pos_i == jeton->pos_i &&
        tmp->jeton->pos_j == jeton->pos_j) {
        joueur->liste_jeton->premier = tmp->suivant;
        free(tmp);
    } else {
        supprime_liste(tmp, jeton);
    }
    joueur->nb_jeton--;
    jeton->couleur = VIDE;
}

int couleur_ennemi(const int couleur) { return couleur == NOIR ? BLANC : NOIR; }

int jeu_joueur(Jeu *jeu, const int case_i, const int case_j,
               const int couleur) {
    int flag = 0;

    // Coup illégal
    if (jeu->plateau[case_i][case_j]->couleur == NOIR ||
        jeu->plateau[case_i][case_j]->couleur == BLANC) {
        return flag;
    }

    // Regarde dans toutes les directions
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            if (i != 0 || j != 0) {
                if (_case_jouable(jeu->plateau, case_i, case_j, i, j,
                                  couleur) &&
                    jeu->plateau[case_i + i][case_j + j]->couleur ==
                        couleur_ennemi(couleur)) {
                    _jeu_joueur(jeu, case_i, case_j, i, j, couleur);
                    flag = 1;
                }
            }
        }
    }

    // Case actuelle
    if (flag) {
        jeu->plateau[case_i][case_j]->couleur = couleur;
        if (couleur == NOIR) {
            ajoute_jeton_joueur(jeu->j1, jeu->plateau[case_i][case_j]);
        } else {
            ajoute_jeton_joueur(jeu->j2, jeu->plateau[case_i][case_j]);
        }
    }

    return flag;
}

void _jeu_joueur(Jeu *jeu, const int case_i, const int case_j,
                 const int case_i_direction, const int case_j_direction,
                 const int couleur) {
    if (case_i + case_i_direction < 0 || case_i + case_i_direction >= LONGEUR ||
        case_j + case_j_direction < 0 || case_j + case_j_direction >= LARGEUR) {
        // Après une suite de pion ennemi, si l'on arrive à l'extérieur du
        // plateau ce n'est pas valide
        return;
    }
    if (jeu->plateau[case_i + case_i_direction][case_j + case_j_direction]
            ->couleur == couleur_ennemi(couleur)) {
        jeu->plateau[case_i + case_i_direction][case_j + case_j_direction]
            ->couleur = couleur;

        Joueur *joueur, *adversaire;
        if (couleur == NOIR) {
            joueur = jeu->j1;
            adversaire = jeu->j2;
        } else {
            joueur = jeu->j2;
            adversaire = jeu->j1;
        }

        // Retire le jeton de l'adversaire
        retire_jeton_joueur(
            adversaire,
            jeu->plateau[case_i + case_i_direction][case_j + case_j_direction]);

        // Ajoute le jeton du joueur
        ajoute_jeton_joueur(
            joueur,
            jeu->plateau[case_i + case_i_direction][case_j + case_j_direction]);

        _jeu_joueur(jeu, case_i + case_i_direction, case_j + case_j_direction,
                    case_i_direction, case_j_direction, couleur);
    }
}
