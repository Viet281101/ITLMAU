
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
    MaStruct* pStruct1 = malloc(sizeof(MaStruct));
    MaStruct* pStruct2 = malloc(sizeof(MaStruct));

	if (pStruct1 != NULL) {
    	pStruct1->i = 10;
    }
    if (pStruct2 != NULL) {
    	pStruct2->j = 5;
    }
    //printf("%i",pStruct1->i);
    //printf("%i",pStruct2->j);
    
    
    free(pStruct1);
    free(pStruct2);
    return 0;
}

int main()
{
    structbug();
}
