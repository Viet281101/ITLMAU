#include "../includes/alphabeta.h"
#include "../includes/humain.h"
#include "../includes/minimax.h"

const char *joueur_type_str(const enum PLAYER_TYPE type) {
    switch (type) {
    case HUMAIN:
        return "qu'humain";
    case MINIMAX:
        return "que minimax";
    case ALPHABETA:
        return "qu'alphabêta";
    }

    return "";
}

Jeton *ajoute_jeton(const int pos_i, const int pos_j, const int couleur) {
    Jeton *jeton = malloc(sizeof(Jeton));
    jeton->couleur = couleur;
    jeton->pos_i = pos_i;
    jeton->pos_j = pos_j;

    return jeton;
}

void affiche_jeton(FILE *stream, const Jeton *jeton) {
    fprintf(stream, "%c%d", jeton->pos_j + 'A', jeton->pos_i + 1);
}

Jeu *nouvelle_partie(void) {
    Jeu *jeu = malloc(sizeof(Jeu));
    jeu->j1 = nouveau_joueur(NOIR);
    jeu->j2 = nouveau_joueur(BLANC);

    remplissage_debut(jeu);

    return jeu;
}

enum CASE deroulement_partie(Jeu *jeu, const enum PLAYER_TYPE type_noir,
                             const enum PLAYER_TYPE type_blanc,
                             const Test_Data *test) {
    Joueur *tour = jeu->j1->couleur == NOIR ? jeu->j1 : jeu->j2;

    while (!partie_finie(jeu)) {
        if (!test->test) {
            affiche_plateau(jeu->plateau);
        }

        Coups *possibilites =
            action_possible_joueur(jeu->plateau, tour->couleur);
        if (possibilites->taille_liste > 0) {
            // Si le joueur peut jouer
            if (!test->test) {
                printf("Tour des jetons %ss !\n", tour->nom);
            }

            if (tour->couleur == NOIR) {
                switch (type_noir) {
                case HUMAIN:
                    printf("Coups possibles (%d) : ",
                           possibilites->taille_liste);
                    affiche_liste(possibilites->coups->premier);
                    printf("\n");
                    action_joueur_humain(jeu, tour->couleur);
                    break;
                case MINIMAX:
                    action_joueur_minimax(jeu, tour->couleur,
                                          test->profondeur_minimax);
                    break;
                case ALPHABETA:
                    action_joueur_alphabeta(jeu, tour->couleur,
                                            test->profondeur_alphabeta);
                    break;
                default:
                    fprintf(stderr, "Erreur: Joueur noir non supporté.");
                    exit(1);
                }
            } else {

                switch (type_blanc) {
                case HUMAIN:
                    printf("Coups possibles (%d) : ",
                           possibilites->taille_liste);
                    affiche_liste(possibilites->coups->premier);
                    printf("\n");
                    action_joueur_humain(jeu, tour->couleur);
                    break;
                case MINIMAX:
                    action_joueur_minimax(jeu, tour->couleur,
                                          test->profondeur_minimax);
                    break;
                case ALPHABETA:
                    action_joueur_alphabeta(jeu, tour->couleur,
                                            test->profondeur_alphabeta);
                    break;
                default:
                    fprintf(stderr, "Erreur: Joueur blanc non supporté.");
                }
            }
        } else {
            if (!test->test) {
                printf("Pas de coup jouable.\n");
            }
        }
        free_coups(possibilites);

        // On passe la main à l'autre joueur
        tour = jeu->j1->couleur == tour->couleur ? jeu->j2 : jeu->j1;
    }

    if (!test->test) {
        affiche_plateau(jeu->plateau);
    }

    int resultat[3];
    if (selection_gagnant(jeu, resultat)) {
        Joueur *gagnant = jeu->j1->couleur == resultat[0] ? jeu->j1 : jeu->j2;
        if (!test->test) {
            printf("Fin de partie ! Le joueur %s a gagné %d contre %d !\n",
                   gagnant->nom, resultat[1], resultat[2]);
        }

        return gagnant->couleur;
    } else {
        if (!test->test) {
            printf("Égalité parfaite, %d contre %d !\n", jeu->j1->nb_jeton,
                   jeu->j2->nb_jeton);
        }

        return VIDE;
    }
}

