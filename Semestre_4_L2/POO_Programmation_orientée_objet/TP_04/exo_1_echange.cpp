
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

//// question 2: 
/*
Cette fonction utilise les références pour échanger les valeurs de deux variables. 
Ainsi, l'appel echange(a,b) échangera les valeurs de a et b, 
tandis que l'appel echange(3,2) provoquera une erreur de compilation 
car les littéraux 3 et 2 ne peuvent pas être passés en tant que références.
*/

