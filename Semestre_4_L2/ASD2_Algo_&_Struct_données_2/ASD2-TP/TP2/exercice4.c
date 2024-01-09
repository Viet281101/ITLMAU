
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>


typedef struct s_noeud_t {
	int v;
	struct noeud_t* g;
	struct noeud_t* d;
} noeud_t;


noeud_t* add_node(int val);
void inserer(noeud_t* tree, int n);
int hauteur(noeud_t* tree);
int max(int a, int b);
void print_tree(noeud_t* tree);
void liberer(noeud_t* a);
int is_ABR_rec(noeud_t* arbre, int *min, int *max);
int test_ABR(noeud_t* arbre);



int main(void) {
	noeud_t *tree = add_node(5);
	inserer(tree, 4);
	inserer(tree, 5);
	inserer(tree, 7);
	inserer(tree, 2);
	inserer(tree, 9);

	print_tree(tree);


	return 0;
}


noeud_t* add_node(int val) {
	noeud_t* tree = malloc(sizeof(noeud_t));
	assert(tree);

	tree->v = val;
	tree->g = NULL;
	tree->d = NULL;

	return tree;
}


void liberer(noeud_t* a){
	if (a != NULL){
		liberer(a -> g);
		liberer(a -> d);
		free(a);
		a = NULL;
	}
}


void inserer(noeud_t* tree, int n) {
	if (tree->g == NULL) {
		tree->g = add_node(n);
		return;
	}
	else if (tree->d == NULL) {
		tree->g = add_node(n);
		return;
	}

	if (hauteur(tree->g) > hauteur(tree->d)) {
		inserer(tree->d, n);
	}else {
		inserer(tree->g, n);
	}
}


int max(int a, int b){
	if (b > a) return b;
	return a;
}


int hauteur(noeud_t* tree) {
	if (tree == NULL) {
		return 1;
	}

	return 1 + max(hauteur(tree->g), hauteur(tree->d));
}


void print_tree(noeud_t* tree) {
	printf("%d ->", tree->v);

	if (tree->g != NULL) print_tree(tree->g);
	if (tree->d != NULL) print_tree(tree->d);

}


int is_ABR_rec(noeud_t* arbre, int *min, int *max){
	int i;
	int is_ABR;

	*min = *max = arbre->v;	
	if (arbre->g != NULL){
		is_ABR = is_ABR_rec(arbre->g, min, &i); 
		if (is_ABR == 0 || arbre->v <= i){
			return 0;
		}
	}
	if (arbre->d != NULL){
		is_ABR = is_ABR_rec(arbre->d, &i, max); 
		if (is_ABR == 0 || arbre->v > i){
			return 0;
		}
	}
	return 1;
}
	
int test_ABR(noeud_t* arbre){
	int min, max;
	if	(is_ABR_rec(arbre, &min, &max)){
		printf("L'arbre est un ABR, val min : %d, val max: %d", min, max);
	}
	return 0;
}	


