#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct board{
    int rows;
    int cols;
    char* game;
} board;

typedef struct state{
    int nb_light;
    int* light_pos;
} state;

state init_state(){
    state s;
    s.nb_light = 0;
    s.light_pos= malloc(s.nb_light * sizeof(int));
    return s;
}

void print_board(board b);
board copy_board(board b);
void print_lights(state s);
void fill_board(board *b,state *s);
void add_light(state *s,int pos);
int check(board *b, state *s);
int is_solved(board *b, state *s);
int solve(board *b,state *s);

int main(int argc, char *argv[]){
    board b;
    int i,row, col, size;
    char c;
    clock_t td,ta;
    FILE *input = fopen(argv[1], "r");
    if (!input)
        exit(1);
    fscanf(input, "%d %d", &col, &row);
    b.rows=row;
    b.cols=col;
    size=row*(col+1)+1;
    b.game=malloc(size*sizeof(char));
    i=0;
    while ((i<size) && ((c=fgetc(input)) != EOF)){
        b.game[i]=c;
        i++;
    }
    fclose(input);
    state s=init_state();
    // td=clock();
    // solve(&b,&s);
    // ta=clock();
    // printf("Durée de résolution : %d \n \n", (int) (ta-td));
    return 0;
}



