
#include<stdio.h>
#include<string.h>
#include <stdbool.h>
#define HIGHT 8
#define WIDTH 8

typedef enum Cell {
	Blank,
	Black,
	White,
} Cell;

void getEnableCells(bool, Cell[HIGHT][WIDTH], bool[HIGHT][WIDTH]);
bool existEnableCells(bool[WIDTH][HIGHT]);
bool canPutLine(bool, int[2], int, Cell[HIGHT][WIDTH]);
void add(int[2], int[2]);
bool canPutLineIter(bool, int[2], int, Cell[HIGHT][WIDTH], bool);
bool fillBoard(Cell[HIGHT][WIDTH]);
void finishGame(Cell[HIGHT][WIDTH]);
bool isOneColor(Cell[HIGHT][WIDTH]);
void inputCell(int[2]);
bool canPut(int[2], bool[WIDTH][HIGHT]);
void reverse(bool, int[2], Cell[HIGHT][WIDTH]);
void reverseIter(bool, int[2], int, Cell[WIDTH][HIGHT]);
void displayBoard(Cell[HIGHT][WIDTH]);
Cell getStoneColor(bool);
void selectByAI(int[2], bool[WIDTH][HIGHT]);

int main() {
	Cell board[HIGHT][WIDTH];
	for (int y=0; y < HIGHT; y++) {
		for(int x=0; x < WIDTH ; x++) {
		board[x][y] = Blank;
		}
	}
	board[3][3] = White;
	board[4][4] = White;
	board[3][4] = Black;
	board[4][3] = Black;
	
	displayBoard(board);
	
	bool isFirst = true;
	bool isAI = true;
	if(isFirst) {
		isAI = false;
	}

	while(true) {
		bool enableCells[WIDTH][HIGHT];
		for (int x=0; x<WIDTH; x++) {
		for (int y=0; y<HIGHT; y++) {
			enableCells[x][y] = false; 
		}
		}
		getEnableCells(isFirst, board, enableCells);

		int selectedCell[2] = {-1, -1};
		if(!existEnableCells(enableCells)) {
		if(fillBoard(board)){
			finishGame(board);
			return 0;
		}
		if (isOneColor(board)) {
			finishGame(board);
			return 0;
		}
		printf("passed \n");
		} else {
		if(isAI){
			printf("AI phase\n");
			selectByAI(selectedCell, enableCells); 
		} else {
			printf("human phase\n");
			inputCell(selectedCell);
			//printf("select: %d, %d\n", selectedCell[0], selectedCell[1]);
			if (!canPut(selectedCell, enableCells)) { 
			printf("On ne peux pas le mettre là !!! \n");
			selectedCell[0] = -1;
			selectedCell[1] = -1;
			isAI = !isAI;
			isFirst = !isFirst;
			} 
		}
		}

		reverse(isFirst, selectedCell, board);
		displayBoard(board);
		isAI = !isAI;
		isFirst = !isFirst;
	}

	return 0;
}

void getEnableCells(bool isFirst, Cell board[HIGHT][WIDTH], bool enableCells[WIDTH][HIGHT]) {
	for (int x=0; x<WIDTH; x++) {
		for (int y=0; y<HIGHT; y++) {
		int selectedCell[2] = {x, y};
		for(int i=0; i<8; i++) {
			if (board[x][y] == Blank 
				&& canPutLine(isFirst, selectedCell, i, board)) {
			printf("(%d, %c) ", y+1, x + 'a');
			enableCells[x][y] = true;
			}
		} 
		}
	}
}

bool canPutLine(bool isFirst, int selectedCell[2], int directionIndex, Cell board[HIGHT][WIDTH]) {
	int x = selectedCell[0];
	int y = selectedCell[1];
	return canPutLineIter(isFirst, selectedCell, directionIndex, board, false);
}

/*
 *
 * @param (flag) Réglez sur true et appelez lorsque la pierre adjacente est d'une couleur différente.
 */
bool canPutLineIter(bool isFirst, int selectedCell[2], int directionIndex, Cell board[HIGHT][WIDTH], bool flag) 
{
	int directions[8][2] = {
		{-1,-1}, {0,-1}, {1,-1},
		{-1, 0}, {1, 0},
		{-1,1}, {0,1}, {1,1}
	};
	
	int tmp[2] = {selectedCell[0], selectedCell[1]};
	add(tmp, directions[directionIndex]);
	
	Cell myColor = getStoneColor(isFirst);
	if (tmp[0] <= -1 || tmp[1] <= -1 || tmp[0] > WIDTH || tmp[1] > HIGHT) {
		return false;
	} else if (board[tmp[0]][tmp[1]] == Blank) {
		return false;
	}  

	if (board[tmp[0]][tmp[1]] != myColor && !flag) {
		return canPutLineIter(isFirst, tmp, directionIndex, board, true);
	} else if (board[tmp[0]][tmp[1]] == myColor && !flag) {
		return false;
	} else if (board[tmp[0]][tmp[1]] == myColor && flag) {
		return true;
	}
	return canPutLineIter(isFirst, tmp, directionIndex, board, true);
}

