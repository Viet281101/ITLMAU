
#include <stdio.h>

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

	N = 7;
	res = fiboR(N);

	printf("fibonacci de %d = %d\n", N, res);

	return 0;
}
