/*!\file DrawLineInBmp.cpp
 *
 * \brief dessin d'un segement de droite en mémoire et sauvegarde dans un fichier BMP.
 *
 * \author Farès Belhadj amsi@up8.edu
 * \date March 02, 2020 -- modifyed on October 27, 2020
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h> /* pour memset */
#include <math.h>
#include "images_io.h"

#define W 80
#define H 80
#define M_PI 3.14159265358979323846

static void drawLine(unsigned char * image, int w, int h, int x0, int y0, int x1, int y1, unsigned char color) {
  float y = 0.0f, pente;
  int u = x1 - x0, v = y1 - y0;
    
  if (abs(u) > abs(v)){ /*octan 1, 4, 5, 8*/

    pente = v / (float)abs(u);

    int pas = u < 0 ? -1 : 1;
    int borne = u + pas;

    for (int x = 0; x != borne; x+=pas) {
      int xp = x + x0;
      int yp = y0 + ((int)(y + 0.5f));
      image[(y0 + ((int)(y + 0.5f))) * w + x + x0] = color;
      y += pente;
    }
  }
  else{ /*octan 2, 3, 6, 7*/

    float x = 0.0f, ipente;
    int pas = v < 0 ? -1 : 1;
    int borne = v + pas;
    ipente = u / (float)abs(v);
    for(int y = 0; y != borne; y += pas){
      image[(y0 + y) * w + (int)(x + 0.5f) + x0] = color;
      x += ipente;
    }
  }
}

// //// Example:
// void line(unsigned char * image, int w, int x0, int y0, int x1, int y1, unsigned char color) {
//  int u = x1 - x0;
//  int v = y1 - y0;
//  float a = v / (float)u;
//  if(a <= 1.0f) {
//    float y = 0.0f;
//    for(int x = 0; x <= u; ++x) {
//       image[((int)y) * w + x] =color;
//       y += a;
//    }
//  }
// }


int main(void) {
  /* on part sur une image 8 bits / 256 niveaux de gris */
  unsigned char image[H * W];
  /* on met tous les pixels à zéro */
  memset(image, 0, sizeof image);
  /* on dessine une droite de (5, 10) à (70, 50) 
   * la couleur utilisée est le blanc (255)
   */
  // drawLine(image, W, 5, 10, 50, 50, 255);
  // drawLine(image, W, 20, 10, 50, 50, 255);

  // Ex1:
  drawLine(image, W, H, 75, 10, 0, 50, 255);
  // Ex2:
  drawLine(image, W, H, 10, 10, 20, 50, 255);
  // Ex3:
  drawLine(image, W, H, -10, -10, 120, 150, 255);

  // // Ex4:
  // for (float angle = 0.0f, rayon = 20.0f; angle < 2.0f * M_PI; angle += 0.5f)
  //   drawLine(image, W, W/2, H/2, W/2 + rayon * cos(angle), H/2 + rayon * sin(angle), 255);

  imageSaveBMP("resu.bmp", image, W, H, 1, 8);
  return EXIT_SUCCESS;
}

/*
 * Exercice 1 : essayez de dessiner le segment (75, 10, 0, 50, 255),
 * ça ne fonctionne pas. Corriger drawLine.
 *
 * Exercice 2 : essayez de dessiner le segment (10, 10, 20, 50, 255),
 * ça ne fonctionne pas. Corriger drawLine.
 * 
 * Exercice 3 : essayez de dessiner le segment (-10, -10, 120, 150,
 * 255), ça ne fonctionne pas. Corriger drawLine.
 *
 * Exercice 4 : dessiner (si ça marche) toutes les positions d'une
 * aiguille trotteuse en variant les intensités de gris. Vous pouvez
 * utiliser cos et sin (inclure math.h) tels que :
 *
 * for (float angle = 0.0f, rayon = 20.0f; angle < 2.0f * M_PI; angle += 0.5f)
 *    drawLine(image, W, W/2, H/2, W/2 + rayon * cos(angle), H/2 + rayon * sin(angle), rand()%256);
 * 
 * Exercice 5 : l'équation d'un cercle est donnée par 
 * 
 * rayon * rayon = (x - x0) * (x - x0) + (y - y0) * (y - y0);
 * écrire drawCircle.
*/
