
#include <stdio.h>

int compteAf(int E[], int taille, int s){
	int n;

	if (taille < 1){
		if (s == 0)
			return 1;
		else
			return 0;
	}


	/*Sous probleme 1: */
	n = compteAf(E, taille - 1, s);
	if (n == 1)
		return 1;


	/*Sous probleme 2: */
	// n = compteAf(E, taille -1, s -E[taille - 1]);
	// if (n == 1)
	// 	return 1;
	// return 0;
}


int main(void){
	int tab[2] = {0, 1};
	printf("%d\n", compteAf(tab, 2, 0));
	return 0;
}
