
#include <iostream> // pour ostream, cout
#include <cstring> // pour strlen, strcpy, strcat
#include <string>
#include <cassert>

using namespace std;

class chaine_t {
public:
    // Constructeurs
    chaine_t() : chaine_(new char[1]), longueur_(0) { chaine_[0] = '\0'; }
    chaine_t(const char* chaine) : chaine_(new char[strlen(chaine)+1]), longueur_(strlen(chaine)) {
        strcpy(chaine_, chaine);
    }
    chaine_t(int entier) {
        string chaine = to_string(entier);
        chaine_ = new char[chaine.length()+1];
        strcpy(chaine_, chaine.c_str());
        longueur_ = chaine.length();
    }
    chaine_t(const chaine_t& autre) : chaine_(new char[autre.longueur_+1]), longueur_(autre.longueur_) {
        strcpy(chaine_, autre.chaine_);
    }
    ~chaine_t() {
        delete[] chaine_;
    }

    // Opérateurs d'affectation
    chaine_t& operator=(const chaine_t& autre) {
        if (this != &autre) {
            delete[] chaine_;
            chaine_ = new char[autre.longueur_+1];
            strcpy(chaine_, autre.chaine_);
            longueur_ = autre.longueur_;
        }
        return *this;
    }

    chaine_t& operator+=(const chaine_t& autre) {
        char* nouvelle_chaine = new char[longueur_ + autre.longueur_ + 1];
        strcpy(nouvelle_chaine, chaine_);
        strcat(nouvelle_chaine, autre.chaine_);
        delete[] chaine_;
        chaine_ = nouvelle_chaine;
        longueur_ += autre.longueur_;
        return *this;
    }

    friend chaine_t operator+(const chaine_t& a, const chaine_t& b) {
        chaine_t resultat(a);
        resultat += b;
        return resultat;
    }

    char& operator[](int i) {
        assert(i >= 0 && i < longueur_);
        return chaine_[i];
    }

    const char& operator[](int i) const {
        assert(i >= 0 && i < longueur_);
        return chaine_[i];
    }

    // Méthodes
    int longueur() const {
        return longueur_;
    }

    void append(const chaine_t& autre) {
        *this += autre;
    }

    string toString() const {
        return string(chaine_);
    }

    // Opérateurs de comparaison
    bool operator==(const chaine_t& autre) const {
        return strcmp(chaine_, autre.chaine_) == 0;
    }

    bool operator!=(const chaine_t& autre) const {
        return !(*this == autre);
    }

private:
    char* chaine_;
    int longueur_;
};

// Fonction pour afficher une chaine_t sur un flux de sortie
ostream& operator<<(ostream& os, const chaine_t& chaine) {
    os << chaine.toString();
    return os;
}

void fonction(chaine_t a){a.append("coucou");}

int main() {
    chaine_t a;
    chaine_t b{"Bonjour"};
    const chaine_t c{"Salut"}; // const ajouté ici
    chaine_t m{"Ave"}; // accolades ajoutées ici
    chaine_t n{45}; // accolades ajoutées ici, contient "45"
    chaine_t l = b;
    chaine_t* d = new chaine_t{"Au revoir"};
    a.append(b); // ajoute le contenu de b à la fin de a (sans modifier b)
    a=b+c; // a contient ici la concatenation de b et c
    b[4]='u'; // on modifie le 4 eime octets
    assert(b[4]!=l[4]); // doit être vrai
    assert(a[4]!=l[4]); // doit être vrai
    // c[3]='o'; erreur à la compilation
    char u=c[3]; // ok (penser que le qualificatif method(...) const {...} fait partie de la signature)
    // c.append(a) ; erreur c est const
    // b[66]='u'; // erreur d'execution l'indice est trop grand 66>longueur(b)
    chaine_t a4 = b + b + b + b; // renvoie la chaine b dupliquée 4 fois
    chaine_t c3 = c3; // met dans b une chaine qui est dupliquée 3 fois : "SalutSalutSalut"
    cout << c.toString() << endl; // la fonction membre toString() renvoie un string
    bool cmp1 = (c==a); // egale vrai ou faux (ici faux)
    bool cmp2 = (c!=a); // egale le contraire (ici vrai)
    delete d;
    fonction(a);
    // ici a est inchangé car mfonction modifie une variable copiée

    return 0;
}


