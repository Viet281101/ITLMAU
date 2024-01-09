#include <stdio.h>
#include <stdlib.h>
//time.h contient les instructions necessaires pour definir un nombre aleatoire
#include <time.h>

#define SIZE 4

void print_tab(int tab[SIZE][SIZE])
{
  int i;
  int j; 
  int v[2] = {2,4}; 
  int p[4] = {0,1,2,3}; 
  int x; 
  int y;
  
  //init un var aleatoire dans la tuile
  while(1)
  {
    srand(time(NULL)); //srand() prend un int non signé comme entrée, donc time(NULL) doit être refondu.
    
    x = p[rand()%SIZE];//randomiser la valeur x
    y = p[rand()%SIZE];//randomiser la valeur y
    
    if(tab[x][y] == 0)
    {
      tab[x][y] = v[rand()%2];
      break;
    }
  }

  //Afichage de la grille du tableau
  for(i = 0; i < SIZE; i++)
  {
    printf("+----------+----------+----------+----------+");
    printf("\n");
    printf("|");
    for(j = 0; j < SIZE; j++)
    {
      //afficher la tuile dans la tab
      if((x == i) && (y == j))
      {
        printf("    %d     |", tab[x][y]);
      }
      else
      {
        if(tab[i][j] > 0)
        {
          printf("    %d     |", tab[i][j]);
        }
        else
        {
          printf("          |");
        }
      }
    }
    
    printf("\n");
  }
  printf("+----------+----------+----------+----------+");
  printf("\n\n");
}

void init_valeur(int tab[SIZE][SIZE])
{
	int i;
	int j;
	
	for (i = 0; i < SIZE; i++)
	{
		for(j = 0; j < SIZE; j++)
		{
			tab[i][j] = 0;
		}
  }
}

//fusion les tuiles au haut
void haut(int tab[SIZE][SIZE], int* point)
{
  int i,j,m;
  for(j=0;j<SIZE;j++)
  {
    for(i=0;i<SIZE - 1;i++)
    {
      if(tab[i][j]>0)
      //s'il existe une tuile avec numéro
      {
        if(tab[i][j]==tab[i+1][j]&&tab[i][j]!=0)
        {
          tab[i][j]=2*tab[i][j];
          *point += 2*(tab[i][j]);
          if(i==2)
          {
            tab[i+1][j]=0;
            *point += 2*(tab[i][j]);
          }
          else
          {
            for(m=i+1;m<SIZE-1;m++)
            {
              tab[m][j]=tab[m+1][j];
              tab[m+1][j]=0;
              *point += 2*(tab[i][j]);
            }
          }
        }
      }
    }
  }
}

//fusion les tuiles au bas
void bas(int tab[SIZE][SIZE], int* point)
{
  int i,j,m;
  for(j=0;j<SIZE;j++)
  {
    for(i=SIZE - 1;i>0;i--)
    {
      if(tab[i][j]>0)
      //s'il existe une tuile avec numéro
      {
        if(tab[i][j]==tab[i-1][j])
        {
          tab[i][j]=2*tab[i][j];
          *point += 2*(tab[i][j]);
          if(i==1)
          {
            tab[i-1][j]=0;
            *point += 2*(tab[i][j]);
          }
          else
          {
            for(m=i-1;m>0;m--)
            {
              tab[m][j]=tab[m-1][j];
              tab[m-1][j]=0;
              *point += 2*(tab[i][j]);
            }
          }
        }
      }
    }
  }
}

//fusion les tuiles a gauche
void gauche(int tab[SIZE][SIZE], int* point)
{
  int m,i,j;
  for(i=0;i<SIZE;i++)
  {
    for(j=0;j<SIZE - 1;j++)
    {
      if(tab[i][j]>0)
      //s'il existe une tuile avec numéro
      {
        if(tab[i][j]==tab[i][j+1])
        {
          tab[i][j]=2*tab[i][j];
          *point += 2*(tab[i][j]);
          if(j==2)
          {
            tab[i][j+1]=0;
            *point += 2*(tab[i][j]);
          }
          else
          {
            for(m=j+1;m<SIZE - 1;m++)
            {
              tab[i][m]=tab[i][m+1];
              tab[i][m+1]=0;
              *point += 2*(tab[i][j]);
            }
          }
        }
      }
    }
  }
}

//fusion les tuiles au droite
void droite(int tab[SIZE][SIZE], int* point)
{
  int m,i,j;
  for(i=0;i<SIZE;i++)
  {
    for(j=SIZE - 1;j>0;j--)
    {
      if(tab[i][j]>0)
      //s'il existe une tuile avec numéro
      {
        if(tab[i][j]==tab[i][j-1])
        //Si deux tuiles du tableau sont sur la même ligne horizontale contenant le même numéro
        {
          tab[i][j]=2*tab[i][j];
          *point += 2*(tab[i][j]);
          if(j==1)
          {
            tab[i][j-1]=0;
            *point += 2*(tab[i][j]);
          }
          else
          {
            for(m=j-1;m>0;m--)
            {
              tab[i][m]=tab[i][m-1];
              tab[i][m-1]=0;
              *point += 2*(tab[i][j]);
            }
          }
        }
      }
    }
  }
}

