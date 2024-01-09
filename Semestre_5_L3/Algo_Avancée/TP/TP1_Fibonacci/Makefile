
all: exo1 exo2

CC = gcc
CFLAGS = -Wall -Wextra
CFLAGS_RPCGEN = -Wno-unused-variable -Wno-unused-but-set-variable -Wno-unused-parameter
C11 = -std=c11
CMZONE = -g -fsanitize=address
RM = rm -f
PROGNAME = exo1 exo2 fib fibo.txt pascal_triangle.txt

exo1: exo_1_algo_fibonacci.c
	$(CC) $(CFLAGS) $(CFLAGS_RPCGEN) $(C11) exo_1_algo_fibonacci.c -o exo1

exo2: exo_2_binome_newton.c
	$(CC) $(CFLAGS) $(C11) exo_2_binome_newton.c -o exo2

clean: 
	@$(RM) -r $(PROGNAME)
