/*!\file linkedlist.c
 * \brief fonctions d'une bibliothèque de gestion d'une liste simplement chaînée d'entiers.
 * \author Revekka KYRIAKOGLOU, kyriakoglou@up8.edu
 * \author Farès BELHADJ, amsi@up8.edu
 * \date October 17 2022
 */
#include <linkedlist.h>

llnode_t * ll_new_node(int data) {
  llnode_t * n = malloc(1 * sizeof *n);
  assert(n);
  n->data = data;
  n->next = NULL;
  return n;
}

llnode_t ** ll_insert_node(llnode_t ** pos, llnode_t * new_node) {
  new_node->next = *pos;
  *pos = new_node;
  return &(new_node->next);
}

void ll_print_from(llnode_t * list) {
  while(list != NULL) {
    printf("%d ", list->data);
    list = list->next;
  }
  printf("\n");
}

void ll_clear_from(llnode_t ** plist) {
  llnode_t * ptr = *plist;
  while(ptr != NULL) {
    llnode_t * tofree = ptr;
    ptr = ptr->next;
    free(tofree);
  }
  *plist = NULL;
}

linkedlist_t * ll_new(void) {
  linkedlist_t * ll = calloc(1, sizeof *ll);
  ll->tail = &(ll->head);
  return ll;
}

void ll_push_back(linkedlist_t * llptr, int data) {
  llptr->tail = ll_insert_node(llptr->tail, ll_new_node(data));  
}

void ll_push_front(linkedlist_t * llptr, int data) {
  if(llptr->head != NULL)
    ll_insert_node(&(llptr->head), ll_new_node(data));
  else
    llptr->tail = ll_insert_node(&(llptr->head), ll_new_node(data));
}

void ll_print(linkedlist_t * llptr) {
  ll_print_from(llptr->head);
}

void ll_clear(linkedlist_t * llptr) {
  ll_clear_from( &(llptr->head) );
  llptr->tail = &(llptr->head);
}

void ll_delete(linkedlist_t ** pllptr) {
  ll_clear(*pllptr);
  free(*pllptr);
  *pllptr = NULL;
}

