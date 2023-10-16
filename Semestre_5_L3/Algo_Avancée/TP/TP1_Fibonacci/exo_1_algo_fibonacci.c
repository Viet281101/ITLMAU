
#include <stdio.h>
#include <time.h>
#include "fibonacci.c"

#define echantillon_max 300

int main(int argc, char **argv) {
    int n, res_ite, res_log, res_vect, res_memo;
    clock_t td, ta;

    for (n = 1; n <= echantillon_max; n += 10) {
        printf("nb : %d  \t", n);

        // Mesure de l'algorithme itératif
        td = clock();
        for (int i = 0; i < n; i++) {
            res_ite = fibo_ite(i);
        }
        ta = clock();
        printf("ite : %d \t", (int)(ta - td));

        // Mesure de l'algorithme vectoriel
        td = clock();
        for (int i = 0; i < n; i++) {
            res_vect = fibo_vect(i);
        }
        ta = clock();
        printf("vect : %d \t", (int)(ta - td));

        // Mesure de l'algorithme logarithmique
        td = clock();
        for (int i = 0; i < n; i++) {
            res_log = fibo_log(i);
        }
        ta = clock();
        printf("log : %d \t", (int)(ta - td));

        // Mesure de l'algorithme avec mémorisation
        td = clock();
        for (int i = 0; i < n; i++) {
            res_memo = fib_incr(i);
        }
        ta = clock();
        printf("memo : %d \t", (int)(ta - td));

        printf("\n");
    }

    return 0;
}
