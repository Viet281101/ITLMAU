/* Il s agit de prendre une image et de la modifier */

#include "ima.h"
#include <limits.h>


void vert(Image *im){
  GLubyte *crt,val1,val2;
  int i, nb_pixels;
  nb_pixels = im->sizeX * im->sizeY;
  val1=0;
  val2=255;
  for (crt=im->data,i=0;i<nb_pixels;i++){
    *crt++=val1;
    *crt++=val2;
    *crt++=val1;
  }
}

/*
void vert_moy(Image *im);

void vert_uniforme(Image *im);

void rouge_origin(Image *im);

void gris_uniforme(Image *im);

void swap_green_red(Image *im);
*/

