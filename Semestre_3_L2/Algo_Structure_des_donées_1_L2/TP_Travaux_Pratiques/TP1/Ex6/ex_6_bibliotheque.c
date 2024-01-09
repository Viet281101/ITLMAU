
#include <stdio.h>
#include <stdlib.h>
#include "maBiBli.h"


int main(void)
{
	int tab[0];
	File *f;
    f = fopen("maBiBli.a", "a");
 
    if(f==NULL){
        printf("Erreur lors de l'ouverture d'un fichier");
        exit(1);
    }

    fprintf(f, "Somme de tableau %d\n", somme(7, tab[10]));
    fprintf(f, "Produit de tableau %d\n", produit(7, tab[10]));

    fclose(f);
	return 0;
}
