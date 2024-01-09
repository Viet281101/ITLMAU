
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct MaStruct
{
    int i;
    int j;
}MaStruct;

int structbug()
{	
    MaStruct* pStruct1 = malloc(sizeof(int));
    MaStruct* pStruct2 = NULL;

    pStruct1->i = 10;
    pStruct1->j = 10;
    pStruct2->j = 5;
    return 0;
}

int main()
{
    structbug();
    return 0;
}
