#include<stdio.h>
#include<assert.h>

int fg(int a)
{
   return a*2+1;
}
int fd(int a)
{
   return a*2+2;
}
int pere(int a)
{
   return (a-1)/2;
}

int estUnTas(int n,int* t)
{
   int i;
   for(i=1;i<n;i++)
      if(t[pere(i)]>t[i])
         return 0;
   return 1;
   
}

void echange(int* a,int* b)
{
   int t;
   t=*a;
   *a=*b;
   *b=t;
}

void triParTas(int n,int* t)
{
   int j;
   int indMin;
   int i;
   for(i=1;i<n;i++)
   {
      j=i;
      while(j>0 && t[pere(j)]>t[j] )
      {
         echange(t+pere(j),t+j);
         j=pere(j);
      }
      assert(estUnTas(i+1,t));
   }
   for(i--;i>0;i--)
   {
      assert(estUnTas(i,t));
      echange(t,t+i);
      j=0;
      while(1)
      {
         if(fg(j)>=i)
            break;
         if(fd(j)>=i)
         {
            if(t[fg(j)]<t[j])
               indMin=fg(j);
            else
               break;
         }
         else
            indMin= t[fg(j)]>t[fd(j)] ? fd(j) : fg(j);
         echange(t+j,t+indMin);
         j=indMin;
      }
   }
}

int main(void)
{
   int T[7]={-3,6,-2,7,6,5,-4};
   int i;
   triParTas(7,T);
   for(i=0;i<7;i++)
      printf("%d ",T[i]);
}
