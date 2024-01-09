
#include <stdio.h>
#include <time.h>
#include "couleur.h"


int tri_a_bulle(int T[], int n);
int tri_a_bulle_cor(int T[], int n);
int tri_a_bulle_opti(int T[], int n);
int permute(int *a, int *b);
//debug
void init_list(int T[], int size);
void print_int_list(int T[], int size);



int main(void) {
    int size = 15;
    int T[size];

    init_list(T, size);
    // print_int_list(T, size);

    clock_t time, time_cor, time_opti;
    time = clock();
    
    //tri a bulle
    printf("\n~~~~~~~~~~~ Tri à bulle ~~~~~~~~~~~~~\n");
    tri_a_bulle(T, size);
    // print_int_list(T, size);
    time = clock() - time;
    double temp_passe = ((double)time) / CLOCKS_PER_SEC;
    printf("Temps d'execution :");
    red();
    printf(" %f\n", temp_passe);
    reset();


    //tri a bulle corrigé
    init_list(T, size);

    time_cor = clock();
    printf("\n~~~~~~~~~~~ Tri à bulle corriger ~~~~~~~~~~~~~\n");
    tri_a_bulle_cor(T, size);
    // print_int_list(T, size);
    time_cor = clock() - time_cor;
    double temp_passe_cor = ((double)time_cor) / CLOCKS_PER_SEC;
    printf("Temps d'execution :");
    red();
    printf(" %f\n", temp_passe_cor);
    reset();


    //tri a bulle opti
    init_list(T, size);
    time_opti = clock();
    printf("\n~~~~~~~~~~~ Tri à bulle optimise ~~~~~~~~~~~~~\n");
    tri_a_bulle_opti(T, size);
    // print_int_list(T, size);
    time_opti = clock() - time_opti;
    double temp_passe_opti = ((double)time_opti) / CLOCKS_PER_SEC;
    printf("Temps d'execution :");
    red();
    printf(" %f\n", temp_passe_opti);
    reset();

    return 0;
}


//// tri à bulle normal
int tri_a_bulle(int T[], int n) {
    for (int i=n ; i > 0 ; i--){
        for(int j = 0 ; j < i-1 ; j++) {
            if(T[j] > T[j+1]){
                permute(&T[j],&T[j+1]);
            }
        }
    }
    return 0;
}


//// tri à bulle coriger :
int tri_a_bulle_cor(int T[], int n) {
    // int temp;
    for (int i = n-1; i > 0; i--) {
        // for (int j = 1; j < i-1; j++) {
        for (int j = 0; j < i; j++) {
            if (T[j] > T[j+1]) {
                // temp = T[j+1];
                // T[j+1] = T[j];
                // T[j] = temp;
                permute(&T[j], &T[j+1]);
            }
        }
    }
    return 0;
}


//// tri à bulle optimizer :
int tri_a_bulle_opti(int T[], int n) {
    for (int i=n ; i > 0 ; i--){
	    int trie=1;
        for(int j = 0 ; j < i-1 ; j++) {
            if(T[j] > T[j+1]){
                permute(&T[j],&T[j+1]);
                trie = 0;
            }
        }
        if (trie == 1){
        	printf("trié avec i=%d\n",i);
			return 0;
		}
    }
    return 0;
}


//// echange:
int permute(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;

    return 0;
}


///// Test :
void init_list(int T[], int size) {
    int init[15] = {4, 6, 1, 5, 3, 4, 8, 2, 8, 9, 10, 19, 13, 18, 25};
    for (int i = 0; i < size; i++) {
        T[i] = init[i];
    }
}

//// debug:
void print_int_list(int T[], int size) {
    printf("T = {");
    for (int i = 0; i < size; i++) {
        printf("%d", T[i]);
        if (i != size-1) printf(",");
    }
    printf("}\n");
}



