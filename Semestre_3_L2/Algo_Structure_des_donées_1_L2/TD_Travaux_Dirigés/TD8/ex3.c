
#include <stdio.h>
#include <stdlib.h>

int calcul_postfixe(char * tab){
    pileI_t p;
    initialiser(&p);
    int a, b;
    while (*tab != 0)
    {
        if (*tab >= '0' && *tab <= '9')
        {
            empilerI(&p, *tab - '0');
        }else if (*tab == '*' || *tab == '+'){
            if (estVide(&p)) error("syntax error");
            a = dePiler(&p);
            if (estVide(&p)) error("syntax error");
            b = dePiler(&p);
            if (*tab == '*') empiler(&p, a*b);
            if (*tab == '+') empiler(&p, a+b);
        }else error("syntax error");
        
        tab++;
    }
    
}


int main(void)
{

    return 0;
}

