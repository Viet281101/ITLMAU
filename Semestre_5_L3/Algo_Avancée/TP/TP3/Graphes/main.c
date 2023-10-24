#include <stdio.h>
#include <stdlib.h>
#include<time.h>

#include "fifo.h"
#include "heap.h"
#include "affichage.h"
#include "matriceadj.h"
#include "listeadj.h"



int main(){
    //// Tests matrices d'adjacence
    grapheM *grph=remplir_grapheM(15);
    print_graphe(grph);
    printf("\n \n");
    int s=0;
    printf("Affichage des accessibles depuis %d : \n ",s);
    accessibles_mat(grph,0);
    printf("\n \n");
    printf("Affichage du résultat avec Dijkstra : \n");
    dijkstra_mat(grph,0);
    free_graph(grph);

    ////Tests listes d'adjacence
    grapheL *grphb = remplir_grapheL(10);
    print_adjlist(grphb);
    printf("\n \n");
    printf("Affichage du résultat avec Dijkstra : \n");
    dijkstra_list(grphb,0);
    printf("\n \n");
    printf("Affichage du résultat avec Dijkstra prio: \n");
    dijkstra_list_prio(grphb,0);
    free(grphb);
    return 0;
}