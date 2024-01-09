/*!\file vector.h
 * \brief entête d'une bibliothèque de gestion de vecteurs (tableaux dynamiques extensibles) d'entiers.
 * \author Revekka KYRIAKOGLOU, kyriakoglou@up8.edu
 * \author Farès BELHADJ, amsi@up8.edu
 * \date October 17 2022
 */

#ifndef VECTOR_H
#  define VECTOR_H

#  include <stdio.h>
#  include <stdlib.h>
#  include <assert.h>

#  ifdef __cplusplus
extern "C" {
#  endif

  /*!\brief le type de données pour un vector, issu de la structure de
   * donnée \ref vector.
   *
   * \ref vector
   */
  typedef struct vector vector_t;

  /*!\brief la structure de donnée stockant l'ensemble des
   * informations nécessaires au vector.
   */
  struct vector {
    /*! donne le nombre d'élements stockés dans le vector. */
    size_t size;
    /*! max_size est le nombre (actuellement) maximal d'éléments à stocker */
    size_t max_size;
    /*! data est le pointeur vers le tableau dynamique d'éléments (ici des int) à stocker. */
    int * data;
  };
  
  /*!\brief créé un vector en allouant (malloc) une structure \ref
   * vector de \a size 0 et \a max_size égal à 1024. Pour le champ \a
   * data, \a max_size éléments (ici des int) sont alloués.
   *
   * La fonction retourne le pointeur vers la nouvelle structure ainsi
   * paramétrée. Ce pointeur de \ref vector doit être libéré à l'aide
   * de \ref vector_delete.
   *
   * \return le pointeur vers le nouveau \ref vector alloué et initialisé.
   * \see vector_delete
   */
  extern vector_t * vector_new(void);
  /*!\brief ajoute un élément (le int \a data) à la fin du \ref
   * vector pointé par \a vec.
   *
   * Si le vecteur n'a plus assez d'espace de stackage (\a size == \a
   * max_size), \a max_size est doublée et \a data est réallouée en
   * conséquence.
   *
   * \param vec le pointeur vers le vecteur dans lequel le "push back"
   * est effectué.
   *
   * \param data l'élément (int) à ajouter à la fin du vecteur.
   */
  extern void       vector_push_back(vector_t * vec, int data);
  /*!\brief donne la taille (nombre d'éléments stockés) du \ref vector
   * pointé par \a vec.
   *
   * \param vec le pointeur vers le vecteur.
   * \return le nombre d'éléments stockés dans le vecteur.
   */
  extern int        vector_size(vector_t * vec);
  /*!\brief indique si le \ref vector pointé par \a vec est vide.
   *
   * \param vec le pointeur vers le vecteur.  
   *
   * \return vrai (différent * de zéro) si le vecteur est vide, faux
   * (zéro) sinon.
   */
  extern int        vector_empty(vector_t * vec);
  /*!\brief retourne l'élément à l'indice \a pos dans le \ref vector
   * pointé par \a vec.
   *
   * \param vec le pointeur vers le vecteur.  
   * \param pos l'indice de l'élément à récupérer dans le vecteur.  
   *
   * \return retourne l'élément à l'indice \a pos.
   */
  extern int        vector_at(vector_t * vec, int pos);
  /*!\brief affiche (à l'aide de \a printf) l'ensemble des éléments
   * stockés dans le \ref vector pointé par \a vec.
   *
   * \param vec le pointeur vers le vecteur à afficher.
   */
  extern void       vector_print(vector_t * vec);
  /*!\brief désalloue (à l'aide de \a free) l'ensemble des éléments
   * stockés dans le \ref vector pointé par \a *pvec puis désalloue le
   * pointeur lui-même. Enfin \a *pvec reçoit NULL.
   *
   * \param pvec pointeur vers le pointeur vers le vecteur à libérer
   * (désallouer).
   */
  extern void       vector_delete(vector_t ** pvec);
  
#  ifdef __cplusplus
}
#  endif

#endif /* du ifndef VECTOR_H */
