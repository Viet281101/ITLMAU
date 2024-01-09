
#include <stdio.h>


int sudoku[9][9];

void solveSudoku(int,int);

int checkrow(int row,int num)
{
	int column;
	for(column=0;column<9;column++)
	    if(sudoku[row][column]==num)
	        return 0 ;
	return 1;
}

int checkcolumn(int column,int num)
{
	int row;
	for(row=0;row<9;row++)
	    if(sudoku[row][column]==num)
	        return 0;
	return 1;
}

int checkgrid(int row,int column,int num)
{
	row=(row/3)*3 ;
	column=(column/3)*3;
	int r,c;
	for(r=0;r<3;r++)
	    for(c=0;c<3;c++)
	         if(sudoku[row+r][column+c]==num)
	            return 0;
	return 1;
}

void navigate(int row,int column)
{
	if(column<8)
	        solveSudoku(row,column+1);
	    else
	       solveSudoku(row+1,0);
}

void display()
{
	FILE *fichier;
	int sudokuTemp[9][9];
	int i, j;

	for(i = 0; i < 9; i++)
		for(j = 0; j < 9; j++)
			sudokuTemp[i][j] = sudoku[i][j];
	
	fichier = fopen("sudoku_solveur.txt", "w");

	if(fichier == NULL){
		red();
		printf("Problème de création de fichier\n");
		reset();
	}

	fprintf(fichier , "LE SUDOKU RÉSOLU :\n");

	for(i = 0; i < 9; i++) {
		for(j = 0; j < 9; j++) {
			if(j == 8)
			 	fprintf(fichier, " %d \n", sudokuTemp[i][j]);
			else 
				fprintf(fichier, " %d ", sudokuTemp[i][j]);
		}
	}
	
	fclose(fichier);

	puts("\nLE SUDOKU RÉSOLU :");

	printf("+--------+--------+--------+\n");
	
	for(i = 0; i < 9; i++) {
		for(j = 0; j < 9; j++) {
			printf(" %d ", sudoku[i][j]);
		}
		printf("\n");
	}

	printf("+--------+--------+--------+\n");
}

void solveSudoku(int row,int column)
{
    if(row>8)
    	display();
    if(sudoku[row][column]!=0)
    	navigate(row,column);
    else
    {
        int ctr;
        for(ctr=1;ctr<=9;ctr++)
        {
	        if((checkrow(row,ctr)==1)&&(checkcolumn(column,ctr)==1)&&(checkgrid(row,column,ctr)==1))
	        {
	            sudoku[row][column]=ctr;
	            navigate(row,column);
	        }
        }
        sudoku[row][column]=0;
    }
}
