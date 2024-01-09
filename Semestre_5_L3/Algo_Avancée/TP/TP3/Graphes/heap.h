#include <stdio.h>
#include <stdlib.h>
#include<time.h>

/* Structure de tas et fonctions utiles */
typedef struct noeudTas{
    int  v;
    int dist;
} noeudTas;

typedef struct Tas{
    int taille;
    int capacite;
    int *pos;
    struct noeudTas **array;
} Tas;


noeudTas * new_noeudTas(int v, int dist);
Tas * creer_tas(int n);
void echange_noeud(noeudTas **a, noeudTas **b);
void entasser(Tas* tas, int idx);
int is_empty_tas(struct Tas* tas);
noeudTas* extract_min(Tas* tas);
void decrease_value(struct Tas* tas, int v, int dist);
int is_in_tas(Tas *tas, int v);