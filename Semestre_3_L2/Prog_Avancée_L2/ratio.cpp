#include <assert.h>
#include <iostream>
using namespace std;

// Classe pour gérer les nombres rationnels
class Ratio {
private:
  int p;
  unsigned int q;
public:
  static int pgcd(int a, int b) { // selon l'algorithme d'Euclide
    if(a == b)
      return a;
    if(a > b)
      return pgcd(a - b, b);
    return pgcd(a, b - a);
  }
  Ratio(int p, int q) {
    assert(q);
    int signe_p = 1, signe_q = 1;
    if(p < 0) {
      signe_p = -1;
      p = -p;
    }
    if(q < 0) {
      signe_q = -1;
      q = -q;
    }
    int d = Ratio::pgcd(p, q);
    this->p = signe_p * signe_q * (p / d);
    this->q = q / d;    
  }
  friend ostream& operator<<(ostream &os, Ratio me) {
    os << "(" << me.p << "/" << me.q << ") ";
    return os;
  }
};

int main(void) {
  Ratio a(2, 10), b(12, -16), c(1, 3);
  // a est donc 2/10 soit 1/5 ;
  // b est donc 12/(-16) soit -3/4
  // c est 1/3
  cout << a << ", " << b << ", " << c << endl;
  // *** jusqu'ici le code compile ***
  
  // *** à partir de la ligne suivante, les opérateurs manquent à l'appel ***
  // ==>> TODO : les implémenter
  Ratio d = b * c;
  Ratio e = a + d;
  cout << "Le résultat final est : " << -e << endl;
  // Le résultat censé être obtenu est 1/20
  return 0;
}
