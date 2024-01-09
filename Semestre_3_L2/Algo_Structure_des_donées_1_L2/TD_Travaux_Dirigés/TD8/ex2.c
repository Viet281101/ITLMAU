
#include <stdio.h>
#include <stdlib.h>

typedef struct s_noeud_t
{
    int v; // étiquette du noeud (v pour valeur)
    struct s_noeud_t* g; // pointeur vers la racine du sous-arbre gauche
    struct s_noeud_t* d; // pointeur vers la racine du sous-arbre droit
} noeud_t;


void initialiserPA(pileA_t* p)
noeud_t* dePilerA(pileA_t* p)
void detruirePA(pileA_t* p)
int estVidePA(pileA_t* p)// renvoie 1 si *p est une pile vide
void emPilerA(pileA_t* p,noeud_t* n)


void pacoursPrefPile(noeud_t * racine){
    pileA_t * p;
    initialiserPA(&p);
    empiler(&p, racine);
    while (!estVidePA(&p))
    {
        racine = dePiler(&p);
        if (racine != NULL){
            printf("%d ", racine -> v);
            empiler(&p, racine -> d);
            empiler(&p, racine -> g);
        }else printf("V ");
    }
    
}

int main(void)
{

    return 0;
}



