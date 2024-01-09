

#include <iostream>

using namespace std;


class acces_t {
public:
    acces_t(int n) : valeur{n}, nbAcces{0}, nbAccesDepuisModif{0} {}
    
    int get() const {
        nbAcces++;
        nbAccesDepuisModif++;
        return valeur;
    }
    
    void set(int n) {
        valeur = n;
        nbAccesDepuisModif = 0;
    }
    
    int nbGet() const {
        return nbAccesDepuisModif;
    }
    
    int nGet() const {
        return nbAcces;
    }

private:
    int valeur;
    mutable int nbAcces;
    mutable int nbAccesDepuisModif;
};


int main() {
    acces_t n{4};
    cout << n.nbGet() << endl;// renvoie 0
    cout << n.get() << endl;// renvoie 4
    cout << n.nbGet() << endl;// renvoie 1
    cout << n.nbGet() << endl;// renvoie 1
    cout << n.get() << endl;// renvoie 4
    cout << n.nbGet() << endl;// renvoie 2
    n.set(2);
    cout << n.nbGet() << endl;// renvoie 0
    cout << n.get() << endl;// renvoie 2
    cout << n.nbGet() << endl;// renvoie 1

    acces_t const c{5};
    cout << c.nGet() << endl; // renvoie 0
    cout << c.get() << endl; // renvoie 5
    cout << c.nGet() << endl; // renvoie 1
    cout << c.nGet() << endl; // renvoie 1
    cout << c.get() << endl; // renvoie 5
    cout << c.get() << endl; // renvoie 5
    cout << c.nGet() << endl; // renvoie 3
    //c.set(4); erreur de compilation c est constant
}



