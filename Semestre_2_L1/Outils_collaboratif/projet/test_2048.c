//Template d'origine de 2048
#include <stdio.h>
#include <stdlib.h>
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
    
    for(i = 0; i < SIZE; i++)
    {
        printf("+---------+---------+---------+---------+");
        printf("\n");
        printf("|");
        for(j = 0; j < SIZE; j++)
        {
            if((x == i) && (y == j))
            {
                printf("    %d    |",tab[x][y]);
            }
            else
            {
                if(tab[i][j] > 0)
                {
                    printf("    %d    |", tab[i][j]);
                }
                else
                {
                    printf("         |");
                }
            }
        }
        printf("\n");
    }
    printf("+---------+---------+---------+---------+");
    printf("\n");
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

void touche()
{
    int touche;
    
    while((touche != 100) && (touche != 103) && (touche != 104) && (touche != 98))
    {
        touche = getchar();
        
        switch(touche)
        {
            case 100 :
                printf("droite\n");
            case 103 :
                printf("gauche\n");
            case 104 :
                printf("haut\n");
            case 98 :
                printf("bas\n");
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
    
    printf("Quel est votre prenom ? ");
    scanf("%s", b);
    
    printf("Bienvenue %s\n", b);
    printf("Voici : 1.jeu , 2.regles\n");
    scanf("%d", &a);
  
    if(a = 1)
    {   
        init_jeu(tab); 
        while(jeu = 1)
        {
            touche();
            print_tab(tab);
            
        }
        if(jeu == 2)
        {
            printf("yes");
        }
        else
        {
            printf("no");
        }
    }
    else if(a = 2)
    {
        printf("Hello");
    }
    
    getchar();
    getchar();
    return 0;
}
