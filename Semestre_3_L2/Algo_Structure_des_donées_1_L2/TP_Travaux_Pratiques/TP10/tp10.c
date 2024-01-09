
#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int s; // sommet
    int e; // etiquette
} couple_t ;

# define MAX_SOMMET 40 // Le nombre maximum de sommets d'un graphe

typedef struct gra{
    couple_t liste[MAX_SOMMET][MAX_SOMMET];
    int n; // nombre de sommets
} grapheE_t; // graphe étiqueté


void creerGraphe(grapheE_t* g, FILE* grDesc){
    grapheE_t * a = (grapheE_t *)malloc(sizeof * a);

}; 


void dijikstra(grapheE_t* g,int depart,couple_t* t){};


void afficheChemin(int s,couple_t* t){};


int main(void){

    return 0;
}

