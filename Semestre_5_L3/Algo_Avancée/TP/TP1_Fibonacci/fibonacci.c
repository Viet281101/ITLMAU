
#include <stdio.h>
#include <stdlib.h>
#include<time.h>

#define echantillon_max 300

/* Algorithme récursif */
int fibo_rec(int n){
    int res=0;
    if (n==0 || n==1){
        return 1;
    }
    else{
        res=fibo_rec(n-1) + fibo_rec(n-2);
        return res;
    }
}

/* Algorithme itératif */
int fibo_ite(int n){
    int a=1;
    int b=1;
    int c=1;
    for (int i = 1; i < n; i++) {
        c = a + b;
        a= b;
        b = c;
    }
    return c;
}

/* Algorithme vectoriel */
int fibo_vect(int n){
    int *f = malloc((n+1)*sizeof(int));
    f[0] = 1;
    f[1] = 1;
    for (int i = 2; i <= n; i++)
       {
            f[i] = f[i-1] + f[i-2];
       }
    return f[n];
}

/* Algorithme récursif terminal */
int fibo_rect_aux(int n, int a, int b){
  if (n==1){
    return a;
  }
  else return fibo_rect_aux(n-1,a+b,a);
}

int fibo_rect(int n){
  return fibo_rect_aux(n,1,1);
}



/* Algo matriciel, encodant la multiplication de matrices et la puissance rapide */
void multiplyMatrices(int m1[2][2], int m2[2][2], int result[2][2]){
   for (int i = 0; i < 2; ++i) {
      for (int j = 0; j < 2; ++j) {
         result[i][j] = 0;
      }
   }
   for (int i = 0; i < 2; ++i) {
      for (int j = 0; j < 2; ++j) {
         for (int k = 0; k < 2; ++k) {
            result[i][j] += m1[i][k] * m2[k][j];
         }
      }
   }
}

void copy(int mat[2][2], int copy[2][2]){
  /* On veut copier le contenu de mat dans copy */
  for (int i=0; i<2; i++){
    for (int j=0; j<2; j++){
        copy[i][j]=mat[i][j];
    }
  }
}

void puissance(int mat[2][2], int res[2][2], int n){
  int b[2][2], aux[2][2];
  if (n==1){
    for (int i = 0; i < 2; i++) {
      for (int j = 0; j < 2; j++) {
         res[i][j] = mat[i][j];
      }
    }
  }
  else if (n%2 ==0){
    multiplyMatrices(mat,mat,b);
    puissance(b,res,n/2);
  }
  else {
    multiplyMatrices(mat,mat,b);
    puissance(b,res,n/2);
    multiplyMatrices(mat,res,aux);
    copy(aux,res);
  }
}

/* Méthode logarithmique, voir https://jj.up8.site/AA/AA23_Intro.html */
typedef unsigned long long int ullint;
struct paire {
    ullint fun;
    ullint fdeux;
};
typedef struct paire paire;

paire fiblog (int n) {
    paire mi, res;
    ullint fi;
    int i;

    if (n < 2){
	    res.fun = (ullint) 1;
	    res.fdeux = (ullint) 1;
	    return res;
    }
    i = n >> 1;
    mi = fiblog(i);
    if (n & 0x01) {
	    res.fdeux = mi.fun * mi.fun + mi.fdeux * mi.fdeux;
	    res.fun = (mi.fun + mi.fdeux + mi.fdeux) * mi.fun;
	    return res;
    }
    res.fun = mi.fun * mi.fun + mi.fdeux * mi.fdeux;
    res.fdeux = (mi.fun + mi.fun - mi.fdeux) * mi.fdeux;
    return res;
}

ullint fibo_log (int n) {
  paire res;
  if (n >= 0 && n < 92) {
	  res = fiblog (n);
	  return res.fun;
  }
  return (ullint) 0;
}


