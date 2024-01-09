
#include <stdio.h>
#include <math.h>

int crible_erastothene(int N) {
	if (N < 2){
		return 0;
	}

	int sqareroot = (int) sqrt(N);
	for (int i = 2; i < sqareroot; i++) {
		if (N % i == 0) {
			return 0;
		}
	}
	return 1;
}

int main()
{
	int i, N;
	printf("Veuillez entrez N = ");
	scanf("%d", &N);
	printf("La liste de Crible d'Eratosthene de 2 -> N est :\n");
	if (N >= 2) {
		printf("%d ", 2);
	}
	for (i = 3; i <= N; i += 2){
		if (crible_erastothene(i) == 1){
			printf("%d ", i);
		}
	}
	getchar();
    getchar();
	return 0;
}
