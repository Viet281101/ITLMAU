

#include <stdio.h>
#include <stdlib.h>


int main(void)
{
    pileI_t p; // pile d'int
    fileI_t f; // file d'int

    initialiserPI(&p);
    initialiserFI(&f);

    emPilerI(&p,1);
    enFilerI(&f,2);
    emPilerI(&p,3);
    emPilerI(&p,4);
    enFilerI(&f,5);

    printf("%d\n",deFilerI(&f));
    printf("%d\n",dePilerI(&p));

    emPilerI(&p,6);
    emPilerI(&p,7);

    printf("%d\n",dePilerI(&p));
    enFilerI(&f,8);

    printf("%d\n",deFilerI(&f));
    printf("%d\n",dePilerI(&p));

    enFilerI(&f,dePilerI(&p));

    printf("%d\n",dePilerI(&p));
    printf("%d\n",deFilerI(&p));
    printf("%d\n",deFilerI(&f));

    detruirePI(&p);
    detruireFI(&f);

    return 0;
}

