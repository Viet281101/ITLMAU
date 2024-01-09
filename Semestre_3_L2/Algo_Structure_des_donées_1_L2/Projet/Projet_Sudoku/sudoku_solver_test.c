


#include <stdio.h>
#include <malloc.h>
#include <memory.h>
 
#define BLOCK 3
 
int solve(int* a, int** row, int** col, int** oval, int block, int current)
{
    int i;
    int rank, total;
   
    rank = block * block;
    total = rank * rank;
    if(current == total)
        return 1;
    if(a[current])
        return solve(a, row, col, oval, block, current + 1);
    for(i = 0; i < rank; i++)
    {
        if(!(row[i][current/rank] || col[i][current%rank] || oval[i][(current/rank/block)*block + (current%rank)/block]))
        {
            a[current] = i + 1;
            row[i][current/rank] = 1;
            col[i][current%rank] = 1;
            oval[i][(current/rank/block)*block + (current%rank)/block] = 1;
            if(!solve(a, row, col, oval, block, current + 1))
            {
                a[current] = 0;
                row[i][current/rank] = 0;
                col[i][current%rank] = 0;
                oval[i][(current/rank/block)*block + (current%rank)/block] = 0;
            }
        }
    }
    if(!a[current])
        return 0;
    return 1;
}

int sodoku_solve(int* a, int block)
{
    int i, j;
    int rank;
    int **row, **col, **oval;
   
    rank = block * block;
    row = (int **)malloc(rank * sizeof(int *));
    col = (int **)malloc(rank * sizeof(int *));
    oval = (int **)malloc(rank * sizeof(int *));
 
    for(i = 0; i < rank; i++)
    {
        row[i] = (int *)calloc(rank, sizeof(int));
        col[i] = (int *)calloc(rank, sizeof(int));
        oval[i] = (int *)calloc(rank, sizeof(int));        
    }
   
    for(j = 0; j < rank * rank; j++)
    {
        if(a[j])
        {
            if((row[a[j] - 1][j/rank] || col[a[j] - 1][j%rank] || oval[a[j] - 1][(j/rank/block)*block + (j%rank)/block]))
            {
                printf("wrong input\n");
                return 0;
            }
            row[a[j] - 1][j/rank] = 1;
            col[a[j] - 1][j%rank] = 1;
            oval[a[j] - 1][(j/rank/block)*block + (j%rank)/block] = 1;
        }
    }
    if(solve(a, row, col, oval, block, 0))
    {
        for(i = 0; i < rank * rank; i++)
        {
            printf("%4d%s", a[i], (i % rank + 1)% block ? "" : "\t");
            (i + 1) % rank ? 0 : ((i / rank) + 1) % block ? printf("\n\n") : printf("\n\n\n\n");
        }
    }
    for(i = 0; i < rank; i++)
    {
        free(row[i]);
        free(col[i]);
        free(oval[i]);
    }
    free(row);
    free(col);
    free(oval);
 
    return 0;
}
int main()
{
    int block = BLOCK;
    int a[] = {
        0, 1, 0,    4, 5, 6,    0, 0, 9,
        0, 0, 0,    0, 0, 0,    0, 0, 8,
        0, 0, 0,    0, 0, 0,    0, 0, 0,
       
        0, 0, 0,    0, 0, 8,    0, 0, 0,
        0, 0, 0,    0, 0, 0,    0, 0, 0,
        0, 0, 0,    0, 0, 0,    0, 0, 0,
       
        0, 0, 0,    0, 0, 0,    0, 0, 0,
        0, 0, 0,    0, 0, 0,    0, 0, 0,
        7, 8, 9,    0, 0, 0,    0, 0, 0
    };
    printf("sodoku 9x9 solve:\n\n");  
    sodoku_solve(a, block);
    return 0;
}

