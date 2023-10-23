
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define INF 9999


/* Structure de graphe */
typedef struct triplet{
   int i;
   int j;
   int poids;
} triplet;

triplet *new_triplet(int i,int j, int poids){
    triplet *t=malloc(sizeof(*t));
    t->i = i;
    t->j= j;
    t->poids = poids;
    return t;
}

typedef struct grapheT {
   int nbs; /* nombre de sommets*/
   int nba; /* nombre d aretes*/
   triplet * aretes; /* vecteur d aretes*/
} grapheT;



/* Prototypes des fonctions à écrire */
grapheT *new_grapheT(int n);
void *delete_grapheT(grapheT *grph);
void add_edge_weightT(grapheT *grph, int i, int j, int weight);
void print_edges(grapheT *grph);
int is_edge_in_grapheT(grapheT *grph, int i, int j);
grapheT *remplir_grapheT(int n);
int minDistance(grapheT *grph, int dist[], int access[]);
void dijkstra_triplet(grapheT *grph, int src); // On pourra utiliser les fonctions d'affichage precedentes.




int main(){
    return 0;
}

