
#include <iostream>

using namespace std;

template <typename T> 
void triGeneral(T * tab, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (tab[i] > tab[j]) {
                T temp = tab[i];
                tab[i] = tab[j];
                tab[j] = temp;
            }
        }
    }
}


int main() {
    int tab[] = {5, 2, 4, 6, 8, 0, 9};
    int n = sizeof(tab) / sizeof(tab[0]);
    triGeneral(tab, n);
    for (int i = 0; i < n; i++) {
        cout << tab[i] << " ";
    }
    cout << endl;
    
    return 0;

}


