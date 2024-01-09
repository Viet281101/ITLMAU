
#include <stdio.h>


/*
2) O(log²(n)) 	<<	O(n^0,1)   <<   O(n)   <<	O(nlog²(n))
		C 				D 			B				A
*/


/*
Oon : nb operation de Ostap cas moyen = le pire de cas dans les entrer possible
Eon : espace de Ostap dans le pire de cas

Oon = O(c + nO) = O(n)
Eon = O( )

*/
int ostap (int n){
	int s = 0, i;
	for (i = 0; i < n; i++){
		s += i;
	}return s;
}


/*
Ton : nb operationde tonass dans le pire cas
Ten : espace de tonass dans le pire des cas

Ton = O(sqrt(n) _|_ + 1) = O(sqrt(n))
Ten = O(1)


i² = n => i = sqrt(n)
*/
int tonass(int n){
	int s = 0, i;
	for (i = 0; i * i < n; i++){
		s += i;
	}return s;
}


/*
Bon : nb opération de Boulba dans le pire des cas(= cas moyen)
Ben : espace de Boulba dans le pire de cas

Bon = O(G + n²K) = O(n²)
Ten = O(1)
*/
int boulba(int n){
	int s = 0, i;
	for(i = 0; i < n * n; i ++){
		s += i;
	}return s;
}

