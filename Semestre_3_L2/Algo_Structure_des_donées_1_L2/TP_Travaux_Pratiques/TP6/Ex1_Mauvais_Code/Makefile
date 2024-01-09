
all : ex1


CC = gcc
CFLAGS = -Wall -Wextra
C11 = -std=c11
CMZONE = -g -fsanitize=address
RM = rm -f
PROGNAME = ex1

ex1 : ex1_mauvais_code.c
	$(CC) $(CMZONE) ex1_mauvais_code.c -o ex1

clean: 
	@$(RM) -r $(PROGNAME)

