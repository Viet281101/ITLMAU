/*!\file linkedlist.h
 * \brief entête d'une bibliothèque de gestion d'une liste simplement chaînée d'entiers.
 * \author Revekka KYRIAKOGLOU, kyriakoglou@up8.edu
 * \author Farès BELHADJ, amsi@up8.edu
 * \date October 17 2022
 */
#ifndef LINKEDLIST_H
#  define LINKEDLIST_H

#  include <stdio.h>
#  include <stdlib.h>
#  include <assert.h>

#  ifdef __cplusplus
extern "C" {
#  endif

  /*!\brief le type de données pour un noeud de liste chaînée, issu de
   * la structure de donnée \ref llnode.
   *
   * \ref llnode
   */
  typedef struct llnode llnode_t;

  /*!\brief le type de données pour une liste chaînée, issu de
   * la structure de donnée \ref linkedlist.
   *
   * \ref llnode
   */
  typedef struct linkedlist linkedlist_t;

  /*!\brief la structure de donnée stockant un noeud de liste chaînée
   * : la donnée (ici un int) et le pointeur vers le noeud suivant.
   */  
  struct llnode {
    /*! donnée stockée dans le noeud */
    int data;
    /*! pointeur vers le successeur */
    struct llnode * next; 
  };
  
  /*!\brief la structure de donnée stockant une "liste chaînée". Afin
   * d'améliorer les performances d'insertion au début et à la fin
   * d'une liste, nous considérons ici qu'il est préférable d'avoir un
   * pointeur vers le début de la liste chaînée (\a ie. adresse du
   * premier noeud s'il existe, NULL sinon) ainsi qu'un pointeur vers
   * le dernier pointeur de la liste pour pouvoir ajouter directement
   * à la fin. Ce second pointeur (de pointeur) pointe vers l'adresse
   * du premier quand la liste est vide.
   */  
  struct linkedlist {
    /*! pointeur vers le début de la liste chaînée (le premier noeud
     * s'il existe, sinon NULL). */
    llnode_t * head;
    /*! pointeur vers le dernier pointeur de la liste pour pouvoir
     * ajouter directement à la fin. Ce pointeur contient l'adresse de
     * \a head quand ce dernier est NULL (\a ie. liste vide). */
    llnode_t ** tail; 
  };
  /*!\brief créé un nouveau noeud de liste chaînée en l'allouant
   * (malloc) une structure \ref llnode et en y stockant \a data et
   * NULL comme élément suivant.
   *
   * A terme, cette fonction peut n'avoir qu'un usage en interne (au
   * sein de linkedlist.c) et pourra donc être déclarée "static" dans
   * le fichier \ref linkedlist.c
   *
   * \param data élément (ici donnée entière) contenu dans le noeud.
   * \return le pointeur vers le nouveau \ref llnode alloué et initialisé.
   */
  extern llnode_t *     ll_new_node(int data); 
  /*!\brief insère (chaîne) un nouveau noeud \a new_node dans une
   * liste chaînée exactement à la position \a pos contenant l'adresse
   * d'un des pointeurs de noeud de la liste.
   *
   * A terme, cette fonction peut n'avoir qu'un usage en interne (au
   * sein de linkedlist.c) et pourra donc être déclarée "static" dans
   * le fichier \ref linkedlist.c
   *
   * \param pos adresse d'un pointeur de noeud à partir duquel le
   * nouveau noeud est inséré et chaîné au reste de la liste.
   *
   * \param new_node le pointeur du noeud (unique) à insérer dans la
   * liste.
   *
   * \return l'adresse du pointeur "suivant" (champ \a next de la
   * structure \ref llnode) du noeud inséré.
   */
  extern llnode_t **    ll_insert_node(llnode_t ** pos, llnode_t * new_node);
  /*!\brief affiche tous les éléments de la liste chaînée en partant
   * du pointeur de noeud \a list. A partir de ce pointeur, tous les
   * noeuds sont itérativement parcourus afin d'afficher l'élément (le
   * champ \a data de type int de la structure \ref llnode) qui y est
   * stocké.
   *
   * A terme, cette fonction peut n'avoir qu'un usage en interne (au
   * sein de linkedlist.c) et pourra donc être déclarée "static" dans
   * le fichier \ref linkedlist.c
   *
   * \param list adresse de noeud à partir duquel l'affichage se fait.
   */
  extern void           ll_print_from(llnode_t * list);
  /*!\brief efface, en désallouant, tous les éléments de la liste
   * chaînée en partant de l'adresse de pointeur de noeud \a plist. A
   * partir de ce pointeur, tous les noeuds sont itérativement
   * parcourus afin d'être désalloués. Le pointeur de noeud initial
   * (\a ie. *plist) est finalement mis à NULL par le biais de l'adresse
   * de pointeur de noeud \a plist.
   *
   * A terme, cette fonction peut n'avoir qu'un usage en interne (au
   * sein de linkedlist.c) et pourra donc être déclarée "static" dans
   * le fichier \ref linkedlist.c
   *
   * \param plist adresse de pointeur de noeud à partir duquel
   * l'effacement se fait.
   */
  extern void           ll_clear_from(llnode_t ** plist);
  /*!\brief créé une novelle liste chaînée de la strucutre \ref linkedlist en l'allouant
   * (malloc) et en l'initialisant à vide.
   *
   * Le pointeur de début de liste (\a ie. le champ head de la
   * structure \ref linkedlist) est mis à NULL et le pointeur de
   * pointeur de fin (\a ie. le champ tail de la structure \ref
   * linkedlist) est placé sur l'adresse du pointeur de début.
   *
   * \return la nouvelle liste chaînée de type \ref linkedlist
   * allouée.
   */
  extern linkedlist_t * ll_new(void); 
  /*!\brief insère un nouvel élément, contenant \a data, à la fin de
   *  la liste chaînée passée en paramètre. Par "fin de la liste" nous
   *  entendons : à partir du champ \a tail de la structure \ref
   *  linkedlist, soit dans le conteneur pointé par \a tail (\a ie. \a
   *  *tail) qui est censé toujours contenir la valeur NULL.
   *
   * \param llptr pointeur de liste chaînée de type \ref linkedlist.
   *
   * \param data est la donnée (de type int) à insérer ; un nouveau
   * noeud est créé pour l'y stocker.
   *
   * \see ll_new_node
   * \see ll_insert_node
   */
  extern void           ll_push_back(linkedlist_t * llptr, int data);
  /*!\brief insère un nouvel élément, contenant \a data, au début
   * (\a ie. en utilisant le champ \a head de la structure \ref
   * linkedlist) de la liste chaînée passée en paramètre.
   *
   * \param llptr pointeur de liste chaînée de type \ref linkedlist.
   *
   * \param data est la donnée (de type int) à insérer ; un nouveau
   * noeud est créé pour l'y stocker.
   *
   * \see ll_new_node
   * \see ll_insert_node
   */
  extern void           ll_push_front(linkedlist_t * llptr, int data);
  /*!\brief affiche tous les éléments de la liste chaînée de type \ref
   * linkedlist.
   *
   * Utilise la fonction \ref ll_print_from en lui passant le pointeur
   * du début (\a ie. champ \a head de la structure \ref linkedlist)
   * pour afficher tous les éléments de la liste.
   *
   * \param llptr adresse de la liste chaînée à afficher.
   * \see llprint_from
   */
  extern void           ll_print(linkedlist_t * llptr);
  /*!\brief efface, en désallouant, tous les éléments de la liste
   * chaînée de type \ref linkedlist en partant du début (\a ie. champ
   * \a head de la structure). Les champs de la strucutre sont
   * réinitialisés afin que la fin de liste repointe sur le début de
   * celle-ci qui sera NULL.
   *
   * Cette fonction utilise \ref ll_clear_from en lui passant
   * l'adresse du début de la liste chaînée.
   *
   * \param llptr pointeur vers la liste chaînée de type \ref
   * linkedlist à effacer.
   *
   * \see ll_clear_from
   */
  extern void           ll_clear(linkedlist_t * llptr);
  /*!\brief désalloue l'ensemble de la liste chaînée de type \ref
   * linkedlist en passant son pointeur de pointeur. La liste est
   * effacée par le biais de \ref ll_clear et le pointeur vers le
   * conteneur de la liste est utilisé (\a ie. en le déréférençant via
   * *pllptr) pour désalouer la \ref linkedlist et mettre le pointeur
   * vers cette dernière à NULL.
   *
   * \param pllptr adresse du pointeur vers la liste chaînée de type
   * \ref linkedlist à supprimer.
   *
   * \see ll_clear_from
   */
  extern void           ll_delete(linkedlist_t ** pllptr);

#  ifdef __cplusplus
}
#  endif

#endif /* du ifndef LINKEDLIST_H */

