
#include <stdio.h>

int rechercherRecTab(int taille,int* tab,int val){
	if (taille > 0){
		if (val == tab[taille])
			if (taille >= 0){
				printf("Trouver le val %d en index %d\n", val, taille);
				return 0;
			}
			else
				return -1;
		rechercherRecTab(taille - 1, tab, val);
	}
}


int main(void)
{
	int tab[5] = {1, 2, 3, 4, 5};
	rechercherRecTab(5, tab, 4);
	return 0;
}

