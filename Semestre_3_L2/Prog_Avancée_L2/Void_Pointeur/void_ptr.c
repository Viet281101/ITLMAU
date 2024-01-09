
#include <stdio.h>

int main(void){
    int i ;
    float f;
    char ch;
    int *iptr;
    float *fptr;
    char *cptr;
    iptr = &i;
    i = 10;
    printf("\n %d %d ", i, *iptr);
    fptr = &f;
    f = 12.8;
    printf("\n %d %d ", f, *fptr);
    cptr = &ch;
    
}

