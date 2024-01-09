
#include <stdio.h>

int puissance(int b, int p){
    int res = 1;
    for( res = 1; p>0; p--) {
        res = res * b;
    } 
    return res; 
}

int main(){

    int x, n;
    printf("Calcul la puissance X^n \n");
    printf("Veuillez entrez une valeur X de puissance: ");
    scanf("%d", &x);
    printf("Veuillez entrez votre n entier: ");
    scanf("%d", &n);
    printf("la puissance de %d^%d = %d\n", x, n, puissance(x, n));
      
    getchar();
    getchar();
    return 0;
}

