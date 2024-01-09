
#include <iostream>
#include <string>

using namespace std;

int main(void) {
    string a="Bonjour ";
    string b="à tous !";
    string d=to_string(15);
    string c=a+b;
    char c=b[0]; // renvoie le première octet du codage de "à tous !"
    cout << c + d << endl; // affiche Bonjour à tous !15
    cout << c=="au revoir à tous" << endl ;
    // (c=="..." compare un string et une chaine de caractère)
}


