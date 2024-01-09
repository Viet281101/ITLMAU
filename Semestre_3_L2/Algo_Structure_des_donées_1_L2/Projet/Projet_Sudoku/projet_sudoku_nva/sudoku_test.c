

/*The following program is an implementation of a Sudoku Solver in C.
Sudoku is a 9*9 grid in which each row,each column and each 3*3 grid contains all numbers from 1 to 9 only once.
The program uses backtracking approach to solve the sudoku. There is a recursive function to solve the sudoku.
*/
#include<stdio.h>

int sudoku[9][9];//The array which stores entries for the sudoku

void solvesudoku(int,int);

int checkrow(int row,int num)
{
	//This function checks whether we can put the number(num) in the row(row) of the Sudoku or not
	int column;
	for(column=0;column<9;column++)
	    if(sudoku[row][column]==num)
	        return 0 ;//If the number is found already present at certain location we return zero
	return 1;//If the number is not found anywhere we return 1
}

int checkcolumn(int column,int num)
{
	//This function checks whether we can put the number(num) in the column(column) of the Sudoku or not
	int row;
	for(row=0;row<9;row++)
	    if(sudoku[row][column]==num)
	        return 0;//If the number is found already present at certain location we return zero
	return 1;//If the number is not found anywhere we return 1
}

int checkgrid(int row,int column,int num)
{
	//This function checks whether we can put the number(num) in the 3*3 grid or not
	//We get the starting row and column for the 3*3 grid
	row=(row/3)*3 ;
	column=(column/3)*3;
	int r,c;
	for(r=0;r<3;r++)
	    for(c=0;c<3;c++)
	         if(sudoku[row+r][column+c]==num)
	            return 0;//If the number is found already present at certain location we return zero
	return 1;//If the number is not found anywhere we return 1
}

void navigate(int row,int column)
{
	//Function to move to the next cell in case we have filled one cell
	if(column<8)
	        solvesudoku(row,column+1);
	    else
	       solvesudoku(row+1,0);
}

void display()
{
	//The function to display the solved Sudoku
	int row,column;
	printf("\nTHE SOLVED SUDOKU \n");
	for(row=0;row<9;row++)
	{
		for(column=0;column<9;column++)
			printf("%d ",sudoku[row][column]);
		printf("\n");
	}
}

void solvesudoku(int row,int column)
{
    if(row>8)//If the row number is greater than 8 than we have filled all cells hence we have solved the sudoku
    	display();
    if(sudoku[row][column]!=0)
    	navigate(row,column);//If the value filled at a cell is not zero than it is filled with some value from 0 to 9 hence we move further
    else
    {
        int ctr;//This is a counter to check numbers from 1 to 9 whether the number can be filled in the cell or not
        for(ctr=1;ctr<=9;ctr++)
        {
	        //We check row,column and the grid
	        if((checkrow(row,ctr)==1)&&(checkcolumn(column,ctr)==1)&&(checkgrid(row,column,ctr)==1))
	        {
	            sudoku[row][column]=ctr;
	            navigate(row,column);
	        }
        }
        sudoku[row][column]=0;//No valid number was found so we clean up and return to the caller.
    }
    
}
int main()
{
	int row,column;
	printf("Enter the desired sudoku and enter 0 for unknown entries\n");
	for(row=0;row<9;row++)
		for(column=0;column<9;column++)
			scanf("%d",&sudoku[row][column]);
	solvesudoku(0,0);//We start solving the sudoku.
}
/*A sample run of the program was carried out and the results were as follows:-
1 0 3 4 0 0 7 0 9
0 5 6 0 8 9 0 2 3
0 8 9 1 0 3 4 0 6
2 1 4 0 6 5 0 9 7
3 0 0 8 0 7 0 1 4
8 0 7 0 1 4 0 6 5
0 3 1 0 4 0 9 7 8
6 4 0 9 7 0 5 3 1
0 7 8 0 0 1 0 4 2

THE SOLVED SUDOKU
1 2 3 4 5 6 7 8 9
4 5 6 7 8 9 1 2 3
7 8 9 1 2 3 4 5 6
2 1 4 3 6 5 8 9 7
3 6 5 8 9 7 2 1 4
8 9 7 2 1 4 3 6 5
5 3 1 6 4 2 9 7 8
6 4 2 9 7 8 5 3 1
9 7 8 5 3 1 6 4 2


0 0 3 4 0 0 7 0 9
0 5 6 0 8 9 0 2 3
0 8 9 1 0 3 4 0 6
0 0 4 0 6 5 0 9 7
3 0 0 8 0 7 0 1 4
8 0 7 0 1 4 0 6 5
0 3 1 0 4 0 9 7 8
6 4 0 9 7 0 5 3 1
0 7 8 0 0 1 0 4 2

*/

