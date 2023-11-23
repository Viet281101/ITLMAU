
#include <stdlib.h>
#include <stdio.h>
#include "ima.h"


/*Écrire une fonction qui permet de construire la C-LUT : on utilisera une structure
Color pour construire un tableau de couleurs.*/
void buildCLUT (GLubyte* image, int width, int height, Color** clut, int* clutSize) {
    int nb_pixels = width * height;
    int i, j;
    int found;
    *clutSize = 0;

    *clut = (Color*)malloc(nb_pixels * sizeof(Color));
    if (*clut == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        return;
    }

    for (i = 0; i < nb_pixels; i++) {
        found = 0;
        for (j = 0; j < *clutSize; j++) {
            if ((*clut)[j].red == image[i * 3] &&
                (*clut)[j].green == image[i * 3 + 1] &&
                (*clut)[j].blue == image[i * 3 + 2]) {
                (*clut)[j].frequency++;
                found = 1;
                break;
            }
        }

        if (!found) {
            (*clut)[*clutSize].red = image[i * 3];
            (*clut)[*clutSize].green = image[i * 3 + 1];
            (*clut)[*clutSize].blue = image[i * 3 + 2];
            (*clut)[*clutSize].frequency = 1;
            (*clutSize)++;
        }
    }
}


/*Écrire une fonction qui permet de déterminer pour chaque couleur dans la C-LUT
sa fréquence d'apparition, afin de ne garder au final que les couleurs prédominantes.
On pourra commencer par trier la C-LUT via une fonction qui à une couleur associe
un entier, par exemple celle vue en cours. Pour ce faire, on pourra utiliser la fonction
qsort de std lib.h, ou réimplémenter par exemple un tri à bulles.*/
int compareColors(const void* a, const void* b) {
    Color* colorA = (Color*)a;
    Color* colorB = (Color*)b;

    return colorB->frequency - colorA->frequency;
}

void sortCLUT (Color* clut, int clutSize) {
    qsort(clut, clutSize, sizeof(Color), compareColors);
}


/*Écrire une fonction qui sélectionne k couleurs de la C-LUT (les k plus fréquentes),
et qui remplace chaque pixel de l'image par un pixel de la couleur la plus proche
parmi celles sélectionnées. On testera le résultat pro duit pour différentes valeurs de k.
*/
void reduceColors (GLubyte* image, int width, int height, Color* clut, int clutSize, int k) {
    int nb_pixels = width * height;
    int i, j;
    int minDistance, distance, minIndex;
    int red, green, blue;

    for (i = 0; i < nb_pixels; i++) {
        red = image[i * 3];
        green = image[i * 3 + 1];
        blue = image[i * 3 + 2];

        minDistance = 255 * 255 * 3 + 1;
        minIndex = 0;
        for (j = 0; j < k; j++) {
            distance = (red - clut[j].red) * (red - clut[j].red) +
                       (green - clut[j].green) * (green - clut[j].green) +
                       (blue - clut[j].blue) * (blue - clut[j].blue);
            if (distance < minDistance) {
                minDistance = distance;
                minIndex = j;
            }
        }

        image[i * 3] = clut[minIndex].red;
        image[i * 3 + 1] = clut[minIndex].green;
        image[i * 3 + 2] = clut[minIndex].blue;
    }
}

