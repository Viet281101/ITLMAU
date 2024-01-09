
#include <stdio.h>
#include <time.h>

int fiboR (int n){
	if (n < 2)
		return n;
	return fiboR(n - 1) + fiboR(n - 2);
}

int fiboB (int n){
	int vi, vip, vim;
	int i;
	if (n < 2)
		return n;
	for (vim = 0, vi = 1, i = 1; i < n; ++i)
	{
		vip = vi + vim;
		vim = vi;
		vi = vip;
	}
	return vip;
}

int main(void)
{
	int N;
	int res;

	N = 10;
	res = fiboR(N);

	// printf("fibonacci de %d = %d\n", N, res);

	clock_t TfiboR;
	clock_t TfiboB;
    
	// calcul temps d'execution de la fonc fiboR()
	TfiboR = clock();
	fiboR(N);
    TfiboR = clock() - TfiboR;
    double tempFiboR = ((double)TfiboR)/CLOCKS_PER_SEC;

	// calcul temps d'execution de la fonc fiboB()
	TfiboB = clock();
	fiboB(N);
    TfiboB = clock() - TfiboB;
    double tempFiboB = ((double)TfiboB)/CLOCKS_PER_SEC;

	printf("Le temps d'execution de la fonc fiboR() est: %f\n", tempFiboR);

	printf("Le temps d'execution de la fonc fiboB() est: %f\n", tempFiboB);

	return 0;
}
