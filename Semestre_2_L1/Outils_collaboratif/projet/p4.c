#include<stdio.h>
#include<stdlib.h>

char tab[6][7];
int compteur_alignement, isvictoire;


void print_t ()
{
  printf ("\n\tPUISSANCE 4\n");
  for (int i = 6; i > -1; i--)
  {
    printf ("+---+---+---+---+---+---+---+");
    printf ("\n");
    for (int j = 0; j < 7; j++)
    {
      // printf("b=[%d][%d]",i,j);
      printf ("  %c ", tab[i][j]);
    }
    printf ("\n");
  }
  printf ("+---+---+---+---+---+---+---+");
  printf ("\n  0   1   2   3   4   5   6\n");
}

void test_vertical (int j, int x, char joueur)
{
  compteur_alignement = 0;
  for (int i = 0; i < 4; i++)
  {
    if (tab[j - i][x] == joueur && j >= 0)
    {
      compteur_alignement++;
    }else{
      break;
    }
  }
  if (compteur_alignement == 4)
  {
    printf ("-> Joueur %c a gagné!", joueur);
    isvictoire = 0;
  }
}

void test_horizontal (int j, int x, char joueur)
{
  compteur_alignement = 0;
  for (int i = 0; i < 4; i++)
  {
    if (tab[j][x - i] == joueur && x >= 0)
    {
      compteur_alignement++;
    }else{
      break;
    }
  }
  if (compteur_alignement == 4)
  {
    printf ("-> Joueur %c a gagné!", joueur);
    isvictoire = 0;
  }
  for (int i = 1; i < 4; i++)
  {
    if (tab[j][x + i] == joueur && x <= 7)
    {
      compteur_alignement++;
      if (compteur_alignement == 4)
      {
        printf ("-> Joueur %c a gagné!", joueur);
        isvictoire = 0;
        break;
      }
    }else{
      break;
    }
  }
}

void test_diag (int j, int x, char joueur)
{
  compteur_alignement = 0;
  int i;
  for (i = 0; i < 4; i++)
  {
    if (tab[j - i][x - i] == joueur && x >= 0 && j >= 0)
    {
    compteur_alignement++;
    }else{
      break;
    }
  }
  if (compteur_alignement == 4)
  {
    printf ("-> Joueur %c a gagné!", joueur);
    isvictoire = 0;
  }
  for (i = 1; i < 4; i++)
  {
    if (tab[j + i][x + i] == joueur && x <= 7 && j <= 7)
    {
    compteur_alignement++;
    if (compteur_alignement == 4)
      {
        printf ("-> Joueur %c a gagné!", joueur);
        isvictoire = 0;
        break;
      }
    }else{
      break;
    }
  }
}

void test_diag2 (int j, int x, char joueur)
{
  compteur_alignement = 0;
  int i;
  for (i = 0; i < 4; i++)
  {
    if (tab[j + i][x - i] == joueur && x >= 0 && j <= 7)
    {
      compteur_alignement++;
    }else{
      break;
    }
  }
  if (compteur_alignement == 4)
    {
      printf ("-> Joueur %c a gagné!", joueur);
      isvictoire = 0;
    }
  for (i = 1; i < 4; i++)
  {
    if (tab[j - i][x + i] == joueur && x <= 7 && j >= 0)
    {
      compteur_alignement++;
      if (compteur_alignement == 4)
      {
        printf ("-> Joueur %c a gagné!", joueur);
        isvictoire = 0;
        break;
      }
    }else{
      break;
    }
  }
}



int main()
{
  int x, i, j, impair, tour;
  for (i = 0; i < 6; i++)
  {
    for (j = 0; j < 7; j++)
    {
      tab[i][j] = ' ';
    }
  }
  print_t ();

  isvictoire = 1;
  char joueur;
  //for(int i=0;i<4;i++)
  tour = 0;
  while (isvictoire)
  {
    printf ("\n-> Entrez un chiffre entre 0 et 6 : ");
    scanf ("%d", &x);
    tour = tour + 1;
    impair = tour % 2; // ici utilisC) pour selectionnC) quel joueur joue(Rouge ou Bleu)
    j = 0;

    while (tab[j][x] != ' ')
    {
      j++;
    }

    if (impair){
      printf ("\n.Le joueur R a joué.");
      printf ("\n.Le joeur B doit jouer maintenant.\n");
      joueur = 'R';
    }else{
      printf ("\n.Le joueur B a joué.");
      printf ("\n.Le joeur R doit jouer maintenant.\n");
      joueur = 'B';
    }

    tab[j][x] = joueur; // a chaque iteration soit Rouge soit Bleu joue

    print_t ();
    printf ("\n");
    test_vertical (j, x, joueur);
    test_horizontal (j, x, joueur);
    test_diag2 (j, x, joueur);
    test_diag (j, x, joueur);
  }
  printf ("\n-> Cette partie est terminée!\n\n");

  getchar();
  getchar();
}

