
#include <stdio.h>



void triBulle(int taille, int* T) {
	int echangeFait=1;
	int i, temp;
	while(echangeFait) {
		echangeFait=0;
		for(i=0;i<taille-1;i++)
			if(T[i+1] < T[i]) { // ici comparaison
				// echange(T+i,T+i+1);
				temp = T[i];
				T[i] = T[i+1];
				T[i+1] = temp;
				echangeFait = 1;
			}
	}
}



void swap(int* xp, int* yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}
 
// A function to implement bubble sort
void bubbleSort(int n, int arr[])
{
    int i, j;
    for (i = 0; i < n - 1; i++)
 
        // Last i elements are already in place
        for (j = 0; j < n - i - 1; j++)
            if (arr[j] > arr[j + 1])
                swap(&arr[j], &arr[j + 1]);
}


int main(void)
{
	
	return 0;
}



