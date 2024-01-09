

all: tp5

CC = g++
CFLAGS = -Wall -Wextra
C17 = -std=c++17
CMZONE = -g -fsanitize=address
RM = rm -f
PROGNAME = tp5
PROGDEL = exo1 exo2
RUN_1 = ./exo1
RUN_2 = ./exo2

tp5: tp2.c
	$(CC) $(CFLAGS) $(C11) exo1_vecteur.cpp -o exo1
	$(CC) $(CFLAGS) $(C11) ./exo_2/personne_t.cpp -o exo2
	chmod a+x tp5

win run:
	tp2

unix run:
	$(RUN_1)
	$(RUN_2)

test:
	./exo1
	./exo2

dist: clean
	zip -r $(PROGNAME).zip

clean: 
	@$(RM) -r $(PROGDEL)