//effectuer l'opération deplacer les tuiles par entrer les caractere <d>, <g>, <h>, <b>
void touche(int tab[SIZE][SIZE], int* point)
{
  int touche, i, j, x, m;

  //deplacement les tuiles quand entrer la caractere
  while((touche != 100) && (touche != 103) && (touche != 104) && (touche != 98))
  {
    touche = getchar();
    
    switch(touche)
    {
      case 100 :  //quand entrer la carectere <d>, voir la nbr de posi dans acsii
        //deplacement les tuiles au droit
        for(i=0;i<SIZE;i++)
        {
          for(j=SIZE-2;j>=0;j--)
          {
            for(x=3-j,m=j;x>0;x--,m++)
            {
              if(tab[i][m+1]>0)
                break;
              else
              {
                tab[i][m+1]=tab[i][m];
                tab[i][m]=0;
              }
            }
          }
        }
        droite(tab, &point);
        break;
      case 103 :  //quand entrer la carectere <g>, voir la nbr de posi dans acsii
        //deplacement les tuiles au gauche
        for(i=0;i<SIZE;i++)
        {
          for(j=1;j<=SIZE-1;j++)
          {
            for(x=j,m=j;x>0;x--,m--)
            {
              if(tab[i][m-1]>0)
                break;
              else
              {
                tab[i][m-1]=tab[i][m];
                tab[i][m]=0;
              }
            }
          }
        }
        gauche(tab, &point);
        break;
      case 104 :  //quand entrer la carectere <h>, voir la nbr de posi dans acsii
        //deplacement les tuiles au haut
        for(j=0;j<SIZE;j++)
        {
          for(i=1;i<=SIZE - 1;i++)
          {
            for(x=i,m=i;x>0;x--,m--)
            {
              if(tab[m-1][j]>0)
                break;
              else
              {
                tab[m-1][j]=tab[m][j];
                tab[m][j]=0;
              }
            }
          }
        }
        haut(tab, &point);
        break;
      case 98 :  //quand entrer la carectere <b>, voir la nbr de posi dans acsii
        //deplacement les tuiles au bas
        for(j=0;j<SIZE;j++)
        {
          for(i=SIZE - 2;i>=0;i--)
          {
            for(x=3-i,m=i;x>0;x--,m++)
            {
              if(tab[m+1][j]>0)
                break;
              else
              {
                tab[m+1][j]=tab[m][j];
                tab[m][j]=0;
              }
            }
          }
        }
        bas(tab, &point);
        break;
    }
  }
}


void init_jeu(int tab[SIZE][SIZE])
{
  init_valeur(tab);
  print_tab(tab);
}


int main()
{
  int tab[SIZE][SIZE] = {};
  int a, jeu = 1;
  char b[100], t;
  int point = 0;
  int v[2] = {2,4}; 
  int p[4] = {0,1,2,3}; 
  int x; 
  int y;
  
  while(1)
  {
    srand(time(NULL)); 
    
    x = p[rand()%SIZE];
    y = p[rand()%SIZE];
    
    if(tab[x][y] == 0)
    {
      tab[x][y] = v[rand()%2];
      break;
    }
  }

  printf("Bonjour!\nQuel est votre prenom ? ");
  scanf("%s", &b);
  
  printf("\n~~Bienvenue %s!~~ ", b);
  printf("\nVous avez lance le jeu de puzzle 2048.\n");
  printf("1.Puzzle 2048\n2.Regles\n");
  printf("Voulez - vous jouer ou lire ? ");
  scanf("%d", &a);

  if(a == 1)
  {  
    //run game 
    init_jeu(tab); 
    while(jeu = 1)
    {
      printf("\n<d> pour la droite, <g> pour la gauche, <h> pour le haut, <b> pour le bas : ");
      touche(tab, &point);
      print_tab(tab);

      printf("\npoint : %d \n\n", point);
    }

    //afficher perdu - gagner
    if(jeu == 2)
    {
      printf("Bravo ! Vous avez gagne !");
    }
    else
    {
      printf("Dommage, vous avez perdu !");
    }
  }
  else if(a == 2)
  {
    //regles du jeu
    printf("\nC'est un jeu de puzzle et addictif. Le but du jeu est d'atteindre une tuile de 2048.");
    printf("\nMais ce n'est pas si facile parce que c'est un jeu de reflexion. Il faut avoir beaucoup de patience.\n\n");
    printf("Tout d'abord, le jeu commence avec des tuiles de 2.");
    printf("\nLe joueur fusionne des tuiles similaires en les deplaçant dans l'une des quatre directions (haut, bas, gauche, droite) ");
    printf("pour creer des tuiles 'plus grandes'.\n\n");
    printf("Apres chaque mouvement, une nouvelle tuile apparait à une position vierge aleatoire avec une valeur de 2.\n\n");
    printf("Le jeu se termine lorsque toutes les tuiles sont remplies ");
    printf("et qu'aucun mouvement ne peut fusionner les tuiles ou que le joueur cree une tuile\n");
    printf("d'une valeur de 2048. (Apres, le joueur peut rejouer le jeu en partant de 0).\n\n");
    printf("Pour deplacer les tuiles dans ce jeu, il faut utiliser les touches suivantes : ");
    printf("<d> pour la droite, <g> pour la gauche, <h> pour le haut, <b> pour le bas.\n\n");
    printf("Vous pouvez relancer le programme!\n");
    getchar();
    getchar();
  }
  
  
  return 0;
}



