#include <stdio.h>
#include <stdlib.h>
#include<time.h>

/* Structure de file et fonctions utiles */
typedef struct element {
    int valeur;
    struct element *suivant;
} element;


typedef struct fifo{
  element *debut;
  element *fin;
  int taille;
} fifo;


// Créer une nouvelle file
fifo *new_fifo();
// Enfiler un élément
void push(fifo *F, int s);
// Défiler un élément
void enqueue(fifo *F);
// Récupérer le premier élément
int get_first(fifo *F);
// Afficher les données de la file
void print_fifo(fifo *F);
// Tester si la file est vide
int is_empty_fifo(fifo *F);