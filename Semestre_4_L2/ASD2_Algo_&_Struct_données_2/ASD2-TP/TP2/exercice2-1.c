
#include <stdio.h>

int main(void) {
	// Déclaration des variables a et b
	int a, b;
	// Déclaration éventuelle d’autres variables
	// À REMPLIR SI BESOIN
	int temp;
	
	// Demande à l’utilisateur de saisir les entiers a et b
	// À REMPLIR
	printf("Veuillez entrez a:");
	scanf("%d\n", &a);
	printf("Veuillez entrez b:");
	scanf("%d\n", &b);
	
	// Tri des variables pour que le printf qui suit soit correct
	// À REMPLIR
	if (a > b){
		temp = a;
		a = b;
		b = temp;
	}
	
	// Affichage des valeurs dans l’ordre croissant
	printf("Valeurs saisies dans l'ordre croissant: %i, %i \n_", a, b);
	// Retour
	return 0;
}




