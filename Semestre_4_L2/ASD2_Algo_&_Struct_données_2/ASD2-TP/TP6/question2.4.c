


//// 1. Les réponses attendues pour les affichages sont :
/*
sizeof(tab) renvoie la taille totale du tableau en octets, soit 16 (car il y a 4 entiers de 4 octets chacun).

sizeof(&tab) renvoie la taille de l'adresse du tableau, soit 8 octets sur une architecture 64 bits (car il s'agit d'un pointeur vers un tableau).

sizeof(tab[0]) renvoie la taille d'un élément du tableau, soit 4 octets (car il s'agit d'un entier).

sizeof(p) renvoie la taille du pointeur, soit 8 octets sur une architecture 64 bits.

sizeof(*p) renvoie la taille de l'objet sur lequel pointe le pointeur (c'est-à-dire un entier), soit 4 octets.

L'affichage de p[i] permet de vérifier que les valeurs ont bien été initialisées et stockées dans le tableau p.
*/


//// 2. le code pour ne faire afficher que les 4 premiers nombres impairs:
#include <stdio.h>
#include <stdlib.h>

int main(){
    int* p=NULL;
    int tab[4];
    printf("%ld, %ld, %ld\n",sizeof(tab), sizeof(&tab), sizeof(tab[0]));
    p = malloc(5*sizeof(int));
    printf("%ld, %ld\n",sizeof(p), sizeof(*p) * 5);
    p = malloc(4*sizeof(int));
    printf("%ld, %ld\n",sizeof(p), sizeof(*p));
    for (int i=0; i<5; i++){
        if (i%2 == 1) { // i est impair
            p[i]=i;
        } else {
            p[i] = 0;
        }
    }
    for (int i=0; i<4; i++){ // ne fait afficher que les 4 premiers nombres impairs
        printf("%d",p[2*i+1]);
    }
    free(p);
    return 0;
}

