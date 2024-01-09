

all: sudoku

CC = gcc
CFLAGS = -Wall -Wextra
C11 = -std=c11
CMZONE = -g -fsanitize=address
RM = rm -f
PROGNAME = sudoku sudoku_generateur.txt sudoku_modele.txt sudoku_solve.txt test
RUN = ./sudoku

sudoku: sudoku.c
	$(CC) $(CFLAGS) $(C11) sudoku.c -o sudoku
	$(CC) $(CFLAGS) $(C11) sudoku_test.c -o test
	$ chmod a+x sudoku

win run:
	$ sudoku

unix run:
	$(RUN)

test:
	$ ./test

clean: 
	@$(RM) -r $(PROGNAME)

