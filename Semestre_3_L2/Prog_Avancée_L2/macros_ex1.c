
#include <stdio.h>

#define MIN(a,b) ((a) < (b) ? (a) : (b))

int main(void){
    int i = 1, j = 2, k;
    float x = 3.1459f, y = 2.71828f, z = 1.41421f, l, m, n;
    k = MIN(i, j);
    l = MIN(j, k);

    return 0;
}
