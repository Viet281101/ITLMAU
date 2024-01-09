
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double random(void);
// double genererAlea(void);

double random_function(void) 
{
    return (double) rand() / RAND_MAX;
}

int genererAlea(const int a, const int b)
{
    return (int)(a + (b - a) * random_function());
}

int main(void)
{
    srand(time(NULL));
    printf("%d.\n", genererAlea(1, 10));
    printf("%d.\n", genererAlea(1, 10));
    printf("%d.\n", genererAlea(1, 10));
    printf("%d.\n", genererAlea(1, 10));
    return 0;
}


