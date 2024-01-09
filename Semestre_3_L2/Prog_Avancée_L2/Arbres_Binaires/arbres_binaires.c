
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

typedef int element_t;
typedef struct bt_node bt_node_t;

struct bt_node
{
    element_t data;
    struct bt_node *childR;
    struct bt_node *childL;
};


bt_node_t * newTree(element_t elem, bt_node_t * childG, bt_node_t * childD){
    bt_node_t * tree = malloc(sizeof * tree);
    assert(tree);
    if (tree == NULL) return NULL;
    tree -> data = elem;
    tree -> childL = childG;
    tree -> childR = childD;
    return tree;
}


/* ************ PRINT L'ARBRES *********** */ 
void bt_prefix_print(bt_node_t * tree){
    if (tree == NULL) return;
    printf("%d\t", tree -> data);
    bt_prefix_print(tree -> childL);
    bt_prefix_print(tree -> childR);
}

void bt_suffix_print(bt_node_t* tree){
    if (tree == NULL) return;
    bt_suffix_print(tree -> childL);
    bt_suffix_print(tree -> childR);
    printf("%d\t", tree -> data);
}

void bt_infix_print(bt_node_t* tree){
    if (tree == NULL) return;
    bt_infix_print(tree -> childL);
    printf("%d\t", tree -> data);
    bt_infix_print(tree -> childR);
}

void reset() {
    printf("\033[0m"); // Normal color text
}

void bt_print_digraph(bt_node_t* tree){
    if (tree == NULL) return;
    if (tree -> childL){
        printf("\033[1;31m"); // Red color text
        printf("\t%d -> %d\n", tree -> data, tree -> childL -> data);
        reset();
        bt_print_digraph(tree -> childL);
    }
    if (tree -> childR){
        printf("\033[0;36m"); // Cyan color text
        printf("\t%d -> %d\n", tree -> data, tree -> childR -> data);
        reset();
        bt_print_digraph(tree -> childR);
    }
}

/* ************************************* */ 

bt_node_t * bt_insert_node ( bt_node_t ** pos , bt_node_t * tree ) {
    bt_node_t * previous = * pos ;
    * pos = tree ;
    if ( previous != NULL ) {
        if ( previous -> data < tree -> data ) tree -> childL = previous ;
        else tree -> childR = previous ;
    }
    return tree ;
}

bt_node_t ** bt_find_ordered_position ( bt_node_t ** ptree , element_t elem ) {
    if (* ptree == NULL )return ptree ;
    if ( elem < (* ptree ) -> data )return bt_find_ordered_position (&((* ptree ) -> childL ) , elem );
    return bt_find_ordered_position (&((* ptree ) -> childR ) , elem ); /* else */
}

bt_node_t * bt_new_node (element_t elem){
    return newTree (elem, NULL, NULL);
}


/* ******************** COMPTER DANS L'ARBRES ************** */ 
int bt_nb_leaves(bt_node_t* tree){
    if (tree == NULL) return 0;
    if(tree -> childL == NULL && tree -> childR == NULL)
        return 1;
    else return (bt_nb_leaves(tree -> childL) + bt_nb_leaves(tree -> childR));
}

int maxHeight(int a, int b){
    // if (a > b){return a;}else{return b;}
    return ((a > b) ? a : b);
}

int bt_height(bt_node_t* tree){
    if (tree == NULL) return -1;
    return (1 + maxHeight(bt_height(tree -> childL), bt_height(tree -> childR))); 
}
/* ********************************************************** */ 


bt_node_t * bt_copy_tree(bt_node_t* tree){
    if (tree == NULL) return NULL;
    return newTree(tree -> data, bt_copy_tree(tree -> childL), bt_copy_tree(tree -> childR));
}

void bt_free_tree(bt_node_t ** ptree){
    if ((*ptree) != NULL){
        bt_free_tree(&((*ptree) -> childL));
        bt_free_tree(&((*ptree) -> childR));
        free(*ptree);
        *ptree = NULL;
    }
}


int main(void)
{
    bt_node_t * tree = NULL;
    bt_node_t * a = newTree(8, newTree(6, NULL, NULL), newTree(5, newTree(4, NULL, NULL), newTree(3, NULL, NULL)));
    // bt_node_t * c = newTree(8, NULL, NULL);
    srand(time(NULL));

    printf("\nPrefix print: \n");
    bt_prefix_print(a);

    printf("\nSuffix print: \n");
    bt_suffix_print(a);

    printf("\nInfix print: \n");
    bt_infix_print(a);


    for (int i = 0; i < 100; ++i){
        int found = 0;
        element_t r = rand() % 150;
        bt_node_t ** pos;
        pos = bt_find_ordered_position(&tree, r);
        if (!found)
            bt_insert_node(pos, bt_new_node(r));
    }
    printf("\n\nPrint tree auto node: ");
    bt_infix_print(tree);
    printf("\n\ndigraph G{\n");
    bt_print_digraph(tree);
    printf("}\n");


    printf("\n\nLa nombre les feuilles dans l'arbre est : %d\n", bt_nb_leaves(a));
    printf("\nLa hauteur de l'arbre est : %d\n", bt_height(a));

    bt_node_t * b = bt_copy_tree(a);
    printf("\nPrint prefix le copy de l'arbre : \n");
    bt_prefix_print(b);

    printf("\nL'arbre apres free: \n");
    bt_free_tree(&a);
    bt_prefix_print(a);

    printf("\n");
    return 0;
}


