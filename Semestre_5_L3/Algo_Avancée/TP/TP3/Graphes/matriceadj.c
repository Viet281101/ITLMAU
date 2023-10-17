#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "fifo.h"
#include "affichage.h"
#include "matriceadj.h"



grapheM *new_grapheM(int n){
    int i,j;
    grapheM *grph = malloc(sizeof(*grph));
    grph->vertices = n;
    grph->adj= malloc(sizeof(int*) * n);
    for (i=0; i<n; i++){
        grph->adj[i] = malloc(n* sizeof(int));
    }
    for (i=0; i < n; i++){
        for (j=0; j < n; j++){
           grph->adj[i][j] = 0;
        }
    }
    return grph;
}

void free_graph(grapheM *grph){
    int n=grph->vertices;
    for(int i = 0;i < n;i++){
        free(grph->adj[i]);
    }
    free(grph->adj);
    free(grph);
}

void print_graphe(grapheM *grph){
    printf("Nombre de sommets : %d. \n",grph->vertices);
    printf("Matrice d'adjacence : \n");
    int i,j;
    int n=grph->vertices;
    for(i=0; i<n; i++){
        for(j=0; j<n; j++){
            printf("%d",grph->adj[i][j]);
            printf(j<n-1?"\t":"\n");
            }
    }
}

void add_edge_weight(grapheM *grph, int i, int j, int weight){
    grph->adj[i][j] += weight;
}

void add_edge(grapheM *grph, int i, int j){
    grph->adj[i][j] += 1;
}

/* Fonction permettant de générer un graphe aléatoire, avec un certain taux de zéros. */
grapheM *remplir_grapheM(int n){
    grapheM *grph = new_grapheM(n);
    int i, j;
    float taux = 0.15; // Taux de remplissage souhaité
    srand(time(NULL));
    for (i = 0; i < n; i++){
        for (j = 0; j < n; j++){
            float v = (float)rand() / RAND_MAX;
            if (v < taux) {
                add_edge_weight(grph, i, j, (int)(v * 100.0));
            }
        }
    }
    return grph;
}


/* Fonction permettant de trouver le sommet à plus petite distance parmis les sommets pas encore parcourus,
sans utiliser de file de priorité */
int minDistanceM(grapheM *grph, int dist[], int access[]){
    int n = grph->vertices;
    int min = INF, min_index;
    int i;
    for (int i = 0; i < n; i++){
        if (access[i] == 0 && dist[i] <= min)
            min = dist[i], min_index = i;
    }
    return min_index;
}



//////////// FONCTIONS A ECRIRE //////////////////

void accessibles_mat(grapheM *grph, int src){
    int n = grph->vertices;
    int *access = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++){
        access[i] = 0;
    }
    access[src] = 1;
    fifo *voisins = new_fifo();
    push(voisins, src);
    while (is_empty_fifo(voisins) == 0){
        int s = get_first(voisins);
        enqueue(voisins);
        for (int i = 0; i < n; i++){
            if (grph->adj[s][i] != 0 && access[i] == 0){
                access[i] = 1;
                push(voisins, i);
            }
        }
    }
    print_acc(access, n, src);
    free(access);
};

void dijkstra_mat(grapheM *grph, int src){
    int n = grph->vertices;
    int *dist = malloc(n * sizeof(int));
    int *access = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++){
        dist[i] = INF;
        access[i] = 0;
    }
    dist[src] = 0;
    for (int i = 0; i < n - 1; i++){
        int u = minDistanceM(grph, dist, access);
        access[u] = 1;
        for (int j = 0; j < n; j++){
            if (!access[j] && grph->adj[u][j] && dist[u] != INF && dist[u] + grph->adj[u][j] < dist[j]){
                dist[j] = dist[u] + grph->adj[u][j];
            }
        }
    }
    print_dist(dist, n, src);
    free(dist);
    free(access);
};
