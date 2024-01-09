
#include <stdio.h>

void foo (const char * a ){
    while(*a){
        printf("%c ", ((*a) - '0' + 'A'));
        ++a;
    }
    printf("\n");
}

int main(void) {
    foo("20006303");
    return 0;
}
