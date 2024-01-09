
#include <stdio.h>


int compte(int E[], int taille, int s){
	int n;

	if (taille < 1){
		if (s == 0)
			return 1;
		else
			return 0;
	}


	/*Sous probleme 1: */
	n = compte(E, taille - 1, s);
	if (n == 1)
		return 1;


	/*Sous probleme 2: */
	n = compte(E, taille -1, s -E[taille - 1]);
	if (n == 1)
		return 1;
	return 0;
}


int main(void){

	// Q1: 
	
	/* Q2: chaque appels execute deux sous-appels si n (la taille du tableau) est different de 0.
	Donc dans le pire des cas (aucune solution trouvee) il y aura 2^n appels avec un tableau de taille 0.
	Donc en comptant les appels internidiaire il y aura, 2^n + 2^(n-1) + 2^(n-2) + 2^1 + 2^0 appel 2^(n+1) - 1 appels en tout
	et donc la complexite en temp s'est l'ordre de O(2^(n+1) - 1) = O(2)

	de l'ordre de O(n) (taille de tableau) + O(n) (pile d'appels)= O(n) donc O(n).
	*/
	return 0;
}
