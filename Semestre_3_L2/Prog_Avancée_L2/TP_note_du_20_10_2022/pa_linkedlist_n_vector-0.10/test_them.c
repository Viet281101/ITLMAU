/*!\file test_them.c
 * \brief tests de quelques fonctions des bibliothèques \a linkedlist et \a vector.
 * \author Revekka KYRIAKOGLOU, kyriakoglou@up8.edu
 * \author Farès BELHADJ, amsi@up8.edu
 * \date October 17 2022
 * \see linkedlist.h
 * \see vector.h
 */
#include <linkedlist.h>
#include <vector.h>
#include <my_timer.h>

/*!\brief nombre d'éléments utilisés pour cette expérience.
 */
#define N 100000

/*!\brief fonction réalisant des tests d'utilisation de la
 * bibliothèque linkedlist.
 */
static void test_linkedlist(void);

/*!\brief fonction réalisant des tests d'utilisation de la
 * bibliothèque vector.
 *
 * \todo (TODO TP noté) lire le corps de la fonction et réaliser tous
 * les TODO demandés. Une fois le travail terminé, vous pourrez faire
 * passer l'option de compilation de -O0 à -O2 (voire -O3) pour
 * apprécier la différence de performance dans ce cas là.
 */
static void test_vector(void);

/*!\brief trouve la position à partir de laquelle l'insertion d'un
 * élément contenant \a data se ferait en respectant l'ordre croissant
 * de la liste.
 *
 * Nous supposons que la liste chaînée est triée par ordre croissant.
 *
 * \param llptr la liste chaînée dans laquelle se ferait l'insertion.
 * \param data la donnée à insérer.
 *
 * \return la position à laquelle l'insertion se fera en respectant
 * l'ordre croissant de la liste.
 */
static llnode_t ** find_ordered_pos_in_ll(linkedlist_t * llptr, int data);

/*!\brief teste si les éléments de la liste chaînée sont bien placés
 * par ordre croissant.
 *
 * \param llptr la liste chaînée à tester.
 *
 * \return une valeur différente de zéro si les éléments de la liste
 * sont bien triés, zéro sinon.
 *
 * \todo (TODO TP noté) finir d'écrire le corps de cette fonction \ref
 * is_ll_ordered. Vous pouvez vous inspirez du principe de
 * fonctionnement de \ref is_vec_ordered .
 */
static int is_ll_ordered(linkedlist_t * llptr);

/*!\brief teste si les éléments successifs du vecteur sont bien placés
 * par ordre croissant.
 *
 * \param vec le vecteur à tester.
 *
 * \return une valeur différente de zéro si les éléments sont bien
 * triés, zéro sinon.
 */
static int is_vec_ordered(vector_t * vec);


/*!\brief lancement des deux tests.
 */
int main(void) {
  test_linkedlist();
  test_vector();
  return 0;
}

void test_linkedlist(void) {
  double el;
  int i, data;
  linkedlist_t * ll = ll_new();
  /* on utilise la même graine (seed) de suite pseudo-aléatoire */
  srand(42);
  initTimer();
  for(i = 0; i < N; ++i) {
    llnode_t ** pos;
    /* on génère une donnée random */
    data = rand() % N;
    /* on trouve la position potentielle de cette donnée dans la liste chaînée */
    pos = find_ordered_pos_in_ll(ll, data);
    /* on insère un nouveau noeud à partir de cette position */
    /* la fonction retourne l'adresse du next de ce nouveau noeud, on
     * le met dans pos */
    pos = ll_insert_node(pos, ll_new_node(data));
    /* on test si le nouveau noeud ajouté est porteur du tail, si oui
     * on met à jour le tail de la liste */
    if(*pos == NULL)
      ll->tail = pos;
  } 
  el = getElapsedTime();
  if(is_ll_ordered(ll)) {
    printf("La liste est bien ordonnée, le temps passé en insertion de %d éléments est de : %f secondes\n", N, el);
  } else {
    printf("La liste n'est pas ordonnée, le temps passé en insertion de %d éléments est de : %f secondes\n", N, el);
  }
 ll_delete(&ll);
}

void test_vector(void) {
  double el;
  int i, data, pos;
  vector_t * vec = vector_new();
  /* on utilise la même graine (seed) de suite pseudo-aléatoire */
  srand(42);
  initTimer();
  for(i = 0; i < N; ++i) {
    /* on génère une donnée random */
    data = rand() % N;
    /* on trouve la position potentielle de cette donnée dans le vecteur */
    /* TODO: proposez et utilisez une fonction qui trouve cette
     * position (c'est un indice entier qu'on cherche). Exemple : 
     * pos = find_ordered_pos_in_vec(vec, data);
     */
    pos = find_ordered_pos_in_vec(vec, data);
    // pos = i; /* cette ligne est fake, à supprimer donc */
    /* puis on insère un nouveau élément à partir de cette position à
     * l'aide d'une fonction de la bibliothèque vector qui manque à
     * l'appel. 
     * 
     * TODO : Cette fonction qu'on souhaite appeler avec
     * vector_insert(vec, pos, data) doit insérer l'élément data dans
     * le vecteur, à la position pos, tout en décalant les éventuels
     * éléments se trouvant à partir de pos. */
    vector_insert(vec, pos, data);

    /* pour l'instant on fait un push_back pour faire semblant, cette
     * ligne de push_back est évidemment à supprimer. */
    vector_push_back(vec, data);

  }
  el = getElapsedTime();
  if(is_vec_ordered(vec)) {
    printf("Le vecteur est bien ordonné, le temps passé en insertion de %d éléments est de : %f secondes\n", N, el);
  } else {
    printf("Le vecteur n'est pas ordonné, le temps passé en insertion de %d éléments est de : %f secondes\n", N, el);
  }
  vector_delete(&vec);
}

llnode_t ** find_ordered_pos_in_ll(linkedlist_t * llptr, int data) {
  llnode_t ** pos = &(llptr->head);
  while( *pos != NULL && (*pos)->data < data )
    pos = &((*pos)->next);
  return pos;
}

int is_ll_ordered(linkedlist_t * ll) {
  /* TODO, see documentation and complete */
  int i, n = ll_size(ll);
  for (i = 0; i < n - 1; ++i){
    if (find_ordered_pos_in_vec(ll, i) > find_ordered_pos_in_ll(ll, i + 1))
      return 0;
  }
  return 1; /* en attendant */
}

int is_vec_ordered(vector_t * vec) {
  int i, n = vector_size(vec);
  for(i = 0; i < n - 1; ++i)
    if(vector_at(vec, i) > vector_at(vec, i + 1))
      return 0;
  return 1;
}

