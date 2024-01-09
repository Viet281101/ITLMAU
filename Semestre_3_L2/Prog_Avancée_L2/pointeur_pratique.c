
#include <stdio.h>


int main(void)
{
	// int age = 18;
	// int *p;
	// p = &age;
	// // int *p = &age;
	// printf("age = %d\n", age);
	// printf("p = %p\n", p);
	// printf("&age = %p\n", &age);
	// printf("*p = %d\n", *p);
	// printf("sizeof(p) = %d\n", sizeof(p));
	// *p = 19;
	// printf("*p = %d\n", *p);
	// printf("age = %d\n", age);


	// int i = 1, j = 2, k = 3;
	// printf("adress i = %p\n", &i);
	// printf("adress j = %p\n", &j);
	// printf("adress k = %p\n", &k);
	// // Que remarquez-vous concernant leur addresse ?
	// int l;
	// int *p = &i;
	// // Je prend un risque
	// for (l = 0; l < 3; l++) {
	// 	printf("%d\n", p[1]);
	// }


	// int t[] = {4, 5, 6};
	// int *p = t;
	// int i;
	// for (i = 0; i < 3; i ++) {
	// 	printf("%d\n", p[i]);
	// }


	int arr[3] = {20, 30, 40};
	int *p = arr;
	int q;

	// value of p (20) increment ted by 1 and returned
	q = ++(*p);
	printf("arr[0] = %d, arr[1] = %d, *p = %d, q = %d\n", arr[0], arr[1], *p, q);

	// value of p (20) is returned pointer incremented by 1
	q = (*p)++;
	printf("arr[0] = %d, arr[1] = %d, *p = %d, q = %d\n", arr[0], arr[1], *p, q);

	// pointer incremented by 1 value returned
	q = *(++p);
	printf("arr[0] = %d, arr[1] = %d, *p = %d, q = %d\n", arr[0], arr[1], *p, q);



	return 0;
}
