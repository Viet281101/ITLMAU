
#include <stdio.h>

void a(char **ptr){
    char *ptr1;
    ptr1 = (ptr += sizeof(int))[-2];
    printf("%s\n", ptr1);
}

int main(void){
    char *t[] = {'a', 'b', 'c', 'd', 'e', 'f'};
    a(t);

    return 0;
}
