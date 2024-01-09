
#include<iostream>
#include<cstdio>
#include<string>

// ceci est un commentaire sur une ligne
/* ceci est un commentaire sur
plusieurs lignes*/

using namespace std;  // permet d'éviter d'écrire systématiquement std::cin ou std::cout (à éviter)

int main(void) {
    int d; // une variable entière d
    int i;
    string divse, pas_divise;

    cout<<"****Premier programme****"<<endl;
    std::cout<<"Saisissez un nombre puis appuyez sur entrée : ";
    std::cin >> d;

    i=1; // on met 0 dans i
    while(i<=15) {
        if( d % i == 0) {
            if (divse.size() > 0) {
                divse += ",";
            }
            divse += to_string(i);
            //cout << i << " divise " << d << endl;
        }
        else {
            if (pas_divise.size() > 0) {
                pas_divise += ",";
            }
            pas_divise += to_string(i);
            //printf("%d ne divise pas %d\n",i,d);
        }

        cout << divse << " divise " << d << ", " << pas_divise << " ne divise pas " << d << endl;
        i=i+1;
    }
}


