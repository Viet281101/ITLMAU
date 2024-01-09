
#include <iostream>

using namespace std;

class tableau20_t {
private:
    int tab[20];

public:
    tableau20_t() {
        for (int i = 0; i < 20; i++) {
            tab[i] = 0;
        }
    }

    int& operator[](int i) {
        return tab[i];
    }

    int nbNul() const {
        int n = 0;
        for (int i = 0; i < 20; i++) {
            if (tab[i] == 0) {
                n++;
            }
        }
        return n;
    }

    void affiche() const {
        for (int i = 0; i < 20; i++) {
            cout << tab[i] << " ";
        }
        cout << "\n";
    }

    tableau20_t operator+(const tableau20_t& t) const {
        tableau20_t res;
        for (int i = 0; i < 20; i++) {
            res[i] = tab[i] + t.tab[i];
        }
        return res;
    }

    tableau20_t& operator=(const tableau20_t& t) {
        if (this != &t) {
            for (int i = 0; i < 20; i++) {
                tab[i] = t.tab[i];
            }
        }
        return *this;
    }
};


int main() {
    tableau20_t tab1;
    tab1[4] = 2;
    int var1 = tab1.nbNul();
    int var2 = tab1[4];
    tab1.affiche();
    tableau20_t tab2;
    tab2 = tab1;
    tab1 = tab2 + tab1;
    tab1.affiche();
    return 0;
}
