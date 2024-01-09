/*!\file bt.h
 * \brief bibliothèque de gestion de conteneur d'un ensemble ordonné
 * d'éléments uniques implémenté sous la forme d'un arbre binaire non
 * équilibré. Dans cette version non générique, seul le type int est
 * géré pour les éléments.
 * \author Farès BELHADJ, amsi@up8.edu
 * \date December 12 2022
 */

#ifndef BT_H
#define BT_H

#include <stdlib.h>
#include <assert.h>

#ifdef __cplusplus
extern "C" {
#endif

  /*!\brief le type et la structure de l'arbre binaire */
  typedef struct bt_node bt_node_t;
  struct bt_node {
    int data;
    struct bt_node * l_child;
    struct bt_node * r_child;
  };
  
  /*!\brief créé un nouveau noeud avec comme donnée data */
  static inline bt_node_t * bt_new_node(int data) {
    /* je mets un cast car je ne créé pas un fichier C */
    bt_node_t * node = (bt_node_t *)malloc(sizeof *node);
    assert(node);
    node->data = data;
    node->l_child = node->r_child = NULL;
    return node;
  }
  
  /*!\brief insère à une position donnée un nouveau noeud déjà créé */
  static inline bt_node_t * bt_insert_node(bt_node_t ** pos, bt_node_t * new_node) {
    bt_node_t * previous = *pos;
    *pos = new_node;
    if(previous != NULL) {
      if(previous->data < new_node ->data)
	new_node->l_child = previous;
      else
	new_node->r_child = previous;
    }
    return new_node;
  }
  
  /*!\brief recherche une position pour une donnée, de manière à ce que
   * l'arbre soit toujours ordonné. Si la donnée est déjà dans l'arbre
   * le contenu pointé par le paramètre \a found sera mis à 1 (mettre à
   * 0 avant appel). */
  static inline bt_node_t ** bt_find_ordered_position(bt_node_t ** ptree, int data, int * found) {
    if(*ptree == NULL)
      return ptree;
    if(data < (*ptree)->data)
      return bt_find_ordered_position(&((*ptree)->l_child), data, found);
    if(data > (*ptree)->data)
      return bt_find_ordered_position(&((*ptree)->r_child), data, found);
    *found = 1;
    return ptree;
  }
  
  /*!\brief libère l'arbre */
  static inline void bt_free(bt_node_t ** tree) {
    if(*tree == NULL)
      return;
    bt_free(&((*tree)->l_child));
    bt_free(&((*tree)->r_child));
    free(*tree);
    *tree = NULL;
  }

#ifdef __cplusplus
}
#endif

#endif
