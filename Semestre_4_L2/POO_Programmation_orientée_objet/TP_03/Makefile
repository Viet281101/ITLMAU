
all: tp4

CC = g++
CFLAGS = -Wall -Wextra
C17 = -std=c++17
CMZONE = -g -fsanitize=address
RM = rm -f
PROGNAME = tp4
PROGDEL = exo1 exo2 exo3 exo4
RUN_1 = ./exo1
RUN_2 = ./exo2
RUN_3 = ./exo3
RUN_4 = ./exo4

tp4:
	$(CC) $(CFLAGS) $(C11) exo1.cpp -o exo1
	$(CC) $(CFLAGS) $(C11) exo2.cpp -o exo2
	$(CC) $(CFLAGS) $(C11) exo3.cpp -o exo3
	$(CC) $(CFLAGS) $(C11) exo4.cpp -o exo4
	chmod a+x tp4

win run:
	tp4

unix run:
	$(RUN_1)
	$(RUN_2)
	$(RUN_3)
	$(RUN_4)

test:
	./exo1
	./exo2

dist: clean
	zip -r $(PROGNAME).zip

clean: 
	@$(RM) -r $(PROGDEL)