Coups *action_possible_joueur(Jeton *plat[LONGEUR][LARGEUR],
                              const int couleur) {
    Coups *coups = malloc(sizeof(Coups));
    coups->coups = nouvelle_liste();
    coups->taille_liste = 0;

    for (int i = 0; i < LONGEUR; i++) {
        for (int j = 0; j < LARGEUR; j++) {
            if (case_jouable(plat, i, j, couleur)) {
                ajoute_liste(coups->coups, nouvel_element(plat[i][j]));
                coups->taille_liste++;
            }
        }
    }

    return coups;
}

void free_coups(Coups *coups) {
    free_liste(coups->coups);
    free(coups);
}

int partie_finie(Jeu *jeu) {
    Coups *possibilites_j1 = action_possible_joueur(jeu->plateau, NOIR);
    Coups *possibilites_j2 = action_possible_joueur(jeu->plateau, BLANC);
    int reponse = ((possibilites_j1->taille_liste == 0) &&
                   (possibilites_j2->taille_liste == 0)) ||
                  plateau_rempli(jeu->plateau);

    free_coups(possibilites_j1);
    free_coups(possibilites_j2);

    return reponse;
}

int selection_gagnant(const Jeu *jeu, int *resultat) {
    if (jeu->j1->nb_jeton == jeu->j2->nb_jeton) {
        // Si égalité
        return 0;
    }

    if (jeu->j1->nb_jeton > jeu->j2->nb_jeton) {
        // Si le joueur 1 a gagné
        resultat[0] = jeu->j1->couleur;
        resultat[1] = jeu->j1->nb_jeton;
        resultat[2] = jeu->j2->nb_jeton;
    } else {
        // Si le joueur 2 a gagné
        resultat[0] = jeu->j2->couleur;
        resultat[1] = jeu->j2->nb_jeton;
        resultat[2] = jeu->j1->nb_jeton;
    }

    return 1;
}

Jeu *copie_jeu(const Jeu *source) {
    Jeu *res = malloc(sizeof(Jeu));

    // Copie de J1
    res->j1 = malloc(sizeof(Joueur));
    res->j1->nom = source->j1->nom;
    res->j1->couleur = source->j1->couleur;
    res->j1->liste_jeton = copie_liste(source->j1->liste_jeton);
    res->j1->nb_jeton = source->j1->nb_jeton;

    // Copie de J2
    res->j2 = malloc(sizeof(Joueur));
    res->j2->nom = source->j2->nom;
    res->j2->couleur = source->j2->couleur;
    res->j2->liste_jeton = copie_liste(source->j2->liste_jeton);
    res->j2->nb_jeton = source->j2->nb_jeton;

    // Copie du plateau
    for (int i = 0; i < LONGEUR; ++i) {
        for (int j = 0; j < LARGEUR; ++j) {
            Jeton *jeton = malloc(sizeof(Jeton));
            jeton->couleur = source->plateau[i][j]->couleur;
            jeton->pos_i = source->plateau[i][j]->pos_i;
            jeton->pos_j = source->plateau[i][j]->pos_j;

            res->plateau[i][j] = jeton;
        }
    }

    return res;
}

void free_jeu(Jeu *jeu) {
    free_liste(jeu->j1->liste_jeton);
    free(jeu->j1);

    free_liste(jeu->j2->liste_jeton);
    free(jeu->j2);

    for (int i = 0; i < LONGEUR; ++i) {
        for (int j = 0; j < LARGEUR; ++j) {
            free(jeu->plateau[i][j]);
        }
    }

    free(jeu);
}
