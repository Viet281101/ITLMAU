
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "couleur.h"
#include "solveur.h"

#define TAILLE 9
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wimplicit-function-declaration"

int sudoku[TAILLE][TAILLE];
typedef enum { F, T } check;
int exempleTab[TAILLE][TAILLE] = { 
			{1, 2, 3, 4, 5, 6, 7, 8, 9 },
			{4, 5, 6, 7, 8, 9, 1, 2, 3 },
			{7, 8, 9, 1, 2, 3, 4, 5, 6 },
			{2, 1, 4, 3, 6, 5, 8, 9, 7 },
			{3, 6, 5, 8, 9, 7, 2, 1, 4 },
			{8, 9, 7, 2, 1, 4, 3, 6, 5 },
			{5, 3, 1, 6, 4, 2, 9, 7, 8 },
			{6, 4, 2, 9, 7, 8, 5, 3, 1 },
			{9, 7, 8, 5, 3, 1, 6, 4, 2 } 
		};
int exempleTab_2[TAILLE][TAILLE] = {
			{0, 0, 0, 0, 0, 0, 0, 0, 0 },
			{0, 0, 0, 0, 0, 0, 0, 0, 0 },
			{0, 0, 0, 0, 0, 0, 0, 0, 0 },
			{0, 0, 0, 0, 0, 0, 0, 0, 0 },
			{0, 0, 0, 0, 0, 0, 0, 0, 0 },
			{0, 0, 0, 0, 0, 0, 0, 0, 0 },
			{0, 0, 0, 0, 0, 0, 0, 0, 0 },
			{0, 0, 0, 0, 0, 0, 0, 0, 0 },
			{0, 0, 0, 0, 0, 0, 0, 0, 0 },
}


void initialiser();
void imprimerSudoku();
void entrerSudoku();
void genererFichierImprimerSudoku();
void genererFichierCompletSudoku();
void genererFichierModeleSudoku();
void swapPetitLigne(int ligne_1, int ligne_2);
void swapGrandeLigne(int lgrande_1, int lgrande_2);
void swapPetitColonne(int col_1, int col_2);
void swapGrandColonne(int colgrande_1, int colgrande_2);
void rotationVertical();
void rotationHorizontale();
void swapColonneLigne();
void inverserTab();
void remplacement(int a, int b);
void genererSudoku();


int main(void){

	system("clear");
	char option;
	check tab = F;

	puts("\n");
	puts("////////////////////////////////////////////////////");
	puts("////////////////////// SUDOKU //////////////////////");
	puts("////////////////////////////////////////////////////");

	do {
		puts("\n");
		puts("Saisissez une option:");
		puts("1. Générez le Sudoku (le fichier sera créé automatiquement).");
		puts("2. Solver le Sudoku (le fichier sera créé automatiquement).");
		puts("3. Entrez une forme incomplet sudoku Tableau pour résoudre (automatique).");
		puts("\n--------------");		
		puts("'X' - QUIT\n");
	
		__fpurge(stdin);
		green();
		scanf("%c", &option);
		reset();

		switch(option) {
			case '1':
				// system("clear");
				puts("Générez le sudoku aléatoire:");
				genererSudoku();
				genererFichierModeleSudoku();
				genererFichierImprimerSudoku();
				tab = T;
				break;
			
			case '2':
				if (tab == T){
					puts("LE SUDOKU RÉSOLU :");
					imprimerSudoku();
					genererFichierCompletSudoku();
					tab = F;
				}else{
					system("clear");
					red();
					puts("PAS DE TABLEAU DISPONIBLE POUR RESOUDRE ! ");
					puts("Veuillez d'abord choisir l'option 1 !");
					reset();
				}
				break;
			
			case '3':
				// system("clear");
				puts("Entrez le sudoku souhaité et entrez 0 pour les entrées inconnues:\n");
				entrerSudoku();
				break;

			case 'X':
				return 0;
			case 'x':
				return 0;

			default:
				system("clear");
				red();
				puts("ERREUR: option non valide.\n");
				reset();
				break;
		}

	} while(option != 0);

	return 0;
}


void initialiser(int sudokuTab[9][9]){
	int i, j;
	
	for(i = 0; i < TAILLE; i++) {
		for(j = 0; j < TAILLE; j++)	{
			sudoku[i][j] = sudokuTab[i][j];
		}
	}	
}

void imprimerSudoku(){
	int i, j;

	printf("+--------+--------+--------+\n");
	
	for(i = 0; i < TAILLE; i++) {
		for(j = 0; j < TAILLE; j++) {
			printf(" %d ", sudoku[i][j]);
		}
		printf("\n");
	}

	printf("+--------+--------+--------+\n");
}

