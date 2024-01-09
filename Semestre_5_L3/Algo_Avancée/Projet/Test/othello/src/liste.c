#include "../includes/jeu.h"

Element *nouvel_element(Jeton *jeton) {
    Element *element = malloc(sizeof(Element));
    element->jeton = jeton;
    element->suivant = NULL;

    return element;
}

Liste *nouvelle_liste(void) {
    Liste *liste = malloc(sizeof(Liste));
    liste->premier = NULL;

    return liste;
}

void ajoute_liste(Liste *liste, Element *nouveau) {
    Element *ptr = liste->premier;
    while (ptr) {
        ptr = ptr->suivant;
    }
    nouveau->suivant = liste->premier;
    liste->premier = nouveau;
}

void supprime_liste(Element *elem, Jeton *data) {
    Element *precedent = elem;
    Element *actuel = elem;
    while (actuel) {
        if (actuel->jeton->pos_i == data->pos_i &&
            actuel->jeton->pos_j == data->pos_j) {
            precedent->suivant = actuel->suivant;
            free(actuel);

            return;
        } else {
            precedent = actuel;
            actuel = actuel->suivant;
        }
    }

    fprintf(stderr, "Élement introuvable dans la liste (");
    affiche_jeton(stderr, data);
    fprintf(stderr, ").\n");
    exit(EXIT_FAILURE);
}

void affiche_liste(const Element *element) {
    if (element) {
        affiche_liste(element->suivant);
        affiche_jeton(stdout, element->jeton);
        printf(" ");
    }
}

Liste *copie_liste(const Liste *liste) {
    Liste *res = nouvelle_liste();

    Element *element = liste->premier;
    while (element) {
        ajoute_liste(res, nouvel_element(element->jeton));

        element = element->suivant;
    }

    return res;
}

void free_liste(Liste *liste) {
    Element *actuel = liste->premier;

    while (actuel) {
        Element *suivant = actuel->suivant;
        free(actuel);
        actuel = suivant;
    }

    free(liste);
}
