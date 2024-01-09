
#include <stdio.h>
#include <stdlib.h>

int somme(int n, int* T) {
	int sum = 0;
	if (n == 0)
	{
		return 0;
	}else
	{
		for(int i=0; i<n; i++)
		{
			sum += T[i];
		}
		return sum;
	}
}

int produit(int n, int* T) {
	int produit = 0;
	if (n == 0)
	{
		return 1;
	}else
	{
		for(int i=0; i<n; i++)
		{
			produit *= T[i];
		}
		return produit;
	}
}