void entrerSudoku(){
	int i, j;
	
	for(i=0; i<TAILLE; i++){
		for(j=0; j<TAILLE; j++){
			scanf("%d", &sudoku[i][j]);
		}
	}
	imprimerSudoku();
	solveSudoku(8, 8);
}

void swapPetitLigne(int ligne_1, int ligne_2){
	int j, tempL;

	for(j = 0; j < TAILLE; j++) {
		tempL = sudoku[ligne_1][j];
		
		sudoku[ligne_1][j] = sudoku[ligne_2][j];
		sudoku[ligne_2][j] = tempL;
	}
}

void swapGrandeLigne(int lgrande_1, int lgrande_2){	
	if(lgrande_1 > 2 || lgrande_2 > 2){
		red();
		printf("ERREUR DE GRANDE LIGNE !!!");
		reset();
	}else {
		swapPetitLigne(lgrande_1 * 3, lgrande_2 * 3);
		swapPetitLigne(lgrande_1 * 3 + 1, lgrande_2 * 3 + 1);
		swapPetitLigne(lgrande_1 * 3 + 2, lgrande_2 * 3 + 2);
	}
}

void swapPetitColonne(int col_1, int col_2){
	int i, tempC;	
	
	for(i = 0; i < TAILLE; i++) {
		tempC = sudoku[i][col_1];
		
		sudoku[i][col_1] = sudoku[i][col_2];
		sudoku[i][col_2] = tempC;
	}
}

void swapGrandColonne(int colgrande_1, int colgrande_2){	
	if(colgrande_1 > 2 || colgrande_2 > 2){
		red();
		printf("ERREUR DE GRANDE COLONNE !!!");
		reset();
	}else {
		swapPetitColonne(colgrande_1 * 3, colgrande_2 * 3);
		swapPetitColonne(colgrande_1 * 3 + 1, colgrande_2 * 3 + 1);
		swapPetitColonne(colgrande_1 * 3 + 2, colgrande_2 * 3 + 2);
	}
}

void rotationVertical(){
	int i, j, tempV;
	
	for(i = 0; i < TAILLE; i++)	{
		for(j = 0; j < TAILLE/2; j++) {
			tempV = sudoku[i][j];
			
			sudoku[i][j] = sudoku[i][8 - j];
			sudoku[i][8 - j] = tempV;
		}
	}
}

void rotationHorizontale(){
	int i, j, tempH;
	
	for(i = 0; i < TAILLE/2; i++) {
		for(j = 0; j < TAILLE; j++)	{
			tempH = sudoku[i][j];
			
			sudoku[i][j] = sudoku[8 - i][j];
			sudoku[8 - i][j] = tempH;
		}
	}
}

void swapColonneLigne(){
	int i, j, tempSwapColonneLigne;
	
	for(i = 0; i < TAILLE; i++) {
		for(j = i; j < TAILLE; j++)	{
			tempSwapColonneLigne = sudoku[i][j];
			
			sudoku[i][j] = sudoku[j][i];
			sudoku[j][i] = tempSwapColonneLigne;
		}
	}
}

void inverserTab(){
	int i, j;
	int sudokuTemp[TAILLE][TAILLE];
	
	for(i = 0; i < TAILLE; i++)	{
		for(j = 0; j < TAILLE; j++)	{
			sudokuTemp[i][j] = sudoku[i][j];			
		}
	}
	
	for(i = 0; i < TAILLE; i++)	{
		for(j = 0; j < TAILLE; j++) {
			sudoku[i][j] = sudokuTemp[j][i];
		}
	}
	
}

void inverserTab2(){

	rotationVertical();
	inverserTab();
}

void remplacement(int a, int b){

	int i, j;
	for(i = 0; i < TAILLE; i++){
		for(j = 0; j < TAILLE; j++){
			if(sudoku[i][j] == a) sudoku[i][j] = b;
			
			else if(sudoku[i][j] == b) sudoku[i][j] =a;
		}
	}
}

