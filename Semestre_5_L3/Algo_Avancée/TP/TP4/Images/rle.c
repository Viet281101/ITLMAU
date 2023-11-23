
#include "ima.h"


/*Écrire une fonction qui p ermet de trier les 3 couleurs d'une image : on sto ckera
tous les GLubyte de rouge, de vert et de bleu dans un grand tableau.*/
void sortColors (GLubyte* image, int width, int height, GLubyte* sortedColors) {
    int i, j, k;
    int nb_pixels = width * height;
    for (i = 0; i < nb_pixels; i++) {
        for (j = 0; j < 3; j++) {
        for (k = 0; k < 3; k++) {
            sortedColors[i * 9 + j * 3 + k] = image[i * 3 + j * width * 3 + k];
        }
        }
    }
    for (i = 0; i < nb_pixels; i++) {
        for (j = 0; j < 3; j++) {
        for (k = 0; k < 3; k++) {
            image[i * 3 + j * width * 3 + k] = sortedColors[i * 9 + j * 3 + k];
        }
        }
    }
}


/*Écrire une fonction qui p ermet de compresser un tableau de GLubyte selon le
princip e de l'algorithme RLE naïf.*/
void compressRLE (GLubyte* data, int size, GLubyte* compressedData) {
    int i, j, k;
    int nb_pixels = size / 3;
    int nb_pixels_compressed = 0;
    for (i = 0; i < nb_pixels; i++) {
        for (j = 0; j < 3; j++) {
            int nb_pixels_same_color = 1;
            for (k = i + 1; k < nb_pixels; k++) {
                if (data[i * 3 + j] == data[k * 3 + j]) {
                    nb_pixels_same_color++;
                } else {
                    break;
                }
            }
            if (nb_pixels_same_color > 2) {
                compressedData[nb_pixels_compressed * 3] = nb_pixels_same_color;
                compressedData[nb_pixels_compressed * 3 + 1] = data[i * 3 + j];
                compressedData[nb_pixels_compressed * 3 + 2] = data[i * 3 + j];
                nb_pixels_compressed++;
                i += nb_pixels_same_color - 1;
            } else {
                for (k = 0; k < nb_pixels_same_color; k++) {
                    compressedData[nb_pixels_compressed * 3] = 1;
                    compressedData[nb_pixels_compressed * 3 + 1] = data[i * 3 + j];
                    compressedData[nb_pixels_compressed * 3 + 2] = data[i * 3 + j];
                    nb_pixels_compressed++;
                }
            }
        }
    }
}

/*Écrire une fonction qui décompresse un tableau de GLubyte, puis une fonction qui
reconstitue l'image à partir du tableau trié de couleurs.*/
void decompressRLE (GLubyte* compressedData, int size, GLubyte* decompressedData) {
    int i, j, k;
    int nb_pixels = size / 3;
    int nb_pixels_decompressed = 0;
    for (i = 0; i < nb_pixels; i++) {
        for (j = 0; j < compressedData[i * 3]; j++) {
            for (k = 0; k < 3; k++) {
                decompressedData[nb_pixels_decompressed * 3 + k] = compressedData[i * 3 + 1 + k];
            }
            nb_pixels_decompressed++;
        }
    }
}


/*Écrire une version améliorée de cet algorithme en a joutant dans la compression
l'amélioration vue en cours avec les multiplicateurs négatifs.
*/
void reconstructImage (GLubyte* sortedColors, int width, int height, GLubyte* image) {
    int i, j, k;
    int nb_pixels = width * height;
    for (i = 0; i < nb_pixels; i++) {
        for (j = 0; j < 3; j++) {
            for (k = 0; k < 3; k++) {
                image[i * 3 + j * width * 3 + k] = sortedColors[i * 9 + j * 3 + k];
            }
        }
    }
}
