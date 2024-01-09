


#include <stdio.h>

typedef struct s_noeud_t
{
	int v; // étiquette du noeud (v pour valeur)
	struct s_noeud_t* g; // pointeur vers la racine du sous-arbre gauche
	struct s_noeud_t* d; // pointeur vers la racine du sous-arbre droit
} noeud_t;
// l'arbre vide aura la valeur NULL




