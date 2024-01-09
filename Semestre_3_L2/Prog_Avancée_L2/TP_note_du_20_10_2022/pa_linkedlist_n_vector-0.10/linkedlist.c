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

int ll_size(ll_node_t* l){
  int i = 0;
  while (l != NULL){
    i++;
    l = l -> next; // et non pas juste l -> next
  }
  return i;
}

int ll_empty (linkedlist_t *llptr){
  if (llptr != NULL) return 0; // return (llptr == NULL);
  return 1;
}

void ll_erase (linkedlist_t *llptr, llnode_t **pos){
  if (llptr == NULL)
    return;
  llnode_t * n = llptr;
  if (*pos == 0){
    llptr = n -> head;
    free(n);
    return;
  }
  for(int i = 0; n!=NULL && i < *pos - 1; i++){
    n = n->next;
  }
  if (n == NULL || n->next == NULL)
    return;
  llnode_t * next = n->next->next;
  free(n->next);
  n->next = next;
}

int ll_pop_back (linkedlist_t *llptr){
  llptr->head = ll_insert_node(llptr->head, ll_new_node(data));
}

int ll_pop_front (linkedlist_t *llptr){
  if(llptr->tail != NULL)
    ll_insert_node(&(llptr->tail), ll_new_node(data));
  else
    llptr->head = ll_insert_node(&(llptr->tail), ll_new_node(data));
}

