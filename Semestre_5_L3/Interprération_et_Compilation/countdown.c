
#include <stdio.h>

void countdown (int n)
{
	if (n != 0) {
	printf("%d\n", n);
	countdown(n - 1);
	}
	else {
		printf("BOUM!\n");
	}
}


int main ()
{
	int n;
	printf("Count from? ");
	scanf("%d", &n);
	countdown(n);
	return 0;
}