void add(int target[2], int a[2]) {
	target[0] = target[0] + a[0];
	target[1] = target[1] + a[1];
}

bool existEnableCells(bool enableCells[WIDTH][HIGHT]) {
	for (int x=0; x<WIDTH; x++) {
		for (int y=0; y<HIGHT; y++) {
			if (enableCells[x][y]) {
				return true;
			}
		}
	}
	return false;
}

bool fillBoard(Cell board[HIGHT][WIDTH]) {
	for (int y=0; y < HIGHT; y++) {
		for(int x=0; x < WIDTH ; x++) {
			if (board[x][y] == Blank)
				return false;
		}
	}
	return true;
}

void finishGame(Cell board[HIGHT][WIDTH]) {
	int countblack = 0, countwhite = 0;
	for (int y=0; y < HIGHT; y++) {
		for(int x=0; x < WIDTH ; x++) {
		switch (board[x][y]) {
		case Black:
		countblack++;
		break;
		case White:
		countwhite++;
		break;
		default:
		break;
		}
		}
	}
		
	printf("o:%d\n",countwhite);
	printf("x:%d\n",countblack);
	if(countwhite > countblack) {
		printf("winner:o");
	} else if (countwhite < countblack) {
		printf("winner:x");
	} else {
		printf("draw");
	}
}

bool isOneColor(Cell board[HIGHT][WIDTH]) {
	enum Cell color = Blank;
	for (int y=0; y < HIGHT; y++) {
		for(int x=0; x < WIDTH ; x++) {
			if(board[x][y]!=Blank) {
				if(color == Blank) {
					color = board[x][y];
				} else if(board[x][y]!=color) {
					return false;
				}
			}
			if(y == HIGHT-1 && x == WIDTH-1)
				return true;
		}
	}
}

void inputCell(int selectedCell[2]){
	char input[20];
	printf(" Entrez l'emplacement \n input:");
	fgets(input,20,stdin);
	
	char *in;
	
	in = strtok(input, ",");
	selectedCell[1] = atoi(in) - 1;
	
	in = strtok(NULL, ",");
	selectedCell[0] = *in - 'a';

	//printf("intput %d, %d\n", selectedCell[0], selectedCell[1]);
}

bool canPut(int selectedCell[2], bool enableCells[WIDTH][HIGHT]) {
	return enableCells[selectedCell[0]][selectedCell[1]];
}

void reverse(bool isFirst, int selectedCell[2], Cell board[HIGHT][WIDTH]) {
	int x = selectedCell[0], y = selectedCell[1];
	Cell myColor = getStoneColor(isFirst);

	board[x][y] = myColor;
	for (int i=0; i < 8; i++) {
		if (canPutLine(isFirst, selectedCell, i, board)) {
			reverseIter(isFirst, selectedCell, i, board);
		}
	}
}

void reverseIter(bool isFirst, int scanningCell[2], int directionIndex, Cell board[WIDTH][HIGHT]) {
	int directions[8][2] = {
		{-1,-1}, {0,-1}, {1,-1},
		{-1, 0}, {1, 0},
		{-1,1}, {0,1}, {1,1}
	};
	
	int tmp[2] = {scanningCell[0], scanningCell[1]};
	add(tmp, directions[directionIndex]);
	
	int x = tmp[0];
	int y = tmp[1];

	Cell myColor = getStoneColor(isFirst);

	if (board[x][y] == myColor || board[x][y] == Blank) {
		return;
	}
	
	board[x][y] = myColor;
	reverseIter(isFirst, tmp, directionIndex, board);
}

void displayBoard(Cell board[HIGHT][WIDTH]) {
	printf("--------------------------\n");
	printf("   ");
	for(int i = 0; i < WIDTH; i++){
		printf("%c ", 'a' + i);
	}
	printf("\n");

	for (int y=0; y < HIGHT; y++) {
		printf(" %d ", y+1);
		for(int x=0; x < WIDTH ; x++) {
		switch (board[x][y]) {
			case Black:
				printf("X ");
			break;
			case White:
				printf("O ");
			break;
			default:
				printf("- ");
			break;
		}
		}
		printf("\n");
	}
}

Cell getStoneColor(bool isFirst) {
	if(isFirst) {
		return Black;
	}
	return White;
}

void selectByAI(int selectedCell[2], bool enableCells[WIDTH][HIGHT]) {
	for (int y=0; y < HIGHT; y++) {
		for(int x=0; x < WIDTH ; x++) {
			if(enableCells[x][y]) {
				selectedCell[0] = x;
				selectedCell[1] = y;
			}
		}
	}
}