/* Algorithme de Fibonacci avec mémorisation; les valeurs déjà calculées sont stockées dans un fichier "fibo.txt" */
int minimum(int a,int b){
    if(a>=b)
        return b;
    else
        return a;
}


int import(int* tab, int n){
    FILE *fichier = fopen("fibo.txt","r");
    int max;
    if (fichier != NULL){
        fscanf(fichier,"%d",&max);
        int l = minimum(max,n);
        for(int i=0; i<l; i++){
            fscanf(fichier,"%d",&(tab[i]));
        }
        fclose(fichier);
    }
    return max;
}

void export(int *tab,int s){
    FILE *fichier= fopen("fibo.txt","w");
    if (fichier != NULL){
        fprintf(fichier,"%d \n",s);
        for (int i=0; i<= s; i++){
            fprintf(fichier,"%d \n",tab[i]);
        }
        fclose(fichier);
    }
}

/* La fonction qui calcule les coefficients de Fibonacci lorsque nécessaire. */
int fib_aux(int *tab, int n){
    if (tab[n]!=0)
        return tab[n];
    else{
        int a=fib_aux(tab,n-1);
        int b=fib_aux(tab,n-2);
        tab[n]=a+b;
        return tab[n];
    }
}


int fib_incr(int n){
    int *tab = malloc((n+1)*sizeof(int));
    int max=import(tab,n+1);
    if (max >= n)
        return tab[n];
    else{
        int res=fib_aux(tab,n);
        export(tab,n);
        return res;
    }
}

/* Fonction main */
// int main(){
//   /* Partie test des résultats. */
//   // int n=17;
//   // printf("Valeur de fibo(%d) récursif : %d. \n",n,fibo_rec(n));
//   // printf("Valeur de fibo(%d) itératif : %d. \n",n,fibo_ite(n));
//   // printf("Valeur de fibo(%d) vectoriel : %d. \n",n,fibo_vect(n));
//   // printf("Valeur de fibo(%d) récursif terminal : %d. \n",n,fibo_rect(n));
//   // int mat[2][2] = {{1,1},{1,0}};
//   // int res[2][2] ={{0,0},{0,0}};
//   // puissance(mat,res,n);
//   // printf("Valeur de fibo(%d) matriciel : %d. \n",n,res[0][0]);
//   // printf("Valeur de fibo(%d) logarithmique : %lld. \n",n,fibo_log(n));
//   // printf("Valeur de fibo(%d) avec mémorisation : %d. \n",n,fib_incr(n));
//   /* Partie test du temps de calcul */
//   int n, res_rec, res_ite, res_log, res_vect, res_memo;
//   clock_t td, ta, dt;
//   for (n=1; n < echantillon_max; n+=10){
//       // Nombre
//       printf("nb :  %d  \t",n);
//       td = clock();
//       for (int i=0; i < n; i++) {
// 		    res_ite = fibo_ite(i);
// 	    }
//       ta = clock();
//       printf ("ite : %ld \t",(int) ta-td);
//       // // Temps récursif
//       // td=clock();
//       //   for (int i=0; i < n; i++) {
// 		  //     res_rec = fibo_rec(i);
// 	    //   }
//       // ta=clock();
//       // printf ("rec : %ld \t",(int) ta-td);
//       // Temps vectoriel
//       td=clock();
//       for (int i=0; i < n; i++) {
// 		    res_vect = fibo_vect(i);
// 	    }
//       ta=clock();
//       printf ("vect : %ld \t",(int) ta-td);
//       // Temps logarithmique
//       td = clock();
//       for (int i=0; i < n; i++) {
// 		    res_log = fibo_log(i);
// 	    }
//       ta = clock();
//       printf ("log : %ld \t",(int) ta-td);
//       // Temps mémorisation
//       td = clock();
//       for (int i=0; i < n; i++) {
// 		    res_memo = fib_incr(i);
// 	    }
//       ta = clock();
//       printf ("memo : %ld \t",(int) ta-td);
//       printf("\n");
//   }
// }




