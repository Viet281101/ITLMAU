
all: droites berstel

CC = gcc
CFLAGS = -Wall -Wextra
CFLAGS_RPCGEN = -Wno-unused-variable -Wno-unused-but-set-variable -Wno-unused-parameter
C11 = -std=c11
CMZONE = -g -fsanitize=address
RM = rm -f
PROGNAME = droites berstel

droites: droites.c
	$(CC) $(CFLAGS) $(CFLAGS_RPCGEN) $(C11) droites.c -o droites

berstel: berstel.c
	$(CC) $(CFLAGS) $(C11) berstel.c -o berstel

clean: 
	@$(RM) -r $(PROGNAME)
