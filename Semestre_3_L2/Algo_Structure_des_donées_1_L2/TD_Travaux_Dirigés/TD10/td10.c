
#include <stdio.h>


/*
EX 1: (en papier)

EX 2: (en papier)
*/

//// EX 3:

#define MAX_NOEUD 40
typedef struct s_graphe_t{
    int n; // nombre de noeud de 0 à n-1
    int liste[MAX_NOEUD][MAX_NOEUD];
    // chaque ligne représente une liste d'adjacence terminée par la valeur -1
    // si liste[O][1] contient 3 (et que liste[0][0] ne contient pas -1) cela signifie que
    // le sommet 3 est un sucesseur direct du sommet 0
} graphe_t;

void parcoursProfR(graphe_t * g, int d, int * marques){
    if (marques[d] != 0) //// si d déjà recontré
    { 
        printf("%d ", d); //// revisite de d
        return;
    }
    printf("%d ", d); //// previsite de d
    marques[d] = 1;

    for ( int i = 0; g -> liste[d][i] != -1; i++)
    {
        parcoursProfR(g, g -> liste[d][i], marques);
    }
    printf("%d ", d); //// post-visite de d
}

void parcoursProf(graphe_t * g, int d){
    int marques[ g -> n];
    int i;
    for ( i = 0; i < g -> n; i++ ){
        marques[i] = 0;
    }
    parcoursProfR(g, d, marques);
}
