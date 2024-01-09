
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct{
    int val;
    struct s_cellule_t * suiv; 
}cellule_t;


void shuffle(cellule_t ** listeD, cellule_t ** listeS){
    cellule_t * temp;
    // while(*listeD != NULL && *listeS != NULL){
    //     *listeD = &(*listeD) -> suiv;
    //     temp = *listeD;
    //     *listeD = *listeS;
    //     *listeS = &(*listeS) -> suiv;
    //     (*listeD) -> suiv = temp;
    //     (*listeD) = &(*listeD) -> suiv;
    //     *listeD = *listeS;
    // }
    if (*listeS == NULL) return;
    if (*listeD == NULL) {
        *listeD = *listeS;
        *listeS = NULL;
        return;
    }
    temp = *listeS;
    *listeS = temp -> suiv;
    (*listeD) -> suiv = temp;
    shuffle(&temp -> suiv, listeS);
}

int main(void){

    cellule_t * l1 = consL(1, consL(2, consL(3, NULL)));
    cellule_t * l2 = consL(-1, consL(-2, consL(-3, NULL)));
    shuffle(&l1, &l2);
    return 0;
}

