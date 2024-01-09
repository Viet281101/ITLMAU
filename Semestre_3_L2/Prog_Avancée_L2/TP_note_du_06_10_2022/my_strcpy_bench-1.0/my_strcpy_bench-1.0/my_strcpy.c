/* my_strcpy.c --
 * Farès Belhadj - 
 * amsi@up8.edu
 * 04/10/2022
 */

#include "my_strcpy.h"

/*
 * Une première proposition de fonction de copie de chaînes de caractères.
 */
char * my_strcpy_01(char * dst, const char * src) {
  int i;
  for(i = 0; src[i] != '\0'; ++i)
    dst[i] = src[i];
  dst[i] = '\0';
  return dst;
}

/*
 * Une seconde proposition de fonction de copie de chaînes de caractères.
 */
char * my_strcpy_02(char * dst, const char * src) {
  char * ret = dst;
  while( (*dst++ = *src++) );
  return ret;
}


/*
 * À vous d'en proposer une troisième, plus rapide que les deux
 * précédentes. Vous ne devez utiliser aucune fonction issue d'une
 * bibliothèque.
 *
 * Ne pas oublier de la déclarer dans le fichier my_strcpy.h et de la
 * tester, avec les autres, dans main.c
 */

/* Voici une définition vide */

char * my_strcpy_03(char * dst, const char * src) { 
    char *ret = dst;
    int *dstInt = (int *)dst;
    int *srcInt = (int *)src;
    int continuer = 1;
    //fprintf(stderr, "je suis 57\n");
    while(1){
        src = (char *)srcInt;
        for(int i = 0; i < (int)sizeof(int) -1; i++){ //I added -1 because if the 4th
            //fprintf(stderr, "adresse %p : valeur %d\n", src+i, src[i]);
            if (src[i] == '\0') {
                continuer = 0;
                break;
            }
        }
        if (!continuer) break;

        //fprintf(stderr, "je suis %d\n", __LINE__);
        *(dstInt++) = *(srcInt++);
    }
    //fprintf(stderr, "je suis %d\n", __LINE__);
    dst = (char *)dstInt;
    while((*(dst++) = *(src++)));

    return ret;
} 




char *my_strcpy_04(char *dst, const char *src){
    char * save = dst;
    int *isrc = (int *)src, *idst = (int *)dst;

    do{
        if(((char *)isrc)[0]) {
            if(((char *)isrc)[1]) {
                if(((char *)isrc)[2]) {
                    *idst = *isrc;
                    if(!((char *)isrc)[3]) break;
                } else {
                    *((short *)idst) = *((short *)isrc);
                    ((char *)idst)[2] = 0;
                    break;
                }
            } else {
                *((short *)idst) = *((short *)isrc);
                break;
            }
        } else {
            ((char *)idst)[0] = 0;
            break;
        }
        ++idst;++isrc;
    } while(1);
    return save;
}


