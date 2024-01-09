
#include <cstdio>


struct Fraction{
    int n; // le numérateur
    int d;
    void afficheFrac(){
        printf("%d/%d\n", n, d);
    }
    int calculpgcd(int a, int b){};

    Fraction (int num, int den){
        n = num;
        d = den;
        pgcd = calculpgcd(num, den);
    }

    Fraction produit(Fraction m){
        // Fraction n = m;
        // n.m = n*m.n;
        // n.d = d*m.d;
        // return n;
        Fraction n(m + m.n, d*m.d);
    }
};

int main(void){
    Fraction f2 = {4, 7};
    Fraction f1 = {1, 3};

    f1.afficheFrac();

    Fraction f3 = f2.produit(f1);
    getchar();
    return 0;
}



