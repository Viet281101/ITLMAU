
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>


typedef struct {
    int source;
    int destination;
    int weight;
} Edge;

typedef struct {
    int vertices;
    int edges;
    Edge* edge;
} Graph;

Graph* createGraph(int vertices, int edges) {
    Graph* graph = (Graph*) malloc(sizeof(Graph));
    graph->vertices = vertices;
    graph->edges = edges;
    graph->edge = (Edge*) malloc(edges * sizeof(Edge));
    return graph;
}

void bellman_ford(Graph* graph, int source) {
    int V = graph->vertices;
    int E = graph->edges;
    int distance[V];

    for (int i = 0; i < V; i++)
        distance[i] = INT_MAX;
    distance[source] = 0;

    for (int i = 1; i <= V-1; i++) {
        for (int j = 0; j < E; j++) {
            int u = graph->edge[j].source;
            int v = graph->edge[j].destination;
            int weight = graph->edge[j].weight;
            if (distance[u] != INT_MAX && distance[u] + weight < distance[v])
                distance[v] = distance[u] + weight;
        }
    }

    for (int i = 0; i < E; i++) {
        int u = graph->edge[i].source;
        int v = graph->edge[i].destination;
        int weight = graph->edge[i].weight;
        if (distance[u] != INT_MAX && distance[u] + weight < distance[v]) {
            printf("Le graphique contient des cycles négatifs.\n");
            return;
        }
    }

    // Print
    printf("Distance du sommet source %d aux autres sommets : \n", source);
    for (int i = 0; i < V; i++)
        printf("%d à %d est %d\n", source, i, distance[i]);
}

int main() {
    int V = 5;
    int E = 8;
    Graph* graph = createGraph(V, E);

    // Exemple: 
    graph->edge[0].source = 0, graph->edge[0].destination = 1, graph->edge[0].weight = -1;
    graph->edge[1].source = 0, graph->edge[1].destination = 2, graph->edge[1].weight = 4;
    graph->edge[2].source = 1, graph->edge[2].destination = 2, graph->edge[2].weight = 3;
    graph->edge[3].source = 1, graph->edge[3].destination = 3, graph->edge[3].weight = 2;
    graph->edge[4].source = 1, graph->edge[4].destination = 4, graph->edge[4].weight = 2;

    clock_t t0, t1, dt;
    t0 = clock();

    bellman_ford(graph, 0);
    
    t1 = clock();
    dt = t1 - t0;
    printf("Temps d'exécution : %f secondes\n", (double) dt / CLOCKS_PER_SEC);

    return 0;
};
