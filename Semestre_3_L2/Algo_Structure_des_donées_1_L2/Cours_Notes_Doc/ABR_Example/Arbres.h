/* Arbres Binaires de Recherche ( ABR ) */

struct Noeud
{
    int valeur ;
    struct Noeud* gauche ;
    struct Noeud* droit ;
};

typedef struct Noeud TNoeud; // pour �viter de tra�ner "struct" partout.
typedef struct Noeud* TArbre; // d�finit le pointeur clairement.


TArbre NouvelArbreVide( void );  // cr�e un nouvel arbre vide retourne un Tarbre.

void Ajouter( TArbre* arbre , int val ); // ajoute une valeur dans un arbre, prend un pointeur
                                         // sur un Tarbre

void Afficher( TArbre arbre );  // Afficher l'arbre en parcours infixe en main gauche

int NombreElements( TArbre arbre ); // Compte le nombre d'�l�ments entr�s dans l'arbre

int Hauteur( TArbre arbre ); // retourne la hauteur de l'arbre

int Somme( TArbre arbre ); // retourne la somme des �l�ments de l'arbre, retourne 0 si l'arbre
                           // est vide
