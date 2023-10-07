

all: eco_system

CC = g++
CFLAGS = -Wall -Wextra
CMZONE = -g -fsanitize=address
RM = rm -r
C14 = -std=c++14
PROGS = eco_system projet_ecosystem.cpp Makefile projetEc.pdf
PROGNAME = eco_system
DELPROGS = eco_system

eco_system: projet_ecosystem.cpp
	$(CC) $(CFLAGS) $(C14) projet_ecosystem.cpp -o $(PROGNAME)
	$ chmod a+x eco_system

test:
	./$(PROGNAME)

clean: 
	@$(RM) $(DELPROGS)


