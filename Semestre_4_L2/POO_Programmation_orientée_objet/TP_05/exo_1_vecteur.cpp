

#include <iostream>
#include <cassert>

#include "vecteur.hpp" // inclure le fichier d'en-tête de la classe vector_t

using namespace std;

int main() {
    vector_t v(5); // tableau de 5 cases allouées (par exemple toutes à 0)
    vector_t r(500000); // tableau de 5000000 cases allouées

    v[3] = 2; // met la valeur 2 dans la case d'indice 3
    int a = v[4]; // initialise a avec le contenu de la 4 ième case

    try {
        v[6]; // doit produire une erreur (exemple throw 1; ou exit(1))
    } catch (out_of_range& e) {
        cout << e.what() << endl;
    }

    int max = v.max(); // renvoie l'entier maximum
    int min = v.min(); // renvoie l'entier minimum

    vector_t b = v * 3; // multiplie par 3 chaque case, produit un nouveau vecteur
    assert(b[3] != v[3]); // b et v sont différents

    r = v * 4; // multiplie par 4 chaque case, produit un nouveau vecteur
    // pas de fuite de mémoire ni de double libération


    // Pour construire un objet constant c de la classe vector_t de longueur 6 cases qui contient 2,3,5,7,11,13
    const vector_t c = {2, 3, 5, 7, 11, 13};


    return 0;
}


