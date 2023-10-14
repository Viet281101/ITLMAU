
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include<assert.h>
#include<string.h>


#define MAX 2000
typedef unsigned char uchar;
typedef unsigned char monplan [MAX][MAX];



void affiche (int sizex, int sizey, monplan pl) {
    int i, j;
    for(j = sizey; j >= 0; j--) {
        for (i = 0; i <= sizex; i++)
            printf("%c", pl[i][j]);
        printf("\n");
  }
}

// Fonction qui calcule les coordonnées de la droite discrète par l'algo trivial.
void droite_triviale (int dx, int dy, monplan pl){
    int x, y;
    float z;
    for (x = 0; x <= dx; x++) {
        z = ((float) x * dy / dx) + 0.49;
        y = (int) z;
    }
}

// Fonction qui permet d'afficher le résultat obtenu dans le plan pl.
void droite_triviale_verif (int dx, int dy, monplan pl) {
    int x, y;
    for (x = 0; x <= dx; x++) {
        y = (int) (((float) x * dy / dx) + 0.49);
        pl [x][y] = '.';
  }
}


void droite_br (int dx, int dy, monplan plan);
void droite_br_verif (int dx, int dy, monplan plan);
// void droite_rvw (int dx, int dy, monplan plan);
// void droite_rvw_verif (int dx, int dy, monplan plan);



int main (int argc, char ** argv) {
    int sizex, sizey, dx, dy, i, j;
    monplan plan;
    clock_t t0, t1, dt;

    dx = 100;
    dy = 100;

    if (argc == 3){
        dx = atoi (argv[1]);
        dy = atoi (argv[2]);
    }
    if (dx < 0)
        dx = 0 - dx;
    if (dy < 0)
        dy = 0 - dy;
    if (dx < dy) {
        dx += dy;
        dy = dx - dy;
        dx = dx - dy;
    } /* nous restons dans le premier octant */
    if (dx >= MAX)
        dx = MAX - 1;
    if (dy >= MAX)
        dy = MAX - 1;
    
    t0 = clock();
    memset (plan, ' ', MAX*MAX);
    droite_triviale_verif (11, 3, plan);
    printf("Triviale\n");
    affiche(11, 3, plan);
    t1 = clock();
    dt = t1 - t0;
    printf("Temps d'execution Triviale verif: %d\n", (int) dt);

    t0 = clock();
    memset(plan, ' ', MAX*MAX);
    droite_triviale_verif (24, 10, plan);
    affiche (24, 10, plan);
    t1 = clock();
    dt = t1 - t0;
    printf("Temps d'execution Triviale verif: %d\n", (int) dt);
    
    /* Test des fonctions */
    ////* Test avec l'algo de Bresenham */////
    memset (plan, ' ', MAX*MAX);
    printf("\n \n");
    printf("Bresenham\n");
    droite_br_verif (11, 3, plan);
    affiche (11, 3, plan);
    
    memset (plan, ' ', MAX*MAX);
    droite_br_verif (24, 11, plan);
    affiche (24, 11, plan);

    // memset (plan, ' ', MAX*MAX);
    // printf("\n \n");
    // printf("Rokne \n");
    // droite_rvw_verif (11, 3, plan);
    // affiche (11, 3, plan);
    // memset (plan, ' ', MAX*MAX);
    // droite_rvw_verif (24, 11, plan);
    // affiche (24, 11, plan);
 
}


void droite_br(int dx, int dy, monplan pl) {
    int x = 0, y = 0;
    int xe = dx;
    int ye = dy;
    int i, e;

    pl[x][y] = '.';

    if (dx > dy) {
        e = (dy - dx) * 2;
        for (i = 0; i < dx; i++) {
            x++;
            if (e > 0) {
                y++;
                e -= 2 * dx;
            }
            e += 2 * dy;
            pl[x][y] = '.';
        }
    } else {
        e = (dx - dy) * 2;
        for (i = 0; i < dy; i++) {
            y++;
            if (e > 0) {
                x++;
                e -= 2 * dy;
            }
            e += 2 * dx;
            pl[x][y] = '.';
        }
    }
}


void droite_br_verif(int dx, int dy, monplan pl) {
    memset(pl, ' ', MAX * MAX);
    droite_br(dx, dy, pl);
}

