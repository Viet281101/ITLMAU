
#include <iostream>

using namespace std;


class intreliee_t {
    public:
        intreliee_t(int a) {
            val = a;
            sommeGlobale += a;
            next = first;
            first = this;
        }

        void set(int a) {
            sommeGlobale += a - val;
            val = a;
        }

        int get() {
            return val;
        }

        static int somme() {
            int sum = 0;
            for (intreliee_t* obj = first; obj != nullptr; obj = obj->next) {
                sum += obj->val;
            }
            return sum;
        }

    private:
        int val;
        intreliee_t* next;
        static intreliee_t* first;
        static int sommeGlobale;
};

intreliee_t* intreliee_t::first = nullptr;
int intreliee_t::sommeGlobale = 0;





class intreliee2_t {
private:
    int* valeur;
    static int somme_globale;

public:
    intreliee2_t(int a = 0) {
        valeur = new int(a);
        somme_globale += a;
    }

    intreliee2_t(const intreliee2_t& other) {
        valeur = new int(*other.valeur);
        somme_globale += *valeur;
    }

    ~intreliee2_t() {
        somme_globale -= *valeur;
        delete valeur;
    }

    void set(int a) {
        somme_globale += a - *valeur;
        *valeur = a;
    }

    int get() const {
        return *valeur;
    }

    intreliee2_t& operator=(const intreliee2_t& other) {
        if (this != &other) {
            somme_globale -= *valeur;
            delete valeur;
            valeur = new int(*other.valeur);
            somme_globale += *valeur;
        }
        return *this;
    }

    static int somme() {
        return somme_globale;
    }
};

int intreliee2_t::somme_globale = 0;


int main() {
    //// Tester la classe intreliee_t
    intreliee_t a(1);
    intreliee_t b(2);
    intreliee_t c(3);
    cout << "Valeur de a : " << a.get() << endl;
    cout << "Valeur de b : " << b.get() << endl;
    cout << "Valeur de c : " << c.get() << endl;
    b.set(4);
    c.set(5);
    cout << "Valeur de a : " << a.get() << endl;
    cout << "Valeur de b : " << b.get() << endl;
    cout << "Valeur de c : " << c.get() << endl;
    cout << "Somme globale : " << intreliee_t::somme() << endl;


    //// Tester la classe intreliee_t
    intreliee2_t d(1);
    intreliee2_t e(2);
    intreliee2_t f(3);
    cout << "Valeur de d : " << d.get() << endl;
    cout << "Valeur de e : " << e.get() << endl;
    cout << "Valeur de f : " << f.get() << endl;
    e.set(4);
    f.set(5);
    cout << "Valeur de d : " << d.get() << endl;
    cout << "Valeur de e : " << e.get() << endl;
    cout << "Valeur de f : " << f.get() << endl;
    cout << "Somme globale : " << intreliee2_t::somme() << endl;

    return 0;
}


