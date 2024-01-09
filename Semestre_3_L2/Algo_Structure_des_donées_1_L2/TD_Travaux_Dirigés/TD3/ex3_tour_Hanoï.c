
#include <stdio.h>

void hanoi(int n, char aD, char aI, char aA) {
	if (n < 1)
		return;
	hanoi(n - 1, aD, aA, aI);
	printf("%c -> %c (deplacer du disque %d)\n", aD, aA, n);
	hanoi(n - 1, aI, aD, aA);
}

int main(void) {
	
	return 0;
}
