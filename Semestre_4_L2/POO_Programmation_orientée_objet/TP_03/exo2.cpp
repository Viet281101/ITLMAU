
#include<iostream>


using namespace std;


class CompteInstance {
    public:
        CompteInstance() {
            compteur++;
        }
        ~CompteInstance() {
            compteur--;
        }
        static int compter() {
            return compteur;
        }
    private:
        static int compteur;
};

int CompteInstance::compteur = 0;


int main(void) {

    CompteInstance a;
    {
        CompteInstance b;
        CompteInstance c;
        CompteInstance d;
        cout<<CompteInstance::compter()<<endl; // il va renvoie 4 (car 4 objets a b c d)
    }
    cout<<CompteInstance::compter()<<endl; // il va renvoie 1 (seule a existe ici)

    return 0;
}



