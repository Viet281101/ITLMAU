
#include <stdio.h>

void trierTab(int taille,int* tab){
	///// tri croissant des tableaux
	// avec boucle for
	int a;
	for(int i = 0; i < taille - 1; i++){
		for(int j = i + 1; j < taille; j ++){
			if(tab[i] > tab[j]){
				a = tab[i];
				tab[i] = tab[j];
				tab[j] = a;
			}
		}
	}

	// avec recursive
	// int a;
	// int i = 0;
	// int j = i + 1;

	// if (i < taille - 1){
	// 	i++;
	// 	if (j < taille){
	// 		j++;
	// 		if (tab[i] < tab[j]){
	// 			a = tab[i];
	// 			tab[i] = tab[j];
	// 			tab[j] = a;
	// 		}
	// 	}
	// }
	// trierTab(taille, tab);


}


void afficherTableau(int taille, int *tab){
	// int i = 0;
	// if (i < taille){
	// 	printf("%d \n", tab[i]);
	// 	i++;
	// }
	// afficherTableau(taille, tab);

	for(int i = 0; i < taille ; i++){
		printf("%d \n", tab[i]);
	}
}


int main(void)
{
	int tab[5] = {8, 5, 7, 6, 2};
	trierTab(5, tab);
	afficherTableau(5, tab);
	return 0;
}

