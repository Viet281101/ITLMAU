#include "../includes/humain.h"

void action_joueur_humain(Jeu *jeu, const int couleur) {
    int ligne, colonne;
    _action_joueur_humain(&ligne, &colonne);

    int ok = 0;
    while (!ok) {
        printf("Vous voulez jouer en %c%d... ", colonne, ligne);

        if (!jeu_joueur(jeu, ligne - 1, colonne - 'A', couleur)) {
            printf("mais ce n'est pas possible, réessayez !\n");

            _action_joueur_humain(&ligne, &colonne);
        } else {
            printf("et c'est un bon coup ;)\n");
            ok = 1;
        }
    }
}

void _action_joueur_humain(int *ligne, int *colonne) {
    // Demande la colonne
    int ok = 0;
    char tmp;
    while (!ok) {
        printf("Quelle colonne voulez-vous placer votre jeton (A-H) ? ");
        scanf(" %1c", &tmp);

        majuscule(&tmp);
        if (!(tmp >= 'A' && tmp <= 'H')) {
            printf("Colonne renseignée invalide.\n");
        } else {
            *colonne = tmp;
            ok = 1;
        }
    }

    // Demande la ligne
    ok = 0, *ligne = 0;
    while (!ok) {
        printf("Quelle ligne voulez-vous placer votre jeton (1-8) ? ");
        scanf(" %1d", ligne);

        if (*ligne < 1 || *ligne > LARGEUR) {
            printf("Ligne renseignée invalide.\n");
        } else {
            ok = 1;
        }
    }
}
