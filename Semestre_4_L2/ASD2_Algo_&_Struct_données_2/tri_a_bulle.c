
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// DÉFINIR UNE TAILLE DE VOTRE CHOIX
// #define TAB_SIZE ??

/* UTILS */ 
int permute(int* a, int* b){
    int tmp = *b;
    *b = *a;
    *a = tmp;
    return 0;
}

void affiche_tableau(int T[], int n){
    /* cette fonction doit afficher un tableau */
	// À COMPLÉTER
    printf("\n~~~ fin du tableau ~~~\n");
}

/* Fonctions de tri à bulle */

int tri_a_bulle(int T[], int n)
{
    int temp;
    for (int i=n ; i > 0 ; i--){
        for(int j = 0 ; j < i-1 ; j++) {
            if(T[j] > T[j+1]){
                permute(&T[j],&T[j+1]);
            }
        }
    }
    return 0;
}

int tri_a_bulle_optimise(int T[], int n)
{
    int temp;
    for (int i=n ; i > 0 ; i--){
	    int trie=1;
        for(int j = 0 ; j < i-1 ; j++) {
            if(T[j] > T[j+1]){
                permute(&T[j],&T[j+1]);
                trie = 0;
            }
        }
        if (trie == 1){
        	printf("trié avec i=%d\n",i);
			return 0;
		}
    }
    return 0;
}



int main()
{

	// DÉCLARATION TABLEAU(X) DE LA TAILLE TAB_SIZE
    
    /* Tri à bulle */
    
    double time_spent=0; 
    // À COMPLETER
    
    printf("Temps d'exécution tri bulle : %f\n\n", time_spent);
    
     /* Tri à bulle otpimisé */
    // À COMPLETER
    
    printf("Temps d'exécution tri bulle optimisé : %f\n\n", time_spent);
    
    return 0;
    
    
}

