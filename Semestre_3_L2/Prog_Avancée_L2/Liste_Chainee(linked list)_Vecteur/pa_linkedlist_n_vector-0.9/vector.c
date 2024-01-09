/*!\file vector.c
 * \brief fonctions d'une bibliothèque de gestion de vecteurs (tableaux dynamiques extensibles) d'entiers.
 * \author Revekka KYRIAKOGLOU, kyriakoglou@up8.edu
 * \author Farès BELHADJ, amsi@up8.edu
 * \date October 17 2022
 */

#include <vector.h>

vector_t * vector_new(void) {
  vector_t * vec = malloc(1 * sizeof *vec);
  assert(vec);
  vec->size = 0;
  vec->max_size = 1024;
  vec->data = malloc(vec->max_size * sizeof *(vec->data));
  assert(vec->data);
  return vec;
}

void vector_push_back(vector_t * vec, int data) {
  if(vec->size == vec->max_size) {
    void * ptr;
    vec->max_size = vec->max_size * 2;
    ptr = realloc(vec->data, vec->max_size * sizeof *(vec->data));
    if(ptr == NULL) {
      free(vec->data);
      free(vec);
      assert(ptr);
    } else
      vec->data = ptr;
  }
  vec->data[vec->size] = data;
  ++(vec->size);
}

int vector_size(vector_t * vec) {
  return vec->size;
}

int vector_empty(vector_t * vec) {
  return !(vec->size);
}

int vector_at(vector_t * vec, int pos) {
  assert(pos < vec->size);
  return vec->data[pos];
}

void vector_print(vector_t * vec) {
  int i;
  for(i = 0; i < (int)vec->size; ++i)
    printf("%d ", vec->data[i]);
  printf("\n");
}

void vector_delete(vector_t ** pvec) {
  free((*pvec)->data);
  free(*pvec);
  *pvec = NULL;
}
