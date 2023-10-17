#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define INF 9999

// Structure de graphe avec matrice d'adjacence //
typedef struct grapheM{
    int vertices;
    int **adj;
} grapheM;


grapheM *new_grapheM(int n);
void free_graph(grapheM *grph);
void print_graphe(grapheM *grph);
void add_edge_weight(grapheM *grph, int i, int j, int weight);
void add_edge(grapheM *grph, int i, int j);
grapheM *remplir_grapheM(int n);
void accessibles_mat(grapheM *grph, int src);
int minDistanceM(grapheM *grph, int dist[], int access[]);
void dijkstra_mat(grapheM *grph, int src);