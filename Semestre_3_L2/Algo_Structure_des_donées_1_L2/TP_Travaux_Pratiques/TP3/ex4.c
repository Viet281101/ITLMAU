
#include <stdio.h>

void swap(int *a, int *b) {
  int t = *a;
  *a = *b;
  *b = t;
}

int partition(int *tab, int low, int high) {
  int pivot = tab[high];
  int i = (low - 1);

  for (int j = low; j < high; j++) {
    if (tab[j] <= pivot) {
      i++;
      swap(&tab[i], &tab[j]);
    }
  }
  swap(&tab[i + 1], &tab[high]);
  
  return (i + 1);
}

void triRapide(int *tab, int low, int high) {
  if (low < high) {
    int pi = partition(tab, low, high);
    triRapide(tab, low, pi - 1);
    triRapide(tab, pi + 1, high);
  }
}

void printtab(int *tab, int size) {
  for (int i = 0; i < size; ++i) {
    printf("%d  ", tab[i]);
  }
  printf("\n");
}

int main() {
  int data[] = {8, 7, 2, 1, 0, 9, 6};
  
  int n = sizeof(data) / sizeof(data[0]);
  
  printf("Avant trie: \n");
  printtab(data, n);
  
  triRapide(data, 0, n - 1);
  
  printf("Le tableau apres tri rapide: \n");
  printtab(data, n);
}