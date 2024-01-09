#include <stdio.h> 
#include <stdlib.h>
#include <assert.h>

/* pour Bocal */
#include <GL/gl.h> 
#include <GL/glut.h>
#include <GL/freeglut.h>  

/* pour Mac */
// #include <GLUT/glut.h>


typedef struct {
    GLubyte red;
    GLubyte green;
    GLubyte blue;
    int frequency;
} Color;

struct Image {
    unsigned long sizeX;
    unsigned long sizeY;
    GLubyte *data;
};
typedef struct Image Image;
typedef unsigned short utab [3][3][3];

int ImageLoad_PPM(char *filename, Image *image);
void imagesave_PPM(char *filename, Image *image);
void upsidedown(Image *im);
void vert(Image *image);

void vert_uniform(Image *image);
void gris_uniform (Image *image);
void rouge_origin(Image *image);
void swap_green_red(Image *image);
void swap_blue_red(Image *image);



//// RLE ////
void sortColors (GLubyte* image, int width, int height, GLubyte* sortedColors);
void compressRLE(GLubyte* data, int size, GLubyte** compressedData, int* compressedSize);
void decompressRLE(GLubyte* compressedData, int compressedSize, GLubyte** decompressedData, int* decompressedSize);

void compressRLE2(GLubyte* data, int size, GLubyte** compressedData, int* compressedSize);
void decompressRLE2(GLubyte* compressedData, int compressedSize, GLubyte** decompressedData, int* decompressedSize);

//// C-LUT ////
void buildCLUT (GLubyte* image, int width, int height, Color** clut, int* clutSize);
void sortCLUT (Color* clut, int clutSize);
void reduceColors (GLubyte* image, int width, int height, Color* clut, int clutSize, int k);
