
#include <stdio.h>

int sommeD(int taille,int* T){
	if (taille < 1)
		return 0;
	return (*T) + sommeD(taille - 1, T + 1);
}

int sommeF(int taille,int* T){
	// int somme = 0;
	// for(int i=0; i<taille; i++)
	// {
	// 	somme += T[i];
	// }
	// return somme;

	if (taille < 1)
		return 0;
	return T[taille - 1] + sommeF(taille - 1, T);
}


int main(void)
{
	int tab[7];
	int taille = 10;
	printf("somme droite de tableau : %d\n", sommeD(taille, tab));
	printf("somme gauche de tableau : %d\n", sommeF(taille, tab));
	return 0;
}

