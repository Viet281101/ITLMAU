/*!\file test_them.cpp
 * \brief dernier VS de la saisons : l'arbre binaire "fait maison" en
 * C, versus l'arbre binaire de la STL/C++ représenté par le conteneur
 * set.
 * \author Farès BELHADJ, amsi@up8.edu
 * \date December 12 2022
 * \see bt.h
 */
#include <bt.h>
#include <my_timer.h>
#include <iostream>

/*!\brief nombre d'éléments utilisés pour cette expérience.
 */
#define N (1 << 21)

/*!\brief fonction réalisant des tests d'utilisation de la
 * bibliothèque bt (home-made binary tree).
 */
static void test_bt(void);

/*!\brief fonction devant réaliser les mêmes tests que \a test_bt mais
 * en utilisant le conteneur set de la STL.
 *
 * \todo écrire le reste du corps de la fonction.
 */
static void test_set(void);

/*!\brief lancement des deux fonctions de tests.
 */
int main(void) {
  test_bt();
  test_set();
  return 0;
}

void test_bt(void) {
  int n = 0;
  bt_node_t * tree = NULL, ** pos;
  /* on utilise la même graine (seed) de suite pseudo-aléatoire */
  srand(42);
  initTimer();
  for(int i = 0; i < N; ++i) {
    /* on génère une donnée random */
    int data = (int)(N * (rand() / (RAND_MAX + 1.0))), found = 0;
    pos = bt_find_ordered_position(&tree, data, &found);
    if(!found) {
      bt_insert_node(pos, bt_new_node(data));
      ++n;
    }
  }
  double el = getElapsedTime();
  std::cout << "Home-Made Binary Tree : Le temps passé en insertion ordonnée de " << n << " éléments est de : " << el << " secondes\n";
  bt_free(&tree);
}

void test_set(void) {
  // TODO ici : créer le set
  /* on utilise la même graine (seed) de suite pseudo-aléatoire */
  srand(42);
  initTimer();
  for(int i = 0; i < N; ++i) {
    /* on génère une donnée random */
    int data = (int)(N * (rand() / (RAND_MAX + 1.0)));
    // TODO ici : insérer la donnée dans le set
    // de manière à ce qu'elle soit ordonnée
    (void)data;
  }
  double el = getElapsedTime();
  // TODO modifiez la ligne ci-après pour que le nombre d'éléments corresponde à la réalité
  std::cout << "Le set de la STL : Le temps passé en insertion ordonnée de " << N << " éléments est de : " << el << " secondes\n";
  // TODO : encore de choses à faire ?
}

