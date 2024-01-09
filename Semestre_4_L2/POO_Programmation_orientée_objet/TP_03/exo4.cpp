
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



int main() {
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

    return 0;
}



