
#include "ima.h"
#include <string.h>


/*Écrire une fonction qui p ermet de trier les 3 couleurs d'une image : on sto ckera
tous les GLubyte de rouge, de vert et de bleu dans un grand tableau.*/
void quickSort(GLubyte* arr, int left, int right) {
    int i = left, j = right;
    GLubyte tmp;
    GLubyte pivot = arr[(left + right) / 2 * 3];
    while (i <= j) {
        while (arr[i * 3] < pivot)
            i++;
        while (arr[j * 3] > pivot)
            j--;
        if (i <= j) {
            for (int k = 0; k < 3; k++) {
                tmp = arr[i * 3 + k];
                arr[i * 3 + k] = arr[j * 3 + k];
                arr[j * 3 + k] = tmp;
            }
            i++;
            j--;
        }
    };

    if (left < j)
        quickSort(arr, left, j);
    if (i < right)
        quickSort(arr, i, right);
}

void sortColors (GLubyte* image, int width, int height, GLubyte* sortedColors) {
    int nb_pixels = width * height;
    memcpy(sortedColors, image, nb_pixels * 3 * sizeof(GLubyte));

    quickSort(sortedColors, 0, nb_pixels - 1);
}


/*Écrire une fonction qui p ermet de compresser un tableau de GLubyte selon le
princip e de l'algorithme RLE naïf.*/
void compressRLE(GLubyte* data, int size, GLubyte** compressedData, int* compressedSize) {
    int i, count;
    int capacity = 100;

    *compressedData = (GLubyte*)malloc(capacity * sizeof(GLubyte));
    if (*compressedData == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        return;
    }

    *compressedSize = 0;
    i = 0;
    while (i < size) {
        count = 1;
        while (i + count < size && data[i] == data[i + count] && count < 255) {
            count++;
        }

        if (*compressedSize + 2 > capacity) {
            capacity *= 2;
            *compressedData = (GLubyte*)realloc(*compressedData, capacity * sizeof(GLubyte));
            if (*compressedData == NULL) {
                fprintf(stderr, "Memory reallocation failed.\n");
                return;
            }
        }

        (*compressedData)[(*compressedSize)++] = count;
        (*compressedData)[(*compressedSize)++] = data[i];

        i += count;
    }
}

/*Écrire une fonction qui décompresse un tableau de GLubyte, puis une fonction qui
reconstitue l'image à partir du tableau trié de couleurs.*/
void decompressRLE(GLubyte* compressedData, int compressedSize, GLubyte** decompressedData, int* decompressedSize) {
    int i, j, k, count;
    int capacity = 100;

    *decompressedData = (GLubyte*)malloc(capacity * sizeof(GLubyte));
    if (*decompressedData == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        return;
    }

    *decompressedSize = 0;
    i = 0;
    while (i < compressedSize) {
        count = compressedData[i++];
        GLubyte value = compressedData[i++];

        if (*decompressedSize + count > capacity) {
            capacity += count;
            *decompressedData = (GLubyte*)realloc(*decompressedData, capacity * sizeof(GLubyte));
            if (*decompressedData == NULL) {
                fprintf(stderr, "Memory reallocation failed.\n");
                return;
            }
        }

        for (j = 0; j < count; j++) {
            for (k = 0; k < 3; k++) {
                (*decompressedData)[(*decompressedSize) * 3 + k] = value;
            }
            (*decompressedSize)++;
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
