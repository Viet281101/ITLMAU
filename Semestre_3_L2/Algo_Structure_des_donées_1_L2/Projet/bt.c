/*
 * Farès Belhadj
 * le 14/11/2022
 *
 * Arbre binaire de recherche (sans équilibrage) appliqué au stockage
 * d'entiers (version non-générique)
 *
 * La fonction print génère un graphe pour graphViz
 *
 * Pour compiler et exécuter :
 * gcc -Wall -Wextra bt.c -o bt && ./bt > g.dot && dot -Tpdf g.dot -o g.pdf && open g.pdf
 *
 * sous linux remplacer "open" par "evince" ou autre binaire qui lit du pdf
 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

typedef int element_t;
typedef struct bt_node bt_node_t;
struct bt_node {
  element_t data;
  struct bt_node * l_child;
  struct bt_node * r_child;
};

bt_node_t * bt_new_tree(element_t elem, bt_node_t * l_child, bt_node_t * r_child) {
  bt_node_t * tree = malloc(sizeof *tree);
  assert(tree);
  tree->data = elem;
  tree->l_child = l_child;
  tree->r_child = r_child;
  return tree;
}

bt_node_t * bt_new_node(element_t elem) {
  return bt_new_tree(elem, NULL, NULL);
}

bt_node_t * bt_insert_node(bt_node_t ** pos, bt_node_t * new_node) {
  bt_node_t * previous = *pos;
  *pos = new_node;
  if(previous != NULL) {
    if(previous->data < new_node->data)
      new_node ->l_child = previous;
    else
      new_node ->r_child = previous;
  }
  return new_node; 
}

bt_node_t ** bt_find_ordered_position(bt_node_t ** ptree, element_t elem, int * pfound) {
  if(*ptree == NULL) return ptree;
  if(elem > (*ptree)->data)
    return bt_find_ordered_position(&((*ptree)->r_child), elem, pfound);
  if(elem == (*ptree)->data)
    *pfound = 1;
  return bt_find_ordered_position(&((*ptree)->l_child), elem, pfound);
}

/* Version sans possibilité de savoir si l'élément est déjà dans l'arbre  */
/* bt_node_t ** bt_find_ordered_position(bt_node_t ** ptree, element_t elem) { */
/*   if(*ptree == NULL) */
/*     return ptree; */
/*   if(elem < (*ptree)->data) */
/*     return bt_find_ordered_position(&((*ptree)->l_child), elem); */
/*   return bt_find_ordered_position(&((*ptree)->r_child), elem); /\* else *\/ */
/* } */

void bt_infix_print(bt_node_t * tree) {
  if (tree == NULL)
    return;

  if(tree->l_child) {
    printf("\t%d -> %d [color=red]\n", tree->data, tree->l_child->data);
    bt_infix_print(tree->l_child);
  }
  if(tree->r_child) {
    printf("\t%d -> %d [color=black]\n", tree->data, tree->r_child->data);
    bt_infix_print(tree->r_child);
  }
}

/* Exemple d’usage */
int main(void) {
  bt_node_t * tree = NULL;
  srand(time(NULL)); /* epoch */
  for(int i = 0; i < 1000; ++i) {
    int found = 0;
    element_t r = rand() % 10;
    bt_node_t ** pos;
    pos = bt_find_ordered_position(&tree, r, &found);
    if(!found)
      bt_insert_node(pos, bt_new_node(r));
  }
  printf("digraph G {\n");
  bt_infix_print(tree);
  printf("}\n");
  return 0;
}

