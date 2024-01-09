
#include <stdio.h>
#include <stdlib.h>

// ex2 : tableau ou pointeur ?
void afficher_tableau(int *T, int taille)
{
    int i;
    for(i=0; i<taille; i++)
    {
        printf("%d  ", T[i]);
    }
    printf("\n");
}


int main(void)
{
	int a[10] = {9, 2, 6, 7};
	afficher_tableau(a, 10);

	return 0;
}

