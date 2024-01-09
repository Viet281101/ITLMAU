
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct s_cellule_t
{
	int val; // valeur
	struct s_cellule_t* suiv; // suiv
} cellule_t;
// la liste vide sera NULL


/* EX 1: Opérations de base */
cellule_t* consL(int val, cellule_t* queue){
	cellule_t * li = malloc(sizeof(*li));
	assert(li);
	li -> val = val;
	li -> suiv = queue;
	return li;
}

cellule_t* libererL(cellule_t* liste){
	cellule_t * ptr = liste;
	while(ptr != NULL) {
		cellule_t * tofree = ptr;
		ptr = ptr->suiv;
		free(tofree);
	}
	return liste = NULL;
}

void afficherL(cellule_t* liste){
	while(liste != NULL) {
		printf("%d ", liste -> val);
		liste = liste -> suiv;
	}
	printf("\n");	
}


/* EX 2: Opérations de calcul */
int longueurL(cellule_t* li){
	int i = 0;
	while (li != NULL){
		i++;
		li = li -> suiv;
	}
	return i;
}

int sommeL(cellule_t* li){
	int somme = 0;
	while (li != NULL){
		if (li -> val >= 0) somme += li -> val;
		li = li -> suiv;
	}
	return somme;
}

int estTrieeL(cellule_t* li){
	int x = -65536;
	while (li != NULL){
		if (li -> val < x) return 0;
		x = li -> val;
		li = li -> suiv;
	}
	return 1;
}


/* EX 3: Opération de modification*/
void ajouteEnTeteL(int val, cellule_t** li){
	cellule_t * lst = malloc(sizeof(*lst));
	lst -> val = val;
	lst -> suiv = *li;
	*li = lst;
}

void fusionL(cellule_t* liC, cellule_t* liS){
	cellule_t *resDebut, *resFin, *temp;
	resDebut = resFin = NULL;
	while(1){
		if (liC == NULL){
			resFin -> suiv = liS;
			break;
		}
		if (liS == NULL){
			resFin -> suiv = liC;
			break;
		}

		if (liC -> val <= liS -> val){
			temp = liC;
			liC = liC -> suiv;
		} else {
			temp = liS;
			liS = liS -> suiv;
		}

		if (resDebut == NULL) resDebut = resFin = temp;
		else{
			resFin -> suiv = temp;
			resFin = temp;
		}
		resFin -> suiv = NULL;
	}
	// libererL(liS);
}


/* EX 4 : Extraire et inserer */
void insererL(int val, cellule_t** li, int i){
    cellule_t* head = (*li);
    cellule_t* new_cell = malloc(sizeof(*new_cell));
    new_cell -> val = val;
 
    int j = 0;
    cellule_t* temp;
    int len = longueurL(head);
    if (i > len){
        printf("Erreur\n");
        exit(1);
    }
    if (i == 0) consL(val, head);
    while (j != i -1){
		head = head -> suiv;
		j++;
    }
    temp = head -> suiv;
    head -> suiv = new_cell;
    new_cell -> suiv = temp;
}

cellule_t* extraireL(cellule_t** li, int i){
	cellule_t * res = NULL, **lst;
	for (i = 0; *li; li = &(*li) -> suiv){
		if (i >= 0) break;
		i++;
	}
	res = *li;
	for(lst = li; *lst; lst = &(*lst) -> suiv){
		if (i >= 1) break;
	}
	*li = *lst;
	*lst = NULL;
	return res;
}


/* EX 5 : Inserer dans l'ordre */
void insererTriee(int val, cellule_t** li){
	if (!estTrieeL(*li)) {
		printf("Liste non trie\n"); 
		return;
	}
	if ((*li) == NULL) {
		ajouteEnTeteL(val, &(*li)); 
		return;
	}
	if (val <= (*li) -> val) {
		ajouteEnTeteL(val, &(*li)); 
		return;
	}
	insererTriee(val, &((*li) -> suiv));
}


/* EX 6 : Miroir */
void miroir(cellule_t** li){
	cellule_t * avant = NULL;
	cellule_t * lst = *li;
	cellule_t * apres = NULL;
	while (lst != NULL){
		apres = lst -> suiv;
		lst -> suiv = avant;
		avant = lst;
		lst = apres;
	}
	*li = avant;
}


int main(void)
{
	cellule_t* l = NULL, *s = NULL;
	l = consL(10, l);
	l = consL(5, l);
	l = consL(1, l);
	l = consL(-1, l);
	ajouteEnTeteL(-5, &l);
	insererTriee(8, &l);
	insererL(4, &l, 3);

	s = consL(7, s);
	s = consL(9, s);
	s = consL(12, s);
	s = consL(3, s);

	printf("\nliste l : ");
	afficherL(l);
	printf("\nliste s : ");
	afficherL(s);

	printf("\nLa longueur de la liste l est : %d\n", longueurL(l));
	printf("\nla somme des éléments positifs de la liste l est : %d\n", sommeL(l));

	if (estTrieeL(l) == 1) printf("\nLes éléments de la liste sont dans l'ordre croissant. \n");
	else printf("\nLes éléments de la liste ne sont pas dans l'ordre croissant. \n");

	printf("\nFusionne liste l et liste s : ");
	fusionL(l, s);
	afficherL(l);

	printf("\nInverse l'ordre des éléments de la liste l : ");
	miroir(&l);
	afficherL(l);

	printf("\nLibere la memoire des listes : ");
	libererL(l);
	libererL(s);
	afficherL(l);
	
	return 0;
}
