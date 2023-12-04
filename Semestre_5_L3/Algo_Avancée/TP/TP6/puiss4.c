#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_TURN 100

/* Indique si le joueur  en paramètre a quatre jetons alignés; les quatre
boucles correspondent aux alignement horizontaux, verticaux, puis diagonal vers
le haut à gauche et diagonale vers le bas à gauche */
int joueur_gagne(int joueur, int jeu[6][7]){
    int joueur_a_gagne = 0;
    int c, l;
    for(c=0;c<=3;c++){
       for(l=5;l>=0;l--){
          if(jeu[l][c]==joueur && jeu[l][c+1]==joueur && jeu[l][c+2]==joueur && jeu[l][c+3]==joueur)
             joueur_a_gagne =1;
       }
    }
    for(c=0;c<=6;c++){
       for(l=5;l>=3;l--){
          if(jeu[l][c]==joueur && jeu[l-1][c]==joueur && jeu[l-2][c]==joueur && jeu[l-3][c]==joueur)
             joueur_a_gagne =1;
       }
    }
    for(c=0;c<=3;c++){
       for(l=5;l>=3;l--){
          if(jeu[l][c]==joueur && jeu[l-1][c+1]==joueur && jeu[l-2][c+2]==joueur && jeu[l-3][c+3]==joueur)
             joueur_a_gagne =1;
       }
    }
    for(c=6;c>=3;c--){
       for(l=5;l>=3;l--){
          if(jeu[l][c]==joueur && jeu[l-1][c-1]==joueur && jeu[l-2][c-2]==joueur && jeu[l-3][c-3]==joueur)
             joueur_a_gagne =1;
       }
    }
    return joueur_a_gagne;
}
 
/// Ajoute le jeton du joueur dans la colonne choisie ///
int jouer(int numero_joueur,int num_col, int jeu[6][7], int hColonnes[7]){
    jeu[5-hColonnes[num_col]][num_col] = numero_joueur; //
    hColonnes[num_col] = hColonnes[num_col] + 1;
    int joueur_a_gagne = 0;
    joueur_a_gagne = joueur_gagne(numero_joueur, jeu);
    return joueur_a_gagne;
}
 
/// Indique si la colonne est remplie
int colonne_remplie(int jeu[6][7], int numColonne){
    int remplie = 1;
    if(jeu[0][numColonne] == 0){
        remplie = 0;
    }
    return remplie;
}
 
/// Indique si la grille est remplie
int grille_remplie(int jeu[6][7]){
    int c, l;
    int remplie = 1;
    for(c=0;c<=6;c++){
        for(l=5;l>=0;l--){
            if(jeu[l][c]==0){
                remplie = 0;
                break;
            }
        }
    }
    return remplie;
}

/// Indique si le jeu est fini: soit un joueur a gagné, soit la grille est remplie
int pos_terminale(int jeu[6][7]){
    int pos_term = 0;
    if(grille_remplie(jeu)||joueur_gagne(1,jeu)||joueur_gagne(2,jeu)){
        pos_term = 1;
    }
    return pos_term;
}
 


/// Permet d'ajouter le jeton d'un joueur sur la grille dans la colonne spécifiée
void jouer_jeton(int jeu[6][7], int num_col, int joueur){
    int l;
    for(l=5;l>=0;l--){  
        if(jeu[l][num_col]==0){  
            jeu[l][num_col] = joueur;
            break;
        }
    }
}
 
/// Permet de retirer le dernier jeton se trouvant sur la colonne num_col
void retirer_jeton(int jeu[6][7], int num_col){
    int l;
    for(l=0;l<=5;l++){    
        if(jeu[l][num_col]!=0){  
            jeu[l][num_col] = 0;
            break;
        }
    }
}

/// Inverser les deux joueurs si le joueur décide de jouer en second
int inverser_joueur(int joueur){
    if(joueur==1){
        return 2;
    }
    else if(joueur==2){
        return 1;
    }
    else{
        return -1;
    }
}
 
 
 
void afficher_jeu(int tabPoint[6][7]){
    int i, j;
    printf("  0   1   2   3   4   5   6  \n");
    printf("|---|---|---|---|---|---|---| \n");
    for(i=0; i<6;i++){
        for(j=0;j<7;j++){
 
            printf("| %d ", tabPoint[i][j]);
        }
         printf("| \n|---|---|---|---|---|---|---| \n");
    }
}


// Fonction d'évaluàtion de position 
int evaluation_position(int joueur, int jeu[6][7], int profondeur) {};

/* Partie de l'IA permettant de calculer le min des valeurs calculées par le joueur
MAX à la position précédente */
int joueur_MIN(int jeu[6][7], int profondeur, int joueur) {};
 
/* Partie de l'IA permettant de trouver le max des valeurs calculés par le joueur MIN
à la profondeur précédente */
int joueur_MAX(int jeu[6][7], int profondeur, int joueur) {};

/// Algorithmes minimax et alpha-beta
int minimax(int jeu[6][7], int profondeur, int joueur) {};
int alpha_beta(int jeu[6][7], int profondeur, int joueur, int alpha, int beta) {};

int main(){
    int joueur_a_gagne=0;
    int num;
    int nb_tours = 1;
    int jeu[6][7];  
    int hColonnes[7] = {0}; 
    int i,j;
    for(i=0; i<6; i++){
        for(j=0; j<7; j++){
            jeu[i][j]=0;
        }
    }
    printf("\n Jouer en (1) ou (2)? ");
    int joueur=0;
    scanf("%d",&joueur);
    printf("\n");
    if (joueur ==2){
        inverser_joueur(joueur);
    }
    int ordinateur = (joueur==1)?2 : 1;
    printf("\n Joueur : %d, Ordinateur : %d \n \n ",joueur,ordinateur);
    afficher_jeu(jeu);
    printf("\n");
    while (joueur_a_gagne==0){
        for(nb_tours = 0; nb_tours<MAX_TURN; nb_tours++){
            if((nb_tours+joueur) % 2 == 1){
                printf("\n Jouer dans la colonne : ");
                scanf(" %d", &num);
                if(colonne_remplie(jeu, num)){
                    printf("La colonne %d est pleine, recommencer.",num);
                    printf("\n Jouer dans la colonne : ");
                    scanf(" %d", &num);
                }
                else{
                    joueur_a_gagne = jouer(1,num,jeu,hColonnes);
                    afficher_jeu(jeu);
                    printf("\n Fin du tour \n \n");
                }
            }
            else{
                if(joueur_a_gagne !=1){
                    int choix_ordi = minimax(jeu, 6, 2);
                    joueur_a_gagne = jouer(2,choix_ordi,jeu,hColonnes);
                    if(joueur_a_gagne != 1){
                    afficher_jeu(jeu);
                    printf("\n Fin du tour \n \n");
                    }
                    else{
                        afficher_jeu(jeu);
                        printf("\n Vous avez perdu ! \n");
                        break;         
                    }
                }
                else{
                        afficher_jeu(jeu);
                        printf("\n Vous avez gagné ! \n");
                        break;
                }
            }
        }
    }
}