#include <stdio.h>
#include <stdlib.h>
#include<time.h>

#include "affichage.h"


/* Affichage du tableau des accessibles */
void print_acc(int *tab, int taille, int s){
    int i;
    printf("Sommets : \t \t");
    for (i=0; i < taille; i++){
        printf("%d",i);
        printf(i<taille-1?"\t":"\n");
    }
    printf("Acc. depuis %d : \t",s);
    for (i=0; i< taille; i++){
        printf("%d",tab[i]);
        printf(i<taille-1?"\t":"\n");
    }
}

/* Affichage du tableau des distances */
void print_dist(int *tab, int taille, int s){
    int i;
    printf("Sommets : \t \t");
    for (i=0; i < taille; i++){
        printf("%d",i);
        printf(i<taille-1?"\t":"\n");
    }
    printf("Dist. depuis %d : \t",s);
    for (i=0; i< taille; i++){
        printf("%d",tab[i]);
        printf(i<taille-1?"\t":"\n");
    }
}