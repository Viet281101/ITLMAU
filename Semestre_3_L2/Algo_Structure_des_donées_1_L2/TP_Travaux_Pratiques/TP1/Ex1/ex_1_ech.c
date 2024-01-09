#include <stdio.h>


void Echange(int *a, int *b) {
	int c=*a;
	*a = *b;
	*b = c;
} 


int main(void) {
	int x, y;

	printf("Entrez deux entiers: ");
	scanf("%d%d", &x, &y);
	printf("\nAvant Echange:\n\tx = %d\n\ty = %d\n", x, y);
	Echange(&x, &y);
	printf("\nApres Echange:\n\tx = %d\n\ty = %d\n", x, y);

	return 0;
}
