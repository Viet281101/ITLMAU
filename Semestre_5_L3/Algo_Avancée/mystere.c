
#include <stdio.h>


int mystere (int dx, int dy) {
    dx -= dy;
    while (dx != dy) {
        if (dx > dy) {
            dx -= dy;
        } else {
            dy -= dx;
        }
    }
    return dx;
}

int droite (int dx, int dy) {
    return dx - dy;
}


int main (void) {
    int x, y;
    printf("x = ");
    scanf("%d", &x);
    printf("y = ");
    scanf("%d", &y);
    printf("mystere(%d, %d) = %d\n", x, y, mystere(x, y));
    printf("droite(%d, %d) = %d\n", x, y, droite(x, y));
    return 0;
}

// mystere(7,5) -> 1
// mystere(8, 6) -> 2
// mystere(22, 11) -> 11
