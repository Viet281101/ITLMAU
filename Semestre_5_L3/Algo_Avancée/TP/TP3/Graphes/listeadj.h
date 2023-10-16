#include <stdio.h>
#include <stdlib.h>
#include<time.h>

#define INF 9999


/* Structure de liste d'adjacence */
typedef struct noeudListeAdj{
    int but;
    int poids;
    struct noeudListeAdj* suivant;
} noeudListeAdj;


typedef struct ListeAdj{
   struct noeudListeAdj* head;
} ListeAdj;


typedef struct grapheL{
    int vertices;
    struct ListeAdj* array;
} grapheL;


int is_empty_adjlist(ListeAdj L);
noeudListeAdj *new_noeudListeAdj(int but, int poids);
grapheL *new_grapheL(int n);
void add_edge_weightL(grapheL *grph, int src, int but, int poids);
int is_edge_in_adjlist(grapheL *grph,int i,int j);
void print_adjlist(struct grapheL* grph);
grapheL *remplir_grapheL(int n);
void accessibles_list(struct grapheL* grph, int s);
int minDistanceL(grapheL *grph, int dist[], int access[]);
void dijkstra_list(grapheL *grph, int src);
void dijkstra_list_prio(grapheL* grph, int src);

