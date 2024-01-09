#include <stdio.h>

#define MAX 7
#define INFINITY 9999

void affiche(int depart, int distance[]) {
    printf("Distance entre noeud %d et noeud %d = %d\n", depart, 0, distance[0]);
    printf("Chemin à parcourir = ");
    int i = 0;
    while (i != depart) {
        printf("%d<-", i);
        i = distance[i];
    }
    printf("%d\n", depart);
}

void dijkstra(int G[MAX][MAX], int depart) {
    int distance[MAX];
    int visite[MAX];

    for (int i = 0; i < MAX; i++) {
        distance[i] = INFINITY;
        visite[i] = 0;
    }

    distance[depart] = 0;

    for (int count = 0; count < MAX - 1; count++) {
        int u = -1;

        for (int i = 0; i < MAX; i++) {
            if (!visite[i] && (u == -1 || distance[i] < distance[u])) {
                u = i;
            }
        }

        visite[u] = 1;

        for (int v = 0; v < MAX; v++) {
            if (!visite[v] && G[u][v] && distance[u] != INFINITY && distance[u] + G[u][v] < distance[v]) {
                distance[v] = distance[u] + G[u][v];
            }
        }
    }

    // Appel de la fonction d'affichage
    affiche(depart, distance);
}

int main() {
    // Déclaration du graphe sous forme de matrice d'adjacence
    int matrice[MAX][MAX] = {{0, 12, INFINITY, INFINITY, INFINITY, 7, INFINITY},
                             {12, 0, 14, INFINITY, INFINITY, INFINITY, INFINITY},
                             {INFINITY, 14, 0, 27, INFINITY, INFINITY, INFINITY},
                             {INFINITY, INFINITY, 27, 0, INFINITY, INFINITY, INFINITY},
                             {INFINITY, INFINITY, INFINITY, INFINITY, 0, INFINITY, INFINITY},
                             {7, INFINITY, INFINITY, INFINITY, INFINITY, 0, 5},
                             {INFINITY, INFINITY, INFINITY, INFINITY, INFINITY, 5, 0}};

    // Nombre de noeuds
    printf("Le nombre de noeuds a été fixé dans une variable globale MAX = %d\n", MAX);

    // Saisie du numéro du noeud de départ
    int depart;
    printf("Entrez le numéro du noeud de départ : ");
    scanf("%d", &depart);

    // Appel de la fonction de Dijkstra
    dijkstra(matrice, depart);

    return 0;
}