/*!\file static_2d_array.c
 *
 * \brief parcours dynamique et optimal d'une image (ou tableau) "2D".
 *
 * \author Farès Belhadj amsi@up8.edu
 * \date September 21, 2021
 */
#include <stdio.h>
#include <stdlib.h>

/* écrire 21 en dur sur l'une des dimensions de l'image est problématique, 
 * cette écriture est rigide et ne permet pas de gérer des images de 
 * dimensions variables.
 */
static void dessinerCroix(char ptr[][21], int w, int h) {
  int x, y;
  for (y = 0; y < h; ++y)
	for (x = 0; x < w; ++x) {
	  if (x == y || (w - 1) - x == y)
	ptr[y][x] = 'X';
	  else
	ptr[y][x] = ' ';
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

static void afficher(char ptr[][21], int w, int h) {
  int x, y;
  for (y = 0; y < h; ++y) {
	for (x = 0; x < w; ++x) {
		printf("%c", ptr[y][x]);
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

int main(void) {
	char image[21][21];
	dessinerCroix(image, 21, 21);
	afficher(image, 21, 21);
	dessinerCarre((char *)image, 21, 21);
	afficher2((char *)image, 21, 21);

	// getchar();
	// getchar();
	return EXIT_SUCCESS;
}
/*
 * Exercice : modifier la fonction afficher pour qu'elle ne soit plus "rigide" 
 * et faire que le parcours se fasse en une simple boucle de 0 à n - 1 où n = w * h.
 * Attention à ne pas oublier le saut de ligne à fin de chacune des lignes de l'image.
 */
