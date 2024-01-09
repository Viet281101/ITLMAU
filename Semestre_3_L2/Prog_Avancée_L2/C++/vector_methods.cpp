

#include <iostream>
#include <vector>

using namespace std;

#include <time.h>
#include <stdlib.h>

int main (void){
    vector <int> vecDInts;
    vector <float> vecDeFloats;
    int n = 10;

    // remplir les deux vecteurs
    for (int i = 0; i < n; ++i){
        vecDInts.push_back(rand() % n);
        vecDeFloats.push_back( (float)n * rand() / (RAND_MAX + 1.0f) );
    }

    // afficher les element de vecDInts (method "classique")
    for (int i = 0; i < (int)vecDInts.size(); ++i){
        cout << vecDInts.at(i) << " ";
    }
    cout << endl ;

    // afficher les elements de vecDInts ( avec les iterators )
    for ( vector <int> :: iterator it = vecDInts.begin() ; it < vecDInts.end(); ++ it ) {
        cout << *it << " ";
    }
    cout << endl ;
    
    // une écriture encore plus concise , on l'utilise ici pour vecDeFloats
    // c'est du C ++11 ( on dirait presque du python
    for ( float f : vecDeFloats ) {
        cout << f << " ";
    }
    cout << endl ;

    // on peut effacer avant de sortir
    vecDInts.clear () ;
    vecDeFloats.clear () ;
    return 0;
}


