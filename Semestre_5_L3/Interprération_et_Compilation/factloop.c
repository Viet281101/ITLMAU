
#include <stdio.h>

int factloop (int n) {
    int r = 1;
    while (n > 1) {
        r = r * n;
        n = n - 1;
    }
    return r;
}


int main (int argc, char *argv[]) {
    int n;
    printf("Entrez un entier : ");
    scanf("%d", &n);
    printf("La factorielle de %d est %d\n", n, factloop(n));
    return 0;
}


