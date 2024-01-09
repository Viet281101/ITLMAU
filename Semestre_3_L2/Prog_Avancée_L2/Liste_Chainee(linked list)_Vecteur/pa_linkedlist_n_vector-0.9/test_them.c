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

/*!\brief fonction réalisant des tests d'utilisation de la
 * bibliothèque linkedlist.
 */
static void test_linkedlist(void);
/*!\brief fonction réalisant des tests d'utilisation de la
 * bibliothèque vector.
 */
static void test_vector(void);
/*!\brief fonction utilisant le parcours, élément par élément, d'un
 * vecteur afin d'afficher ses éléments.
 *
 * \param v le pointeur vers le vecteur à parcourir et afficher.
 */
static void manually_print_vector(vector_t * v);

/*!\brief lancement des deux tests.
 */
int main(void) {
  test_linkedlist();
  test_vector();
  return 0;
}

void test_linkedlist(void) {
  int i;
  linkedlist_t * ll = ll_new();
  /* ajouts à la fin */
  ll_push_front(ll, -1);
  ll_push_back(ll, 1);
  ll_push_back(ll, 2);
  ll_push_back(ll, 3);
  ll_push_back(ll, 4);
  /* ajout au début */
  ll_push_front(ll, 0);
  /* autres ajouts à la fin */
  for(i = 10; i < 21; ++i)
    ll_push_back(ll, i);
  printf("\nAffichage de la liste chaînée par le biais de la fonction de la bibliothèque :\n");
  ll_print(ll);
  ll_delete(&ll);
}

void test_vector(void) {
  int i;
  vector_t * v = vector_new();
  for(i = 0; i < 100; ++i)
    vector_push_back(v, (rand() % 100));
  printf("\nAffichage du vecteur par le biais de la fonction de la bibliothèque :\n");
  vector_print(v);
  printf("\nAffichage du vecteur par le biais d'une fonction le parcourant élément par élément :\n");
  manually_print_vector(v);
  vector_delete(&v);
}

void manually_print_vector(vector_t * v) {
  int i;
  for(i = 0; i < vector_size(v); ++i)
    printf("%d ", vector_at(v, i));
  printf("\n");
}
