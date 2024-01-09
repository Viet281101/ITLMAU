#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "my_timer.h"
#include "my_strcpy.h"

/*
 * remplit le tableau pointé par str de texte pseudo-aléatoire. Elle
 * inscrit (len - 1) éléments puis ajoute le '\0'.
 */
static void fill_with_text(char * str, int len);

int main(void) {
  const int n = 100000;
  /* allouer la source et destinations */
  char * src = NULL, * dst01 = NULL, * dst02 = NULL, * dst03 = NULL;
  src   = malloc(n * sizeof *src);
  dst01 = malloc(n * sizeof *dst01);
  dst02 = malloc(n * sizeof *dst02);
  dst03 = malloc(n * sizeof *dst03);
  assert(src && dst01 && dst02 && dst03);
  /* remplissage de src avec une longue chaîne */
  srand(42);
  fill_with_text(src, n);

  
  /* test de performance de my_strcpy_01 */
  initTimer();
  my_strcpy_01(dst01, src);
  fprintf(stderr, "Temps pour copie d'une chaîne de %d catactères avec la fonction my_strcpy_01 : %f secondes\n", n, getElapsedTime());
  if(strcmp(src, dst01) == 0)
    fprintf(stderr, "Copie effectuée avec succès\n\n");
  else
    fprintf(stderr, "Échec de copie\n\n");

  

  /* test de performance de my_strcpy_02 */
  initTimer();
  my_strcpy_02(dst02, src);
  fprintf(stderr, "Temps pour copie d'une chaîne de %d catactères avec la fonction my_strcpy_02 : %f secondes\n", n, getElapsedTime());
  if(strcmp(src, dst02) == 0)
    fprintf(stderr, "Copie effectuée avec succès\n\n");
  else
    fprintf(stderr, "Échec de copie\n\n");

  printf("\n-------------------------------------------\n");  

  /* test de performance de my_strcpy_03 */
  initTimer();
  my_strcpy_03(dst03, src);
  fprintf(stderr, "Temps pour copie d'une chaîne de %d catactères avec la fonction my_strcpy_03 : %f secondes\n", n, getElapsedTime());
  if(strcmp(src, dst03) == 0)
    fprintf(stderr, "Copie effectuée avec succès\n\n");
  else
    fprintf(stderr, "Échec de copie\n\n");


  /* libération de la mémoire */
  free( src );
  free(dst01);
  free(dst02);
  free(dst03);

  return 0;
}


void fill_with_text(char * str, int len) {
  int i;
  for(i = 0; i < len - 1; ++i) {
    int r = rand() & 0xFF;
    if(r < 10)
      str[i] = ' ';
    else
      str[i] = (r < 132 ? 'a' : 'A') + (r % 26);
  }
  str[i] = '\0';
}


