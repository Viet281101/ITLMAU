
all: tp4

CC = gcc
CFLAGS = -Wall -Wextra
C11 = -std=c11
CMZONE = -g -fsanitize=address
RM = rm -f
PROGNAME = tp4

tp4: tp4_liste_chainee.c
	$(CC) $(CFLAGS) tp4_liste_chainee.c -o tp4

clean: 
	@$(RM) -r $(PROGNAME) 
