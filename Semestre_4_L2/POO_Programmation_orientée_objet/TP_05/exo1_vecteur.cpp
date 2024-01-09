

#include <iostream>
#include "vecteur.hpp"

using namespace std;

vector_t::vector_t(int t) {
    taille = t;
}
        
vector_t::~vector_t(void) {}



int main(void){
    vector_t v(5);  // tableau de 5 cases allouée
    vector_t r(500000); // tableau de 5000000 cases allouées
    // v[3]=2; // met la valeur 2 dans la case d'indice 3
    // int a=t[4]; // initialise a avec le contenu de la case d'indice 4
    // v[6]; // doit produire une erreur d'indice : throw 1;
    // v.max() // renvoie l'entier maximum
    // v.min() // renvoie l'entier minimum
    // v*3; // multiplie par 3 chaque élément, produit un nouveau vecteur
    // 3*v; // multiplie par 3 chaque élément, produit un nouveau vecteur
}


