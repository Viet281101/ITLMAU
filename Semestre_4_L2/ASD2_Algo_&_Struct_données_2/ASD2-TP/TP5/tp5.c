
#include <stdio.h>

#define MAX 7
#define INFINITY 9999

void affichage(int depart, int distances[], int predecessors[]) 
{    
    printf("\nLe nombre de noeuds a été fixé dans une variable globale MAX = %d\n", MAX);
    printf("Entrez le numéro du noeud de départ : %d\n", depart);

    for (int i = 0; i < MAX; i++) 
    {
        if (i != depart) 
        {
            printf("\nDistance entre noeud %d et noeud %d = %d\n", depart, i, distances[i]);
            printf("Chemin à parcourir = %d", i);
            int prev_node = predecessors[i];
            while (prev_node != -1) 
            {
                printf("<-%d", prev_node);
                prev_node = predecessors[prev_node];
            }
            printf("<-%d\n", depart);
        }
    }
}


void dijkstra(int G[MAX][MAX], int depart) 
{
    int visited[MAX] = {0};
    int distances[MAX];
    int predecessors[MAX];
    
    for (int i = 0; i < MAX; i++) 
    {
        distances[i] = INFINITY;
        predecessors[i] = -1;
    }
    
    distances[depart] = 0;
    
    for (int count = 0; count < MAX - 1; count++) 
    {
        int min_distance = INFINITY;
        int min_node;

        for (int i = 0; i < MAX; i++) 
        {
            if (!visited[i] && distances[i] <= min_distance) 
            {
                min_distance = distances[i];
                min_node = i;
            }
        }
        
        visited[min_node] = 1;
        
        for (int i = 0; i < MAX; i++) 
        {
            if (!visited[i] && G[min_node][i] && distances[min_node] != INFINITY &&
                distances[min_node] + G[min_node][i] < distances[i]) 
            {
                distances[i] = distances[min_node] + G[min_node][i];
                predecessors[i] = min_node;
            }
        }
    }
    affichage(depart, distances, predecessors);
}



int main()
{

    int matrice[MAX][MAX] = {
        {0, 12, INFINITY, INFINITY, INFINITY, 7, INFINITY},
        {12, 0, 14, INFINITY, INFINITY, INFINITY, INFINITY},
        {INFINITY, 14, 0, 27, INFINITY, INFINITY, INFINITY},
        {INFINITY, INFINITY, 27, 0, INFINITY, INFINITY, INFINITY},
        {INFINITY, INFINITY, INFINITY, INFINITY, 0, INFINITY, INFINITY},
        {7, INFINITY, INFINITY, INFINITY, INFINITY, 0, 5},
        {INFINITY, INFINITY, INFINITY, INFINITY, INFINITY, 5, 0}
    };

    int depart;
    printf("Entrez le numéro du noeud de départ : ");
    scanf("%d", &depart);
    dijkstra(matrice, depart);


    printf("\n\n\n Métro parisiens sur 7 gares principales : ");
    int metroParisien[MAX][MAX] = {
        {0,   INFINITY, INFINITY, INFINITY, INFINITY, 12,  5},
        {INFINITY, 0,   2,   INFINITY, INFINITY, INFINITY, 7},
        {INFINITY, 2,   0,   13,  INFINITY, INFINITY, 10},
        {INFINITY, INFINITY, 13,  0,   INFINITY, INFINITY, INFINITY},
        {INFINITY, INFINITY, INFINITY, INFINITY, 0,   INFINITY, 2},
        {12,  INFINITY, INFINITY, INFINITY, INFINITY, 0,   12},
        {5,   7,   10,  INFINITY, 2,   12,  0}
    };
    dijkstra(metroParisien, 0);


    printf("\n\n\n Métro parisiens mais ligne 4 ne circule pas dans le sens Porte Clignancourt vers Bagneux : ");
    int metroParisienSans4[MAX][MAX] = {
        {0,   INFINITY, INFINITY, INFINITY, INFINITY, 12,  5},
        {INFINITY, 0,   2,   INFINITY, INFINITY, INFINITY, 7},
        {INFINITY, 2,   0,   13,  INFINITY, INFINITY, INFINITY},
        {INFINITY, INFINITY, 13,  0,   INFINITY, INFINITY, INFINITY},
        {INFINITY, INFINITY, INFINITY, INFINITY, 0,   INFINITY, 2},
        {12,  INFINITY, INFINITY, INFINITY, INFINITY, 0,   12},
        {5,   7,   10,  INFINITY, 2,   INFINITY, 0}
    };
    dijkstra(metroParisienSans4, 0);
    

    return 0;
}



