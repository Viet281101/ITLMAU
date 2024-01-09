
#include <stdio.h>
#include <stdlib.h>
 
int main(void)
{
	int N;
    File *f;
    f = fopen("alea.nb", "rb");
 
    if(f==NULL){
        printf("Erreur lors de l'ouverture d'un fichier");
        exit(1);
    }
 
    printf("Veullez entrez un nbr N aleatoire entre de 1 a 100: \n");
    scanf("%d ", &N);

    fprintf(f, "N = %d\n", N);
 
    fclose(f);
 
    return 0;
}

