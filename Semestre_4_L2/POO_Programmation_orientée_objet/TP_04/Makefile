
all: tp4

CC = g++
CFLAGS = -Wall -Wextra
C17 = -std=c++17
CMZONE = -g -fsanitize=address
RM = rm -f
PROGNAME = tp4
PROGDEL = exo1 exo2 exo3 exo4 exo5
RUN_1 = ./exo1
RUN_2 = ./exo2
RUN_3 = ./exo3
RUN_4 = ./exo4
RUN_5 = ./exo5

tp4:
	$(CC) exo_1_echange.cpp -o exo1
	$(CC) exo_2_vecteur_du_plan.cpp -o exo2
	$(CC) exo_3_tableau.cpp -o exo3
	$(CC) exo_4_somme_2.cpp -o exo4
	$(CC) exo_5_acces.cpp -o exo5

winrun:
	tp4

unixrun:
	$(RUN_1)
	$(RUN_2)
	$(RUN_3)
	$(RUN_4)
	$(RUN_5)

test:
	./exo1
	./exo2
	./exo3
	./exo4
	./exo5

clean: 
	@$(RM) -r $(PROGDEL)

