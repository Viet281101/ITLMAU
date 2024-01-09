
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void remplirRecTab(int taille,int* tabl) {
	int min = -100, max = 100;
	srand(time(0));
	if (taille < 0) return;
	int num = (rand() % (max - min + 1)) + min;
	printf("%d ", num);
	remplirRecTab(taille - 1, tabl);
}

int main(void) {
	int *tab[10] = {};
	remplirRecTab(10, *tab);
	return 0;
}
