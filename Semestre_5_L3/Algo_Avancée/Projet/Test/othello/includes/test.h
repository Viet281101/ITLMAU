#ifndef OTHELLO_TEST_H
#define OTHELLO_TEST_H 1

#include <time.h>

struct test_data {
    int test;
    int profondeur_minimax;
    int profondeur_alphabeta;
};
typedef struct test_data Test_Data;

/* Initialise un Test_Data */
Test_Data *nouveau_test_data(int test, int profondeur_minimax,
                             int profondeur_alphabeta);

/* Libère un Test_Data de la mémoire */
void free_test_data(Test_Data *test_data);

/* Lance les différents tests */
void run_tests(void);

/* Test par rapport à la vitesse d'éxécution */
void speed_test(int profondeur_max_minimax, int profondeur_max_alphabeta);

/* Test par rapport à qui gagne */
void winrate_test(int profondeur_max_minimax, int profondeur_max_alphabeta);

#endif
