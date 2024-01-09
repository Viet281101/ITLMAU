

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


typedef struct s_noeud_t
{
	int v; // étiquette du noeud (v pour valeur)
	struct s_noeud_t* g; // pointeur vers la racine du sous-arbre gauche
	struct s_noeud_t* d; // pointeur vers la racine du sous-arbre droit
} noeud_t;
// l'arbre vide aura la valeur NULL


/* EX 1 : Operation de base*/
noeud_t* consA(noeud_t* gau, noeud_t* droit, int etiquette){
	noeud_t * arbre = (noeud_t*)malloc(sizeof(*arbre));
	assert(arbre);
	if (arbre == NULL) // exit(1);
		return NULL;
	arbre -> g = gau;
	arbre -> d = droit;
	arbre -> v = etiquette;
	return arbre;
}

void liberer(noeud_t* a){
	if (a != NULL){
		liberer(a -> g);
		liberer(a -> d);
		free(a);
		a = NULL;
	}
}


/* EX 2: Parcours */ 
void parcourirPref(noeud_t * a){
	if (a == NULL) return;
	printf("%d \t", a -> v);
	parcourirPref(a -> g);
	parcourirPref(a -> d);
}

void parcourirPost(noeud_t* a){
	if (a == NULL) return;
    parcourirPost(a -> g);
    parcourirPost(a -> d);
    printf("%d \t", a -> v);
}

void parcourirInfix(noeud_t* a){
    if (a == NULL) return;
    parcourirInfix(a -> g);
    printf("%d \t", a -> v);
    parcourirInfix(a -> d);
}



/* EX 3: Compter */
int taille(noeud_t* arbre){
	static int compte = 0;
	if (arbre != NULL){	
		taille(arbre -> g);
		compte++;
		taille(arbre -> d);
	}
	return compte;
}

int nbFeuilles(noeud_t* arbre){
	if (arbre == NULL) return 0;
    if(arbre -> g == NULL && arbre -> d == NULL)
        return 1;
    else return (nbFeuilles(arbre -> g) + nbFeuilles(arbre -> d));
}

int hauteur(noeud_t* a){
    if (a == NULL) return -1;
    else{	
		int gauche;
		int droite;
		gauche = hauteur(a -> g);
		droite = hauteur(a -> d);
		if(gauche > droite)
		{
			return gauche + 1;
		}else return droite + 1;
	}
}



/* EX 4: Trouver */
int estDans(noeud_t* a, int v){
	if (a == NULL) return 0;
	if (v == a -> v) return 1;
	else return 0;
	if (v < a -> v) estDans(a -> g, v);
	if (v > a -> v) estDans(a -> d, v);
}


/* EX 5: Construction par parcours prefixe */
// void construirePref(noeud_t** a){

// };


// int construirePrefT(neud_t** A,int* tab){

// };


int main(void){

	noeud_t * a = consA(consA(consA(NULL,NULL,4),consA(NULL,NULL,5),3),consA(NULL,NULL,2),1);

	printf("\nPour imprimer le resultat d'un parcours prefixe de l'arbre : \n");
    parcourirPref(a);

    printf("\nPour imprime le resultat d'un parcours postfixe de l'arbre: \n");
    parcourirPost(a);

    printf("\nPour imprime le resultat d'un parcours infixe de l'arbre: \n");
    parcourirInfix(a);

	
	printf("\n\nLe nombre de noeuds (étiqueté) d'arbre a: \t%d\n\n", taille(a));
	printf("\nLa nombre les feuilles dans l'arbre est : \t%d\n\n", nbFeuilles(a));
	printf("\nLa hauteur de l'arbre est : \t%d\n\n", hauteur(a));

	int i;
	printf("\nVeuillez entrez une valeur de trouver s'il est une étiquette de l'arbre a: \t");
	scanf("%d", &i);
	if (estDans(a, i) == 1){
		printf("La valeur %d est une étiquette de l'arbre a !\n", i);
	}else printf("La valeur %d n'est pas une étiquette de l'arbre a !\n", i);

	printf("\nApres libere arbres a: \n");
	liberer(a);
	parcourirPref(a);

	printf("\n");
	return 0;
}




