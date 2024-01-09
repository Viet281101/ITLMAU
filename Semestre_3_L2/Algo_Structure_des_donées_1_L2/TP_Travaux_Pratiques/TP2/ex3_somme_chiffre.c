
#include <stdio.h>

int sommeChiffres(int a) {
	//// Example avec boucle:
	/*int somme = 0, x;
	while (a > 0){
		x = a % 10;
		somme = somme + x;
		a = a / 10;
	} return somme;*/

	if (a!=0){
		return (a % 10 + sommeChiffres(a/10));
	}else{
		return 0;
	}
}


int main(void) {
	printf("%d", sommeChiffres(456));
	return 0;
}
