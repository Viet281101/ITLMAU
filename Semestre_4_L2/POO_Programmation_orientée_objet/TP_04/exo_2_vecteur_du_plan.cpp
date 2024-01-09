
#include <iostream>
#include <cmath>

using namespace std;

class vecteur2d_t {
public:
    float x, y;

    vecteur2d_t() : x(0), y(0) {}
    vecteur2d_t(float x_, float y_) : x(x_), y(y_) {}

    vecteur2d_t operator+(const vecteur2d_t& v) const {
        return vecteur2d_t(x + v.x, y + v.y);
    }

    vecteur2d_t operator*(float a) const {
        return vecteur2d_t(x * a, y * a);
    }

    float operator||(const vecteur2d_t& v) const {
        return x * v.x + y * v.y;
    }

    vecteur2d_t operator&&(const vecteur2d_t& v) const {
        cerr << "Le produit vectoriel n'existe pas en 2D." << endl;
        return vecteur2d_t();
    }

    void afficher() const {
        cout << "(" << x << ", " << y << ")" << endl;
    }
};


int main() {
    vecteur2d_t o{0, 0}, a{3, 4};
    vecteur2d_t c = o + a;
    c.afficher(); // affiche (3, 4)
    c = c * 4.5;
    a.afficher(); // affiche (3, 4)
    float h = a || c;
    cout << h << endl; // affiche 25.5
    return 0;
}


