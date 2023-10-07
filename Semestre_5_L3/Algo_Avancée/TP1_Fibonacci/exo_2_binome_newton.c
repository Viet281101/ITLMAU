
#include <stdio.h>
#include <time.h>

// Fonction récursive pour calculer le coefficient binomial (n k)
int binomialRecursive(int n, int k) {
    if (k == 0 || k == n) {
        return 1;
    } else {
        return binomialRecursive(n - 1, k - 1) + binomialRecursive(n - 1, k);
    }
}

// Fonction itérative avec tableau 2D pour calculer les coefficients binomiaux et afficher le triangle de Pascal
void binomialIterative2D(int n) {
    int triangle[n + 1][n + 1];
    
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= i; j++) {
            if (j == 0 || j == i) {
                triangle[i][j] = 1;
            } else {
                triangle[i][j] = triangle[i - 1][j - 1] + triangle[i - 1][j];
            }
            printf("%d ", triangle[i][j]);
        }
        printf("\n");
    }
}

// Fonction itérative avec vecteur pour calculer les coefficients binomiaux et afficher le triangle de Pascal
void binomialIterativeVector(int n) {
    int vector[n + 1];
    
    for (int i = 0; i <= n; i++) {
        vector[i] = 1;
        for (int j = i - 1; j > 0; j--) {
            vector[j] = vector[j - 1] + vector[j];
        }
        for (int j = 0; j <= i; j++) {
            printf("%d ", vector[j]);
        }
        printf("\n");
    }
}

// Fonction pour calculer le coefficient binomial (n k) en utilisant les factorielles
int binomialFactorial(int n, int k) {
    int numerator = 1;
    int denominator = 1;
    
    for (int i = n; i > n - k; i--) {
        numerator *= i;
    }
    
    for (int i = 1; i <= k; i++) {
        denominator *= i;
    }
    
    return numerator / denominator;
}

// Fonction itérative incrémentale pour calculer les coefficients binomiaux
void binomialIncremental(int n) {
    FILE *file = fopen("pascal_triangle.txt", "w");
    
    if (file == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }
    
    int vector[n + 1];
    
    for (int i = 0; i <= n; i++) {
        vector[i] = 1;
        
        for (int j = i - 1; j > 0; j--) {
            vector[j] = vector[j - 1] + vector[j];
        }
        
        for (int j = 0; j <= i; j++) {
            fprintf(file, "%d ", vector[j]);
        }
        
        fprintf(file, "\n");
    }
    
    fclose(file);
}

int main() {
    int n;
    clock_t td, ta;

    printf("\nEntrez la valeur de n : ");
    scanf("%d", &n);
    
    printf("\na) Calcul récursif des coefficients binomiaux :\n");
    td = clock();
    for (int k = 0; k <= n; k++) {
        printf("(%d %d) = %d\n", n, k, binomialRecursive(n, k));
    }
    ta = clock();
    printf("\nrec : %d\n", (int)(ta - td));
    
    printf("\nb) Calcul itératif avec tableau 2D (Triangle de Pascal) :\n");
    td = clock();
    binomialIterative2D(n);
    ta = clock();
    printf("\nite2D : %d\n", (int)(ta - td));
    
    printf("\nc) Calcul itératif avec vecteur (Triangle de Pascal) :\n");
    td = clock();
    binomialIterativeVector(n);
    ta = clock();
    printf("\nvect : %d\n", (int)(ta - td));
    
    printf("\nd) Calcul par les factorielles :\n");
    td = clock();
    for (int k = 0; k <= n; k++) {
        printf("(%d %d) = %d\n", n, k, binomialFactorial(n, k));
    }
    ta = clock();
    printf("\nfact : %d\n", (int)(ta - td));
    
    printf("\ne) Calcul itératif incrémental avec sauvegarde dans un fichier :\n");
    td = clock();
    binomialIncremental(n);
    ta = clock();
    printf("\nincr : %d\n", (int)(ta - td));
    printf("pascal_triangle.txt créé.\n");
    
    return 0;
}