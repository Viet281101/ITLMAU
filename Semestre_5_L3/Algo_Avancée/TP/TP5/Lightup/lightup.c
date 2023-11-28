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

void print_board(board b) {
    int i;
    for (i = 0; i < b.rows*(b.cols+1)+1; i++) {
        if (b.game[i] == '!')
            printf("%2c", 'x');
        else if (b.game[i] == '+')
            printf("%2c", '!');
        else if (b.game[i] == ' ')
            printf("%2c", '.');
        else if (b.game[i] == '/')
            printf("%2c", '#');
        else if (b.game[i] == '*')
            printf("%2c", ' ');
        else
            printf("%2c", b.game[i]);
        if (i % b.cols == b.cols-1)
            puts("");
    }
};
board copy_board(board b) {
    board c;
    c.rows=b.rows;
    c.cols=b.cols;
    c.game=malloc((c.rows*(c.cols+1)+1)*sizeof(char));
    int i;
    for (i = 0; i < c.rows*(c.cols+1)+1; i++)
        c.game[i] = b.game[i];
    return c;
};
void print_lights(state s) {
    int i;
    for (i = 0; i < s.nb_light; i++)
        printf("%d ", s.light_pos[i]);
    puts("");
};
void fill_board(board *b,state *s) {
    int i;
    for (i = 0; i < b->rows*(b->cols+1)+1; i++) {
        if (b->game[i] == '!')
            add_light(s,i);
    }
};
void add_light(state *s,int pos) {
    s->nb_light++;
    s->light_pos = realloc(s->light_pos, s->nb_light * sizeof(int));
    s->light_pos[s->nb_light-1] = pos;
};
int check(board *b, state *s) {
    int i;
    for (i = 0; i < s->nb_light; i++) {
        if (!check_light(b,s,s->light_pos[i]))
            return 0;
    }

    return 1;
};
int is_solved(board *b, state *s) {
    int i;
    for (i = 0; i < b->rows*(b->cols+1)+1; i++) {
        if (b->game[i] == ' ' || b->game[i] == '+')
            return 0;
    }
    return 1;
};
int solve(board *b,state *s) {
    int i;
    if (is_solved(b,s)) {
        print_board(*b);
        return 1;
    }
    for (i = 0; i < b->rows*(b->cols+1)+1; i++) {
        if (b->game[i] == ' ') {
            board c = copy_board(*b);
            state t = init_state();
            fill_board(&c,&t);
            add_light(&t,i);
            c.game[i] = '!';
            if (check(&c,&t) && solve(&c,&t))
                return 1;
        }
    }
    return 0;
};

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



