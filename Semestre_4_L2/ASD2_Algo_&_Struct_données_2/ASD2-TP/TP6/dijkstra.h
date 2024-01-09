
#pragma once

#ifndef DIJKSTRA_H
#define DIJKSTRA_H



#include <stdio.h>


#define MAX 9
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




#endif

