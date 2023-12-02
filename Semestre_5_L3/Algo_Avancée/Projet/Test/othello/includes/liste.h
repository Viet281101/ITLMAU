#ifndef OTHELLO_LISTE_H
#define OTHELLO_LISTE_H 1

typedef struct jeton Jeton;

/* Élement de la liste */
struct element {
    Jeton *jeton;
    struct element *suivant;
};
typedef struct element Element;

/* Créer un nouvel élément pour la liste */
Element *nouvel_element(Jeton *jeton);

/* Liste chaînée */
struct list {
    Element *premier;
};
typedef struct list Liste;

/* Créer une nouvelle liste vide */
Liste *nouvelle_liste(void);

/* Ajoute un élément à la liste */
void ajoute_liste(Liste *liste, Element *nouvel_element);

/* Supprime un élément de la liste */
void supprime_liste(Element *element_actuel, Jeton *jeton);

/* Affiche la liste */
void affiche_liste(const Element *element);

/* Renvoie une copie de la liste */
Liste *copie_liste(const Liste *liste);

/* Libère la liste en mémoire */
void free_liste(Liste *liste);

#endif
