/*!\file static_2d_array.c
 *
 * \brief parcours dynamique et optimal d'une image (ou tableau) "2D".
 *
 * \author Farès Belhadj amsi@up8.edu
 * \date September 21, 2021
 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/* écrire 21 en dur sur l'une des dimensions de l'image est problématique, 
 * cette écriture est rigide et ne permet pas de gérer des images de 
 * dimensions variables.
 */
static void dessinerCroix(char * ptr, int w, int h) {
  int x, y;
  for (y = 0; y < h; ++y)
    for (x = 0; x < w; ++x) {
      if (x == y || (w - 1) - x == y)
	ptr[y * w + x] = 'X';
      else
	ptr[y * w + x] = ' ';
    }
}

/* solution */
static void dessinerCarre(char * ptr, int w, int h) {
  int x, y;
  for (y = 0; y < h; ++y)
    for (x = 0; x < w; ++x) {
      if (x == 0 || x == (w - 1) || y == 0 || y == (h - 1))
	ptr[y * w + x] = 'X';
      else
	ptr[y * w + x] = ' ';
    }
}

static void afficher(char * ptr, int w, int h) {
  int x, y;
  for (y = 0; y < h; ++y) {
    for (x = 0; x < w; ++x) {
      printf("%c", ptr[y * w + x]);
    }
    printf("\n");
  }
}

static void afficher2(char * ptr, int w, int h) {
  int i;
  for (i = 0; i < w * h; ++i) {
    if((i % w) == 0)
      printf("\n");
    printf("%c", ptr[i]);
  }
}

int main(int argc, char ** argv) {
  int W = 11, H = 11;
  char * image = NULL;
  if(argc != 3) {
    fprintf(stderr, "usage: %s <largeur> <hauteur>\n", argv[0]);
    return 1;
  }
  W = atoi(argv[1]);
  H = atoi(argv[2]);
  assert(W > 0 && H > 0);
  image = malloc(W * H * sizeof *image);
  assert(image);
  dessinerCroix(image, W, H);
  afficher(image, W, H);
  dessinerCarre(image, W, H);
  afficher2(image, W, H);
  free(image);
  return EXIT_SUCCESS;
}
/*
 * Exercice : modifier la fonction afficher pour qu'elle ne soit plus "rigide" 
 * et faire que le parcours se fasse en une simple boucle de 0 à n - 1 où n = w * h.
 * Attention à ne pas oublier le saut de ligne à fin de chacune des lignes de l'image.
 */
