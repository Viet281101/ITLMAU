
#include <stdio.h>

int recherche(int n, int *tab, int val) {
	int mil;
	if (n == 0)
		return -1;

	mil = n/2;
	if (tab[mil] == val)
		return mil;
	if (tab[mil] < val) {
		n = recherche(n - mil -1, tab + mil + 1, val);
		if (n == -1)
			return -1;
		else
			return n + mil + 1;
	}
	if (tab[mil] > val) {
		n = recherche(mil, tab, val);
		if (n == -1)
			return -1;
		else
			return n;
	}
}


int main(void)
{
	long array[100], n, c;

	printf("Enter number of elements\n");
	scanf("%ld", &n);

	printf("Enter %ld integers\n", n);

	for (c = 0; c < n; c++)
		scanf("%ld", &array[c]);


	return 0;
}

