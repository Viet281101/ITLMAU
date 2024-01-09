
#include <stdio.h>

int puissance(int a, int n) {
	if (n == 0) {
		return(1);
	}
	else if (n == 1) {
		return(a);
	}
	else {
		int tmp = puissance(a, int(n / 2));
		if (n % 2 == 0) {			
			return(tmp * tmp);
		}
		else {
			return(a * tmp * tmp);
		}
	}
}

int main() {
	int a = 3; int n = 5;
	printf("a= %d\n",a);
	
	printf("n= %d\n",n);
	printf("\n");
	
	int res = puissance(a, n);
	printf("res= %d\n",res);
	
	getchar();
	return 0;
}