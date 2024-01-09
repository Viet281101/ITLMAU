
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct s_noeud_t{
	int v; //étiqueté (ou value)
	struct s_noeud_t * g;
	struct s_noued_t * d;
}noeud_t;


noeud_t * consA(noeud_t * gauche, noeud_t * droit, int etiquete){
	noeud_t * n = (noeud_t*)malloc(sizeof(*gauche));
	if (n == NULL)
		exit(1);
	n -> g = gauche;
	n -> d = droit;
	n -> v = etiquete;
	return n;
}

// noeud_t * t = consA(NULL, NULL, e)



void parcoursPrefixe(noeud_t * racine){
	if (racine == NULL){
		printf("V ");
		return;
	}
	printf("%d \n", racine -> v);
	parcoursPrefixe(v -> g);
	parcoursPrefixe(v -> d);
}

int main(void)
{
	
	return 0;
}


