


#include <stdio.h>


#define MAX 7
#define INFINITY 9999


//// Fonction pour afficher les résultats
void affiche(int depart, int distance[]) {
    printf("Le nombre de noeuds a été fixé dans une variable globale MAX = %d\n", MAX);
    for (int i = 0; i < MAX; i++) 
    {
        if (i != depart) 
        {
            printf("Distance entre noeud %d et noeud %d = %d\n", depart, i, distance[i]);
            printf("Chemin à parcourir = %d", i);

            int prev = depart;
            while (prev != i) 
            {
                printf("<-%d", prev);
                prev = distance[prev];
            }
            printf("<-%d\n", depart);
        }
    }
}


//// Fonction pour trouver le noeud non visité avec la distance minimale
int trouverNoeudMin(int distance[], int visite[]) {
    int min = INFINITY;
    int min_index;

    for (int i = 0; i < MAX; i++) 
    {
        if (visite[i] == 0 && distance[i] < min) 
        {
            min = distance[i];
            min_index = i;
        }
    }

    return min_index;
}


//// Fonction principale pour l'algorithme de Dijkstra
int dijkstra(int G[MAX][MAX], int depart) {
    int visite[MAX] = {0};  // tableau pour indiquer les noeuds visités
    int distance[MAX];     // tableau pour stocker les distances minimales
    __attribute__((unused)) int predecessors[MAX];

    //// Initialisation des distances à l'infini sauf pour le noeud de départ
    for (int i = 0; i < MAX; i++) 
    {
        distance[i] = INFINITY;
        predecessors[i] = -1;
    }
    distance[depart] = 0;

    //// Boucle principale de l'algorithme de Dijkstra
    for (int count = 0; count < MAX - 1; count++) 
    {
        int u = trouverNoeudMin(distance, visite); // Trouver le noeud non visité avec la distance minimale
        visite[u] = 1;                            // Marquer le noeud comme visité

        //// Mettre à jour les distances des noeuds adjacents au noeud u
        for (int v = 0; v < MAX; v++) 
        {
            if (!visite[v] && G[u][v] && distance[u] != INFINITY && distance[u] + G[u][v] < distance[v]) 
            {
                distance[v] = distance[u] + G[u][v];
            }
        }
    }

    //// Appel de la fonction d'affichage
    affiche(depart, distance);

    return 0;
}


int main() {
    int G[MAX][MAX] = {{0, 2, INFINITY, INFINITY, INFINITY, INFINITY, INFINITY},
                        {2, 0, 12, INFINITY, INFINITY, INFINITY, INFINITY},
                        {INFINITY, 12, 0, 4, INFINITY, INFINITY, INFINITY},
                        {INFINITY, INFINITY, 4, 0, 14, INFINITY, INFINITY},
                        {INFINITY, INFINITY, INFINITY, 14, 0, 27, INFINITY},
                        {INFINITY, INFINITY, INFINITY, INFINITY, 27, 0, 7},
                        {INFINITY, INFINITY, INFINITY, INFINITY, INFINITY, 7, 0}};

    int depart;

    printf("Le nombre de noeuds a été fixé dans une variable globale MAX = %d\n", MAX);
    printf("Entrez le numéro du noeud de départ : ");
    scanf("%d", &depart);

    dijkstra(G, depart);


    // réseau de métro parisiens sur 7 gares principales
    int metroParisien[MAX][MAX] = {
        {0,   INFINITY, INFINITY, INFINITY, INFINITY, 12,  5},
        {INFINITY, 0,   2,   INFINITY, INFINITY, INFINITY, 7},
        {INFINITY, 2,   0,   13,  INFINITY, INFINITY, 10},
        {INFINITY, INFINITY, 13,  0,   INFINITY, INFINITY, INFINITY},
        {INFINITY, INFINITY, INFINITY, INFINITY, 0,   INFINITY, 2},
        {12,  INFINITY, INFINITY, INFINITY, INFINITY, 0,   12},
        {5,   7,   10,  INFINITY, 2,   12,  0}
    };
    
    // pareil, mais avec une ligne ne circulant pas dans un sens
    int metroParisienSans4[MAX][MAX] = {
        {0,   INFINITY, INFINITY, INFINITY, INFINITY, 12,  5},
        {INFINITY, 0,   2,   INFINITY, INFINITY, INFINITY, 7},
        {INFINITY, 2,   0,   13,  INFINITY, INFINITY, INFINITY},
        {INFINITY, INFINITY, 13,  0,   INFINITY, INFINITY, INFINITY},
        {INFINITY, INFINITY, INFINITY, INFINITY, 0,   INFINITY, 2},
        {12,  INFINITY, INFINITY, INFINITY, INFINITY, 0,   12},
        {5,   7,   10,  INFINITY, 2,   INFINITY, 0}
    };


    return 0;
}



