
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


typedef struct s_noeudh_t{
    int v; // étiquette du noeud (v pour valeur)
    struct s_noeudh_t* g; // pointeur le sous-arbre gauche
    struct s_noeudh_t* d; // pointeur le sous-arbre droit
    int h; // hauteur du sous-arbre enraciné en ce noeud (h pour hauteur)
} noeudh_t;


void creerNoeud( noeudh_t **arbre, int valeur )
{
    noeudh_t *noeud = malloc(sizeof(noeudh_t));
    assert(noeud);
    if(noeud != NULL)
    {
        noeud->v = valeur;
        noeud->g = NULL;
        noeud->d = NULL;
        noeud->h = 0;
    }
    *arbre = noeud;
}


int ajouterABR( noeudh_t **a, int x )
{
    if ( (*a) == NULL ){
        creerNoeud( &(*a), x );
        return 0;
    }
    if ( (*a)->v > x ){
        if ( (*a)->g == NULL ){
            creerNoeud( &(*a)->g, x );
            return 0;
        }
        else {
            ajouterABR( &(*a)->g, x );
        }
    }
    if ( (*a)->v < x ){
        if ( (*a)->d == NULL ){
            creerNoeud( &(*a)->d, x );
            return 0;
        }
        else {
            ajouterABR( &(*a)->d, x );
        }
    }
    return 1;
}


void parcoursPref(noeudh_t* a)
{
   if(a==NULL)
   {
      printf("NULL ");
      return;
   }
   printf("%d ",a->v);
   parcoursPref(a->g);
   parcoursPref(a->d);
   printf("\n");
}


int chercher(noeudh_t* a, int x){
    while(a){
        if(x == a->v) return 1;

        if(x > a->v) a = a->d;
        else a = a->g;
    }
    return 0;
}

int extraireMaxABR(noeudh_t** a){
    if ((*a) == NULL) return 0;
    int max = (*a)->v;
    if ((*a)->g){
        int gauche = extraireMaxABR (&(*a)->g);
        max = (max > gauche ) ? max : gauche;
    }
    if ((*a)->d){
        int droit = extraireMaxABR (&(*a)->d);
        max = (max > droit ) ? max : droit;
    }
    return max;
}

int extraireMinABR(noeudh_t** a){
    if ((*a) != NULL) return 0;
    int min = (*a)->v;
    if ((*a)->g){
        int gauche = extraireMinABR (&(*a)->g);
        min = (min < gauche ) ? min : gauche;
    }
    if ((*a)->d){
        int droit = extraireMinABR (&(*a)->d);
        min = (min < droit ) ? min : droit;
    }
    return min;
}

void fixer(noeudh_t **a, int x);
int supprimerMax(noeudh_t **a);
int supprimerABR(noeudh_t** a,int x){
    if((*a)->v < x) {
        supprimerABR((&(*a)->d),x);
        return 1;    
    }
    else if ((*a)->v > x)  {
        supprimerABR((&(*a)->g),x);
        return 1;
    }
    else if ((*a)->g==NULL) (*a)=(*a)->d;
    else if ((*a)->d==NULL) (*a)=(*a)->g;
    else {
        fixer(&(*a), supprimerMax(&(*a)->d));
        return 1;
    }
    return 0;
}

int max(int a,int b)
{
   return a>b?a:b;
}

int hauteurAVL(noeudh_t* r)
{
    if(r==NULL)
        return 0;
    return (1 + max(hauteurAVL(r->g), hauteurAVL(r->d)));
}

void miseAJHaut(noeudh_t* r){
    if(r != NULL){
        (r)->h = hauteurAVL(r->g) - hauteurAVL(r->d);
    }
}

void rotationG(noeudh_t** r){
    noeudh_t *arbre = (*r)->d;
    if(*r){
        (*r)->d = arbre->g;
        arbre->g = (*r);
        *r = arbre;
        miseAJHaut((*r));
        miseAJHaut((*r)->g);
    }
}

void rotationD(noeudh_t** r){
    noeudh_t *arbre = (*r)->g;
    if(*r){
        (*r)->g = arbre->d;
        arbre->d = (*r);
        *r = arbre;
        miseAJHaut((*r));
        miseAJHaut((*r)->d);
    }
}


void equilibrer(noeudh_t* r){
    if(r != NULL){
        if((r)->h == 2){
            if(((r)->g)->h == -2) {
                rotationD(&r->d);
                rotationG(&r);
            }
            else rotationD(&r);
        }
        else if ((r)->h == -2){
            if(((r)->d)->h == 2) {
                rotationG(&r->g);
                rotationD(&r);
            }
            else rotationG(&r);
        }
        else miseAJHaut(r);
    }
}

int ajouterAVL(noeudh_t** r, int x){
    if(*r != NULL){
        if( x == (*r)->v) return 0;
        else if(x < (*r)->v){
            ajouterAVL(&(*r)->g, x);
            miseAJHaut(*r);
            equilibrer(*r);
            return 1;
        } else if ( x > (*r)->v){
            ajouterAVL(&(*r)->d, x);
            miseAJHaut(*r);
            equilibrer(*r);
            return 1;
        }
    }
    return 0;
}

int extraireMaxAVL(noeudh_t** ar){
    int temp;
    int gauche, droite;
    int max = -99;
    if(*ar != NULL){
        temp = (*ar) -> v;
        gauche = extraireMaxAVL(&(*ar) -> g);
        droite = extraireMaxAVL(&(*ar) -> d);
        if(gauche > droite) max = gauche;
        else max = droite;
        if(temp > max) max = temp;
    }
    return max;
}

int extraireMinAVL(noeudh_t** ar){
    int temp;
    int gauche, droite;
    int min = 99;
    if(*ar != NULL){
        temp = (*ar) -> v;
        gauche = extraireMinAVL(&(*ar) -> g);
        droite = extraireMinAVL(&(*ar) -> d);
        if(gauche < droite) min = gauche;
        else min = droite;
        if(temp < min) min = temp;
    }
    return min;
}

int supprimerAVL(noeudh_t** r, int val);

int main(void){
    
    noeudh_t* arbre=NULL; 
    ajouterABR(&arbre,3);
    ajouterABR(&arbre,6);
    
    parcoursPref(arbre);

    printf("%d\n", chercher(arbre,3));
    printf("%d\n", extraireMinABR(&arbre));
    printf("%d\n", extraireMaxABR(&arbre));

    supprimerABR(&arbre, 3);
    parcoursPref(arbre);

    noeudh_t* arbreAVL=NULL; 
    ajouterAVL(&arbreAVL, 5);
    ajouterAVL(&arbreAVL, 9);
    parcoursPref(arbreAVL);

    printf("%d\n", hauteurAVL(arbre));

    return 0;
}


void fixer(noeudh_t **a, int x){
    (*a)->v=x;
}
int supprimerMax(noeudh_t **a){
    int val;
    if((*a)->d==NULL){ 
        val=(*a)->v;
        (*a)=NULL;
        free(*a);
        return val;
    }
    else return supprimerMax(&(*a)->d);
}

