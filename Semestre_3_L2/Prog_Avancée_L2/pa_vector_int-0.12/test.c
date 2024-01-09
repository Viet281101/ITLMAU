/*!\file test.c
 * \brief tests de quelques fonctions de la bibliothèque et \a vector.
 * \author Revekka KYRIAKOGLOU, kyriakoglou@up8.edu
 * \author Farès BELHADJ, amsi@up8.edu
 * \date October 17 2022
 * \see vector.h
 */
#include <vector.h>
#include <my_timer.h>

/*!\brief nombre d'éléments utilisés pour cette expérience.
 */
#define N 30000

/*!\brief fonction réalisant des tests d'utilisation de la
 * bibliothèque vector.
 */
static void test_vector(void);

/*!\brief lancement du tests.
 */
int main(void) {
  test_vector();
  return 0;
}

void test_vector(void) {
  double el;
  int i, data, pos;
  vector_t * vec = vector_new();
  /* on utilise la même graine (seed) de suite pseudo-aléatoire */
  srand(42);
  initTimer();
  for(i = 0; i < N; ++i) {
    data = rand() % N;
    pos = vector_find_ordered_pos(vec, data);
    vector_insert(vec, pos, data);
  }
  el = getElapsedTime();
  if(vector_is_ordered(vec)) {
    printf("Le vecteur est bien ordonné, le temps passé en insertion de %d éléments est de : %f secondes\n", N, el);
  } else {
    printf("Le vecteur n'est pas ordonné, le temps passé en insertion de %d éléments est de : %f secondes\n", N, el);
  }
  vector_delete(&vec);
}
