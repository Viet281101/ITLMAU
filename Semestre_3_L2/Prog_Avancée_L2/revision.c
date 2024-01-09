
#include <stdio.h>

void doubler (int x){
	x *= 2;
}

int main(void)
{
	// int var1 = 5, var2 = 5;
	// printf("%d\n", var1++);
	// printf("var1 = %d\n", var1);


	int a[] = {5, 16, 7, 89, 45, 32, 10};
	// int *p = &a[0];
	// printf("%d\n", *p);
	// printf("%d\n", *(p++));
	// printf("%d\n", *(++p));
	// printf("%d\n", *p);

	// int *p = &a[2];
	// printf("%d\n", *(--p));
	// printf("%d\n", *(p--));
	// printf("%d\n", *p);

	// int *p = &a[1];
	// int *q = &a[5];

	// printf("%d\n", *(p+3));
	// printf("%d\n", *(q-3));
	// printf("%d\n", q-p);
	// printf("%d\n", q<p);
	// printf("%d\n", q>p);

	int y;
	y = 1;
	printf("%d\n", y);
	doubler(y);
	printf("%d\n", y);

	return 0;
}
