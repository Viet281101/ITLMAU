#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 2000

//// Fonction pour créer le mot de trace initial en fonction de la pente (dx, dy).
void creer_mot_trace_initial(int dx, int dy, char* mot_trace) {
    int x = 0, y = 0;
    int len = 0;

    while (x < dx && y < dy) {
        if (2 * (x + 1) * dy < 2 * (y + 1) * dx) {
            mot_trace[len] = 'H';
            x++;
        } else if (2 * (x + 1) * dy > 2 * (y + 1) * dx) {
            mot_trace[len] = 'D';
            x++;
            y++;
        } else {
            mot_trace[len] = 'D';
            x++;
            y++;
        }
        len++;
    }
    mot_trace[len] = '\0';
}

//// Fonction pour obtenir le mot de trace final en fonction du mot de trace initial.
void obtenir_mot_trace_final(const char* mot_trace_initial, char* mot_trace_final) {
    int len = strlen(mot_trace_initial);
    int j = 0;
    
    for (int i = 0; i < len; i++) {
        if (mot_trace_initial[i] == 'H') {
            mot_trace_final[j] = 'H';
            j++;
        } else if (mot_trace_initial[i] == 'D') {
            mot_trace_final[j] = 'H';
            j++;
            mot_trace_final[j] = 'H';
            j++;
            mot_trace_final[j] = 'D';
            j++;
        }
    }
    mot_trace_final[j] = '\0';
}

int main() {
    int dx = 11, dy = 3;
    char mot_trace_initial[MAX];
    char mot_trace_final[MAX];
    
    memset(mot_trace_initial, 0, sizeof(mot_trace_initial));
    memset(mot_trace_final, 0, sizeof(mot_trace_final));
    
    creer_mot_trace_initial(dx, dy, mot_trace_initial);
    printf("Mot de trace initial pour la droite (dx=%d, dy=%d): %s\n", dx, dy, mot_trace_initial);

    obtenir_mot_trace_final(mot_trace_initial, mot_trace_final);
    printf("Mot de trace final : %s\n", mot_trace_final);
    
    //// Mot de trace initial pour la droite (dx=11, dy=3): HHHDHHHDHHD
    //// Mot de trace final : HHHHHDHHHHHDHHHHD


    return 0;
}