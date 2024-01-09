#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<time.h>

//{{{ Exo1 


int tempsPasse(clock_t a)
   // renvoie le temps écoulé depuis a en miliseconde
{
   return (int)((clock()-a)*1000/CLOCKS_PER_SEC);
}


void tempsExecut(void)
   // à placer dans le fichier tmpsExecut.c
{
   int i;
   long int nbOperation=100000;
   clock_t instant;
   while(1)
   {
      instant=clock();
      for(i=0;i<nbOperation;i++);
      instant=tempsPasse(instant);
      printf("%ld operations;  temps passé : %ld ms;  op/ms %f \n",
            nbOperation,
            instant,
            nbOperation/(float)instant
            );
      nbOperation*=1.1;
   }
}



//}}}
//{{{ fibonnacci (exercice 2 non fait)
int fibo_b(int n)
   // fibonnacci boucle
{
   int i_1,i_2,i;
   if(n<0) exit(EXIT_FAILURE);
   if(n<2) return n;
   n--;
   for(i_2=0,i_1=1;n>0;n--)
   {
      i=i_1+i_2;
      i_2=i_1;
      i_1=i;
   }
   return i;
}

int fibo_r(int n)
   // fibonnacci recursif
{
   if(n<0) exit(EXIT_FAILURE);
   if(n<2) return n;
   return fibo_r(n-1)+fibo_r(n-2);
}

void testExo3TP2(void)
{
   int i;
   int valb;
   int valr;
   clock_t depart;
   for(i=10;i<40;i++)
   {
      depart=clock();
      valb=fibo_b(i);
      printf("temps écoulé pour fibo_b(%d)=%d : %d\n",i,valb,tempsPasse(depart));
      depart=clock();
      valr=fibo_r(i);
      printf("temps écoulé pour fibo_r(%d)=%d : %d\n\n",i,valr,tempsPasse(depart));
      assert(valr==valb);
   }
}
//}}}
//{{{ puissance

int puissance(int a,int n)
{
   int val;
   if(n==0) return 1;

   val=puissance(a,n/2); // car puissance(a,n)=puissance(a,n/2)*puissance(a,n/2) si n est pair
   val*=val;

   if(n%2) val*=a; // il faut gérer le cas impair
   return val;
}


//}}}
//{{{ echange
void echange(int* a,int* b)
{
   int temp;
   temp=*a;
   *a=*b;
   *b=temp;
}

//}}}
//void echange_p(int** a,int** b)
//   // echange la vaeur de deux variable de type int*
//{
//   int* temp;
//   temp=*a;
//   *a=*b;
//   *b=temp;
//}
// {{{ triRapide
void triRapide(int* tab,int taille)
{
   int pivot=tab[0];
   int a=taille-1; 
   int d=0;
   if(taille<2) return;
   while(d<=a)
   {
      if(tab[d]>pivot)
      {
         echange(tab+d,tab+a);
         a--;
      }
      else
         d++;
   }
   echange(tab+a,tab);
   triRapide(tab,a);
   triRapide(tab+a+1,taille-a-1);
}
//}}}

// {{{triRapideP
void triRapideP(int* tab,int taille)
{
   int pivot,a,d,ap_pivot;
   if(taille<2) return;
   pivot=tab[((unsigned)rand())%taille]; // on choisit le pivot au hasard
   d=0;
   ap_pivot=0;
   a=taille-1;
   while(d<=a)
   {
      if(tab[d]>pivot)
      {
         echange(tab+d,tab+a);
         a--;
      }
      else
      {
         if(tab[d]==pivot)
         {
            echange(tab+ap_pivot,tab+d);
            ap_pivot++;
         }
         d++;
      }
   }
   ap_pivot--;
   while(ap_pivot>=0) 
      // ici on place les valeurs pivots à la limite de façon à ne pas avoir à les 
      // trier dans les futurs appels 
   {
      echange(tab+ap_pivot,tab+a);
      ap_pivot--;
      a--;
   }
   triRapideP(tab,a+1);
   triRapideP(tab+d,taille-d);
}
//}}}

//{{{ compteAf
//
int compteAf_(int E[],char S[],int taille_v,int tailledeE,int s)
   // on suppose que E ne contient pas de valeurs nulles
{
   int valsans;
   int valavec;
   if(s<0)
      return 0;
   if(s==0)
   {
      printf("{ ");
      for(int i=tailledeE;i<taille_v;i++)
         if(S[i])
            printf("%d ",E[i]);
      printf("}\n");
      return 1;
   }
   if(tailledeE==0)
      return 0;
   S[tailledeE-1]=0;
   valsans=compteAf_(E,S,taille_v,tailledeE-1,s); // solution sans la dernière valeur
   S[tailledeE-1]=1;
   valavec=compteAf_(E,S,taille_v,tailledeE-1,s-E[tailledeE-1]); // solution avec la dernière valeur
   return valavec || valsans; // si elle a été trouvé dans l'un des deux cas 1 est renvoié 0 sinon
}

int compteAf(int E[],int tailledeE,int s)
{
   char S[tailledeE]; 
   return compteAf_(E,S,tailledeE,tailledeE,s);
}
//}}}

int main(void)
{
   return 0;
}



