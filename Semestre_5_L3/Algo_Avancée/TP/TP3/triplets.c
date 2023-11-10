
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
grapheT *new_grapheT(int n) {
    grapheT *grph = malloc(sizeof(*grph));
    grph->nbs = n;
    grph->nba = 0;
    grph->aretes = malloc(sizeof(triplet) * n);
    return grph;
};

void *delete_grapheT(grapheT *grph) {
    free(grph->aretes);
    free(grph);
};

void add_edge_weightT(grapheT *grph, int i, int j, int weight) {
    grph->aretes[grph->nba] = *new_triplet(i, j, weight);
    grph->nba++;
};

void print_edges(grapheT *grph) {
    for (int i = 0; i < grph->nba; i++) {
        printf("arete %d : (%d,%d) poids %d\n", i, grph->aretes[i].i, grph->aretes[i].j, grph->aretes[i].poids);
    }
};

int is_edge_in_grapheT(grapheT *grph, int i, int j) {
    for (int k = 0; k < grph->nba; k++) {
        if (grph->aretes[k].i == i && grph->aretes[k].j == j) {
            return 1;
        }
    }
    return 0;
};

grapheT *remplir_grapheT(int n) {
    grapheT *grph = new_grapheT(n);
    int i, j;
    int weight;
    for (i = 0; i < n; i++) {
        for (j = i; j < n; j++) {
            weight = rand() % 10;
            if (weight != 0) {
                add_edge_weightT(grph, i, j, weight);
            }
        }
    }
    return grph;
};

int minDistance(grapheT *grph, int dist[], int access[]) {
    int min = INF, min_index;
    for (int v = 0; v < grph->nbs; v++) {
        if (access[v] == 0 && dist[v] <= min) {
            min = dist[v];
            min_index = v;
        }
    }
    return min_index;
};

void print_dist(int *tab, int taille, int s) {
    int i;
    printf("Sommets : \t \t");
    for (i = 0; i < taille; i++) {
        printf("%d", i);
        printf(i < taille - 1 ? "\t" : "\n");
    }
    printf("Dist. depuis %d : \t", s);
    for (i = 0; i < taille; i++) {
        printf("%d", tab[i]);
        printf(i < taille - 1 ? "\t" : "\n");
    }
};

void dijkstra_triplet(grapheT *grph, int src) {
    int n = grph->nbs;
    int *dist = malloc(n * sizeof(int));
    int *access = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        dist[i] = INF;
        access[i] = 0;
    }
    dist[src] = 0;
    for (int i = 0; i < n - 1; i++) {
        int u = minDistance(grph, dist, access);
        access[u] = 1;
        for (int j = 0; j < n; j++) {
            if (!access[j] && is_edge_in_grapheT(grph, u, j) && dist[u] != INF && dist[u] + grph->aretes[u].poids < dist[j]) {
                dist[j] = dist[u] + grph->aretes[u].poids;
            }
        }
    }
    print_dist(dist, n, src);
    free(dist);
    free(access);
}; // On pourra utiliser les fonctions d'affichage precedentes.





int main(){
    //// Tests matrices d'adjacence
    grapheT *grph=remplir_grapheT(15);
    print_edges(grph);
    printf("\n \n");
    int s=0;
    printf("Affichage du résultat avec Dijkstra : \n");
    
    clock_t t1, t2;
    t1 = clock();
    dijkstra_triplet(grph,0);
    t2 = clock();
    printf("Temps d'execution Dijkstra: %f secondes\n", (double) (t2 - t1) / CLOCKS_PER_SEC);
    free(grph);


    
    
    return 0;

}

