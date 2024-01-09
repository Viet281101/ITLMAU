
#include <stdio.h>

void rebour(int n)
{
	if(n<0) return;
	printf("%d\n",n);
	rebour(n-1);
}

int main(void)
{
	rebour(10);
	return 0;
}

