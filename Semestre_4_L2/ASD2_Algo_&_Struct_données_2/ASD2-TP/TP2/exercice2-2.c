
#include <stdio.h>

/* aucune autre variable ne doit être déclarée */

int main(void) {
	// Déclaration des variables a et b
	int a, b;


	// Demande à l’utilisateur de saisir les entiers a et b
	printf("Veuillez entrez a:");
	scanf("%d\n", &a);
	printf("Veuillez entrez b:");
	scanf("%d\n", &b);


	// Tri des variables pour que le printf qui suit soit correct
	if (a > b) {
		a = a + b;
		b = a - b;
		a = a - b;
	}

	///// ou :
	// if (b < a){
	// 	a = a-b;
	// 	b = b+a;
	// 	a = b-a;
	// }

	// Affichage des valeurs dans l’ordre croissant
	printf("Valeurs saisies dans l'ordre croissant: %i, %i \n", a, b);


	// Retour
	return 0;
}


