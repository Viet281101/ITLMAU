
#include <time.h>
#include <stdio.h>

int fiboR (int n){
	if (n < 2)
		return n;
	return fiboR(n - 1) + fiboR(n - 2);
}

int main(void){
    int n = 100;
    clock_t t;
    t = clock();

    for(int i = 0; i < n; i++){
        fiboR(20);
    }
    
    t = clock() - t;
    double temp_passe = ((double)t)/CLOCKS_PER_SEC;
    
    printf("%d operations; temps_passe : %f ms; op/ms: %f \n", n, temp_passe, temp_passe/n);

    return 0;
}

