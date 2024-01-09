
#include <iostream>

//// question 1: 
void echange(int a, int b){
    int temp = a;
    a = b;
    b = temp;
}


int main(){ 
    int a=3;
    int b=2;
    echange(a,b); // et pas echange(&a,&b);
    // ici a==2 et b==3.
}



//// question 2: on ne peut pas à donner un sens : echange(3, 2)

