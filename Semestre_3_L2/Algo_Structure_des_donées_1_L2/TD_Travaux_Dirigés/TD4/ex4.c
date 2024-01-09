
/* tri a bulle */

#include <stdio.h>


void bubble_sort(long [], long);


void fusion(int n1, int *t1, int n2, int *t2, int *t){
	// int i;
	if (n1 < 1){
		copie(n2, t, t2);
		return;
	}
	if (n2 < 1){
		copie(n1, t, t1);
		return;
	}
	if (*t1 < *t2){
		*t = *t1;
		fusion(n1 -1, t1 + 1, n2, t2, t + 1);
	}else{
		*t = *t2;
		fusion(n1, t1, n2 - 1, t2 + 1, t + 1);
	}
}


void triFusion(int n, int *tab, int tabT){
	if (n < 2)
		return;
	triFusion(n/2, tab, tabT);
	triFusion(n -n/2, tab + n/2, tabT);
	fusion(n/2, tab, n-n/2, tab + n/2, tabT);
	copie(n, tab, tabT);
}


void copie(int n, int *dest, int *src){
	while (n--){
		*(dest++) = *(src++);
	}
}

int main()
{

	return 0;
}


/*

a chaque niveau appel recursif du tri fusion a effectue O(n) operation pour effectuer la fusion et la copie.
et le nombre de niveau d'appel est de l'odre de O(log²(n)) (1) a chaque niveau on divise n par 2.
(2) la condition d'arret suvient lorsque n = 1 ou 0.
donc on tout effectue O(log²(n)) * O(n)
O(nlog(n)) operation

*/

