#include "../includes/jeu.h"
#include <stdio.h>
#include <time.h>

Test_Data *nouveau_test_data(int test, int profondeur_minimax,
                             int profondeur_alphabeta) {
    Test_Data *res = malloc(sizeof(Test_Data));

    res->test = test;
    res->profondeur_minimax = profondeur_minimax;
    res->profondeur_alphabeta = profondeur_alphabeta;

    return res;
}

void free_test_data(Test_Data *test_data) { free(test_data); }

void run_tests(void) {
    speed_test(6, 8);
    winrate_test(5, 7);
}

void speed_test(int profondeur_max_minimax, int profondeur_max_alphabeta) {
    int repetions = 5;

    printf("Lancement des tests, on va jusqu'à une profondeur de %d avec une "
           "moyenne de %d répétitions.\n",
           profondeur_max_alphabeta, repetions);
    printf("On fait jouer alpha-bêta contre lui-même puis minimax contre "
           "lui-même.\n");

    clock_t t0;
    double delta1, delta2, precedent = 0, actuel = 0;
    for (int i = 1; i < profondeur_max_alphabeta + 1; ++i) {
        delta1 = 0;
        for (int j = 0; j < repetions; ++j) {
            Jeu *jeu = nouvelle_partie();

            Test_Data *test = nouveau_test_data(1, 0, i);

            t0 = clock();

            // Lance le jeu en mode test avec 2 alpha-bêta
            deroulement_partie(jeu, ALPHABETA, ALPHABETA, test);

            delta1 += ((double)(clock() - t0)) / CLOCKS_PER_SEC;

            free_jeu(jeu);
            free_test_data(test);
        }
        delta1 /= repetions;

        printf("Profondeur de %d (moyenne de %d tests) ->\t alpha-bêta = %fs\t",
               i, repetions, delta1);

        if (i < profondeur_max_minimax) {
            // On ne calcul que Minimax avec une petite profondeur parce que
            // sinon c'est trop long
            delta2 = 0;
            for (int j = 0; j < repetions; ++j) {
                Jeu *jeu = nouvelle_partie();

                Test_Data *test = nouveau_test_data(1, i, 0);

                t0 = clock();

                // Lance le jeu en mode test avec 2 alpha-bêta
                deroulement_partie(jeu, MINIMAX, MINIMAX, test);

                delta2 += ((double)(clock() - t0)) / CLOCKS_PER_SEC;

                free_jeu(jeu);
                free_test_data(test);
            }
            delta2 /= repetions;

            actuel = delta2 - delta1;
            printf("| minimax = %fs\t | différence (m - a) = %fs", delta2,
                   actuel);
        }
        if (i > 1 && i < profondeur_max_minimax) {
            printf("\tavec le précédent = %fs\n", actuel - precedent);
        } else {
            printf("\n");
        }
        precedent = actuel;
    }
}

void winrate_test(int profondeur_max_minimax, int profondeur_max_alphabeta) {
    int nb_tests = 0;

    int nb_victoire_minimax = 0, nb_victoire_alphabeta = 0, nb_egalite = 0;
    for (int i = 1; i < profondeur_max_alphabeta; ++i) {
        for (int j = 1; j < profondeur_max_minimax; ++j, ++nb_tests) {
            Jeu *jeu = nouvelle_partie();
            Test_Data *test = nouveau_test_data(1, j, i);

            // On alterne qui commence le jeu
            int joueur_noir = i % 2 ? MINIMAX : ALPHABETA;
            int joueur_blanc = joueur_noir == MINIMAX ? ALPHABETA : MINIMAX;

            int res;
            switch (res = deroulement_partie(jeu, joueur_noir, joueur_blanc,
                                             test)) {
            case VIDE:
                nb_egalite++;
                break;
            case NOIR:
                if (joueur_noir == MINIMAX) {
                    nb_victoire_minimax++;
                    printf(
                        "Minimax\t\ta gagné (profondeur minimax = %d vs %d = "
                        "profondeur alphabêta) en tant que noir\n",
                        j, i);
                } else {
                    nb_victoire_alphabeta++;
                    printf(
                        "Alpha-bêta\ta gagné (profondeur minimax = %d vs %d = "
                        "profondeur alphabêta) en tant que noir\n",
                        j, i);
                }
                break;
            case BLANC:
                if (joueur_blanc == MINIMAX) {
                    nb_victoire_minimax++;
                    printf(
                        "Minimax\t\ta gagné (profondeur minimax = %d vs %d = "
                        "profondeur alphabêta) en tant que blanc\n",
                        j, i);
                } else {
                    nb_victoire_alphabeta++;
                    printf(
                        "Alpha-bêta\ta gagné (profondeur minimax = %d vs %d = "
                        "profondeur alphabêta) en tant que blanc\n",
                        j, i);
                }
                break;
            default:
                fprintf(stderr,
                        "Une erreur est survenue lors des tests de victoire "
                        "'%c'.\n",
                        res);
                exit(1);
            }

            free_jeu(jeu);
            free_test_data(test);
        }
    }

    printf("Nombre totale de parties : %d.\n", nb_tests);
    printf("Alpha-bêta a gagné\t%d fois.\n", nb_victoire_alphabeta);
    printf("Minimax a gagné\t\t%d fois.\n", nb_victoire_minimax);
    printf("Il y a eu\t\t%d égalités.\n", nb_egalite);
}
