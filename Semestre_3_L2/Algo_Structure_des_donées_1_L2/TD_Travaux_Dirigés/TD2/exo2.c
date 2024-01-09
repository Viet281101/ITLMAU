
#include <stdio.h>
#include <stdlib.h>

int main(void) {
	int a; //(a)
	int* p = &a; //(b)
	int b; //(c)

	*p = 1; //(d)
	p = &b; //(e)

	*p = a + 3; //(f) 
	// *p = *(&a + 3)
	printf("%d\n", *p); // *p = 4

	printf("a = %d\n", a);
	printf("b = %d\n", b);


	return EXIT_SUCCESS;
	
}

