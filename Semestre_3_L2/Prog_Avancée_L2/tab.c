#include <stdio.h>


int main(){
  int echange;
  int i, j;

  int somme, moyenne = 0;
  int nombre[4];

  //remplir le tableau:
  for(i = 0; i<4; i++)
    {
      printf("Entrez vos nombres: %d\n", (i+1));
      scanf("%d", &nombre[i]);
    }

  //afficher le tableau:
  printf("voici votre tableau: \n");
  for(i = 0; i<4; i++)
    {
      printf("%d   ", nombre[i]);
    }
  printf("\n");
  
  //faire le somme du tableau:
  printf("La somme des éléms du tableau est: ");
  for(i=0; i<4; i++)
    {
      somme += nombre[i];
    }
  printf("%d\n", somme);

  //faire la moyenne du tableau:
  printf("La moyenne des élémens du tableau est: ");
  moyenne = somme/4;
  printf("%d\n", moyenne);

  
  //Inverser le tableau:
  printf("voici votre inverser tableau: \n");
  for(i = 0, j=4-1; i<j ; i++, j--)
    {
      echange =  nombre[i];
      nombre[i] =  nombre[j];
      nombre[j] = echange;
    }
  
  for(i = 0; i<4; i++)
    {
       printf("%d   ", nombre[i]);
    }
  printf("\n");
  
  return 0;
}
