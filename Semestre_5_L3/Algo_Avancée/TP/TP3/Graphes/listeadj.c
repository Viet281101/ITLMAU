#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include<time.h>

#include "fifo.h"
#include "affichage.h"
#include "heap.h"
#include "listeadj.h"



/* Crée un noeud de liste d'adjacence */
noeudListeAdj *new_noeudListeAdj(int but, int poids){
    noeudListeAdj *noeud = malloc(sizeof(*noeud));
    noeud->but = but;
    noeud->poids = poids;
    noeud->suivant = NULL;
    return noeud;
}

/* Fonction qui détermine si une liste d'adjacence est vide*/
int is_empty_adjlist(ListeAdj L){
    return L.head == NULL;
}

/* Fonction qui crée un grapheL vide à n sommets. */
grapheL *new_grapheL(int n){
    grapheL *grph = malloc(sizeof(*grph));
    grph->vertices = n;
    grph->array = (ListeAdj*) malloc(n * sizeof(struct ListeAdj));
    for (int i = 0; i < n; ++i)
        grph->array[i].head = NULL;
    return grph;
}

void add_edge_weightL(grapheL *grph, int src, int but, int poids){
    if (poids == 0)
        return;
    noeudListeAdj *noeud = new_noeudListeAdj(but, poids);
    noeud->suivant = grph->array[src].head;
    grph->array[src].head = noeud;
}

/* Fonction qui teste si il y a une arête de i vers j dans le graphe,
renvoie le poids de l'arête si oui et 0 sinon. */
int is_edge_in_adjlist(grapheL *grph,int i,int j){
    int test = 0;
    noeudListeAdj *n = grph->array[i].head;
    while (n != NULL && test == 0){
        if (n->but == j)
            test = n->poids;
        n=n->suivant;
    }
    return test;
}


/* Affichage des listes d'adjacence d'un graphe */
void print_adjlist(struct grapheL* grph){
    int v;
    for (v = 0; v < grph->vertices; v++) {
        noeudListeAdj* temp = grph->array[v].head;
        printf("\n Liste d'adjacence de %d : \n head ", v);
        while (temp != NULL){
            printf("-> (%d, %d)", temp->but, temp->poids);
            temp = temp->suivant;
        }
        printf("\n");
    }
}

/* Génération d'un graphe aléatoire, avec un certain taux de 0. */
grapheL *remplir_grapheL(int n){
    grapheL *grph = new_grapheL(n);
    int i, j;
    float taux = 0.25; // Taux de remplissage souhaité
    srand(time(NULL));
    for (i = 0; i < n; i++){
        for (j = 0; j < n; j++){
            float v = (float)rand() / RAND_MAX;
            if (v < taux) {
                add_edge_weightL(grph, i, j, (int)(v * 100.0));
            }
        }
    }
    return grph;
}


int minDistanceL(grapheL *grph, int dist[], int access[])
{
    int n = grph->vertices;
    int min = INF, min_index;
    int i;
    for (int i = 0; i < n; i++)
        if (access[i] == 0 && dist[i] <= min)
            min = dist[i], min_index = i;
    return min_index;
}

///////// FONCTIONS A ECRIRE //////////////


void accessibles_list(struct grapheL* grph, int s) {
    int *visited = calloc(grph->vertices, sizeof(int));
    fifo *queue = new_fifo();

    visited[s] = 1;
    push(queue, s);

    while (!is_empty_fifo(queue)) {
        int currentVertex = get_first(queue);
        enqueue(queue);

        noeudListeAdj* temp = grph->array[currentVertex].head;
        while (temp != NULL) {
            int adjVertex = temp->but;
            if (visited[adjVertex] == 0) {
                visited[adjVertex] = 1;
                push(queue, adjVertex);
            }
            temp = temp->suivant;
        }
    }

    printf("Les sommets sont accessibles par le haut %d: ", s);
    for (int i = 0; i < grph->vertices; i++) {
        if (visited[i]) {
            printf("%d ", i);
        }
    }
    printf("\n");

    free(visited);
    while (!is_empty_fifo(queue)) {
        enqueue(queue);
    }
    free(queue);
}

void dijkstra_list_prio(grapheL* grph, int src) {
    int n = grph->vertices;
    int dist[n];
    int access[n];
    int i;
    for (i = 0; i < n; i++) {
        dist[i] = INF;
        access[i] = 0;
    }
    dist[src] = 0;
    Tas *tas = creer_tas(n);
    for (i = 0; i < n; i++) {
        tas->array[i] = new_noeudTas(i, dist[i]);
        tas->pos[i] = i;
    }
    tas->taille = n;
    decrease_value(tas, src, dist[src]);
    while (!is_empty_tas(tas)) {
        noeudTas *noeud = extract_min(tas);
        int u = noeud->v;
        access[u] = 1;
        noeudListeAdj *n = grph->array[u].head;
        while (n != NULL) {
            int v = n->but;
            if (access[v] == 0 && dist[u] != INF && dist[u] + n->poids < dist[v]) {
                dist[v] = dist[u] + n->poids;
                decrease_value(tas, v, dist[v]);
            }
            n = n->suivant;
        }
    }
    print_dist(dist, n, src);
};

/* Implémente l'algorithme de Dijkstra en utilisant la fonction minDistanceL, p ermettant de trouver le sommet non-encore parcours situé à plus courte distance. */
void dijkstra_list(grapheL* grph, int src) {
    int n = grph->vertices;
    int dist[n];
    int access[n];
    int i;
    for (i = 0; i < n; i++) {
        dist[i] = INF;
        access[i] = 0;
    }
    dist[src] = 0;
    for (i = 0; i < n - 1; i++) {
        int u = minDistanceL(grph, dist, access);
        access[u] = 1;
        noeudListeAdj *n = grph->array[u].head;
        while (n != NULL) {
            if (access[n->but] == 0 && dist[u] != INF && dist[u] + n->poids < dist[n->but])
                dist[n->but] = dist[u] + n->poids;
            n = n->suivant;
        }
    }
    print_dist(dist, n, src);
};

