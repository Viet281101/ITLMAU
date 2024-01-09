
all: tp5

CC = gcc
CFLAGS = -Wall -Wextra
C11 = -std=c11
CMZONE = -g -fsanitize=address
RM = rm -f
PROGNAME = tp5

tp5: tp5_arbres_binaires.c
	$(CC) $(CFLAGS) $(C11) tp5_arbres_binaires.c -o tp5

clean: 
	@$(RM) -r $(PROGNAME)