void genererSudoku(){

	initialiser(exempleTab);
	srand(time(NULL));
	
	int melanger, i, bloc;
	
	for(i = 0; i < 10; i++) {
		
		melanger = rand() % 10;
		bloc = rand() % 3;
		
		switch(melanger) {
		case 0: 
			switch(bloc) {
				case 0:
					swapPetitLigne(rand() % 3, rand() % 3);
					break;
					
				case 1:
					swapPetitLigne((rand() % 3) + 3, (rand() % 3) + 3);
					break;
					
				case 2: 
					swapPetitLigne((rand() % 3) + 6, (rand() % 3) + 6);
					break;
					
			}
			break;
		case 1: 
			swapGrandeLigne((rand() % 3), (rand() % 3));
			break;
			
		case 2: 
			switch(bloc) {
				case 0:
					swapPetitColonne((rand() % 3), (rand() % 3));
					break;
					
				case 1:
					swapPetitColonne((rand() % 3) + 3, (rand() % 3) + 3);
					break;
					
				case 2: 
					swapPetitColonne((rand() % 3) + 6, (rand() % 3) + 6);
					break;
				}
			break;
		case 3: 
			swapGrandColonne((rand() % 3), (rand() % 3));
			break;
			
		case 4: 
			rotationVertical();
			break;
			
		case 5: 
			rotationHorizontale();
			break;
			
		case 6: 
			swapColonneLigne();
			break;
			
		case 7: 
			inverserTab();
			break;
			
		case 8: 
			inverserTab2();
			break;
			
		case 9: 
			remplacement((rand() % 9) + 1, (rand()  % 9)+ 1);
			break;
		}
	}
}

void genererFichierImprimerSudoku(){	
	int i, j, aux = 0;

	char sudokuTemp[TAILLE][TAILLE];

	FILE * fichier_1;
	fichier_1 = fopen("sudoku_modele.txt", "r");

	if(fichier_1 == NULL){
		red();
		printf("Problème de création de fichier\n");
		reset();
	}

	for(i = 0; i < TAILLE; i++)
		for(j = 0; j < TAILLE; j++)
			fscanf(fichier_1, "%c", &sudokuTemp[i][j]);


	for(i = 0; i < TAILLE; i++)	{
		do {
			j = rand() % 9;
			sudokuTemp[i][j] = '0';

			j = rand() % 9;
			sudokuTemp[i][j] = '0';

			j = rand() % 9;
			sudokuTemp[i][j] = '0';

			j = rand() % 9;
			sudokuTemp[i][j] = '0';

			j = rand() % 9;
			sudokuTemp[i][j] = '0';

			j = rand() % 9;
			sudokuTemp[i][j] = '0';

			aux++;
		} while (aux < 5);
	}

	printf("+--------+--------+--------+\n");

	for(i = 0; i < TAILLE; i++) {
		for(j = 0; j < TAILLE; j++) {
			printf(" %c ", sudokuTemp[i][j]);
		}
		printf("\n");
	}

	printf("+--------+--------+--------+\n");

	fclose(fichier_1);

	FILE * fichier_2;
	fichier_2 = fopen("sudoku_generateur.txt", "w");

	if(fichier_2 == NULL){
		red();
		printf("Problème de création de fichier\n");
		reset();
	}

	for(i = 0; i < TAILLE; i++)
		for(j = 0; j < TAILLE; j++) {
			if(j == 8)
			 	fprintf(fichier_2, " %c \n", sudokuTemp[i][j]);
			else 
				fprintf(fichier_2, " %c ", sudokuTemp[i][j]);
		}

	fclose(fichier_2);
}

void genererFichierCompletSudoku(){
	FILE *fichier;
	int sudokuTemp[TAILLE][TAILLE];
	int i, j;

	for(i = 0; i < TAILLE; i++)
		for(j = 0; j < TAILLE; j++)
			sudokuTemp[i][j] = sudoku[i][j];
	
	fichier = fopen("sudoku_solve.txt", "w");

	if(fichier == NULL){
		red();
		printf("Problème de création de fichier\n");
		reset();
	}

	fprintf(fichier , "LE SUDOKU RÉSOLU :\n");

	for(i = 0; i < TAILLE; i++) {
		for(j = 0; j < TAILLE; j++) {
			if(j == 8)
			 	fprintf(fichier, " %d \n", sudokuTemp[i][j]);
			else 
				fprintf(fichier, " %d ", sudokuTemp[i][j]);
		}
	}
	
	fclose(fichier);
}

void genererFichierModeleSudoku(){
	FILE * fichier;
	int sudokuTemp[TAILLE][TAILLE];
	int i, j;

	for(i = 0; i < TAILLE; i++)
		for(j = 0; j < TAILLE; j++)
			sudokuTemp[i][j] = sudoku[i][j];
	
	fichier = fopen("sudoku_modele.txt", "w");

	if(fichier == NULL){
		red();
		printf("Problème de création de fichier\n");
		reset();
	}
	
	for(i = 0; i < TAILLE; i++){
		for(j = 0; j < TAILLE; j++){
			fprintf(fichier, "%d", sudokuTemp[i][j]);
		}
	}
	
	fclose(fichier);	
}

