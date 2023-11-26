
#include <GL/glut.h>

#define BOARD_SIZE 8
#define CELL_SIZE 80

int isValidMove(int board[BOARD_SIZE][BOARD_SIZE], int x, int y, int player);
void makeMove(int board[BOARD_SIZE][BOARD_SIZE], int x, int y, int player);
