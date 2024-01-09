
#include <iostream>

using namespace std;

template <typename T> 
T somme(int n, T *tab)
{
    int i;
    T acc = tab[0];
    for (i = 1; i < n; i++){
        acc = acc + tab[i];
    }
    return acc;
}

int main(){
    int tableau[] = {1, 2, 74, 67, 89};
    int n = sizeof(tableau) / sizeof(tableau[0]);
    int total = somme(5, tableau); // somme <double> (5, tableau);
    cout << "La somme est : " << total << endl;    
    
    return 0;
}

