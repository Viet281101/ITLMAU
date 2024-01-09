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

int vector_find_ordered_pos(vector_t * vec, int data) {
  int i;
  for(i = 0; i < vec->size; ++i)
    if(data < vec->data[i])
      return i;
  return i;
}

void vector_insert(vector_t * vec, int pos, int data) {
  int i;
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
  for(i = vec->size; i > pos; --i)
    vec->data[i] = vec->data[i - 1];

  vec->data[pos] = data;
  ++vec->size;
}

int vector_is_ordered(vector_t * vec) {
  int i, n = vector_size(vec);
  for(i = 0; i < n - 1; ++i)
    if(vector_at(vec, i) > vector_at(vec, i + 1))
      return 0;
  return 1;
}
