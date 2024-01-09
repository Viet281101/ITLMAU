#include <string.h>

#include "../includes/jeu.h"
#include "../includes/test.h"

/* Affiche un message d'aide */
void help(char const progName[]);

int main(int argc, char const *argv[]) {
    enum PLAYER_TYPE noirs;
    enum PLAYER_TYPE blancs;

    if (argc < 2) { // si aucun argument
        fprintf(stderr, "Aucun argument n'a été renseigné.\n");
        // Affichage du message d'aide
        help(argv[0]);
        exit(EXIT_FAILURE);
    }

    if (argc == 2) { // si un seul argument de renseigné
        if (strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "-h") == 0) {
            // Affiche le message d'aide
            help(argv[0]);
            exit(EXIT_SUCCESS);
        } else {
            if (strcmp(argv[1], "--test") == 0 || strcmp(argv[1], "-t") == 0) {
                run_tests();
                exit(EXIT_SUCCESS);
            } else {
                fprintf(stderr, "Il manque des arguments.\n");
                // Affichage du message d'aide
                help(argv[0]);
                exit(EXIT_FAILURE);
            }
        }
    }
    if (argc == 3) { // s'il y a 2 arguments
        // Concernant les noirs
        if (strcmp(argv[1], "humain") == 0 || strcmp(argv[1], "h") == 0) {
            noirs = HUMAIN;
        } else {
            if (strcmp(argv[1], "minimax") == 0 || strcmp(argv[1], "m") == 0) {
                noirs = MINIMAX;
            } else {
                if (strcmp(argv[1], "alphabeta") == 0 ||
                    strcmp(argv[1], "a") == 0) {
                    noirs = ALPHABETA;
                } else {
                    fprintf(stderr, "Le joueur 1 n'a pas été reconnu.\n");
                    // Affichage du message d'aide
                    help(argv[0]);
                    exit(EXIT_FAILURE);
                }
            }
        }

        // Concernant les blancs
        if (strcmp(argv[2], "humain") == 0 || strcmp(argv[2], "h") == 0) {
            blancs = HUMAIN;
        } else {
            if (strcmp(argv[2], "minimax") == 0 || strcmp(argv[2], "m") == 0) {
                blancs = MINIMAX;
            } else {
                if (strcmp(argv[2], "alphabeta") == 0 ||
                    strcmp(argv[2], "a") == 0) {
                    blancs = ALPHABETA;
                } else {
                    fprintf(stderr, "Le joueur 2 n'a pas été reconnu.\n");
                    // Affichage du message d'aide
                    help(argv[0]);
                    exit(EXIT_FAILURE);
                }
            }
        }

        Jeu *jeu = nouvelle_partie();
        Test_Data *test = nouveau_test_data(0, 4, 6);

        printf("Le jeu commence avec les noirs en tant %s et les blancs en "
               "tant %s.\n",
               joueur_type_str(noirs), joueur_type_str(blancs));

        deroulement_partie(jeu, noirs, blancs, test);

        free_jeu(jeu);
        free_test_data(test);

        return EXIT_SUCCESS;
    }

    fprintf(stderr, "Trop d'arguments renseignés.\n");
    // Affichage du message d'aide
    help(argv[0]);
    return EXIT_FAILURE;
}

void help(char const progName[]) {
    printf("=========================== OTELLO ===========================\n");
    printf(
        "-> %s <N> <B>  || Lance le jeu avec les N(oirs) et les B(blancs) :\n"
        "\t\t\t\t- humain\t - h\n"
        "\t\t\t\t- minimax\t - m\n"
        "\t\t\t\t- alphabeta\t - a\n"
        "\t\t\t\t=> exemple : %s humain alphabeta\n",
        progName, progName);
    printf("-> %s -t, --test || Test l'efficacité des IA.\n", progName);
    printf("-> %s -h, --help || Affiche ce message d'aide.\n", progName);
    printf("==============================================================\n");
}
