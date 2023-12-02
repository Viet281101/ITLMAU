CC      = gcc
CFLAGS  = -std=c11 -pedantic
LDFLAGS =
RM      = rm

SOURCES = $(wildcard src/*.c)
OBJECTS = $(patsubst %.c,%.c.o,$(notdir $(SOURCES)))

EXE     = othello

%.c.o: src/%.c
	$(CC) $(CFLAGS) $(DEVFLAGS)-c $< -o $@

main: CFLAGS += -O3
main: compilation

dev: CFLAGS += -Wall -Wextra -Wshadow -Wcast-align -Wstrict-prototypes
dev: CFLAGS += -fanalyzer -fsanitize=undefined -g -Og
dev: LDFLAGS += -fsanitize=undefined
dev: compilation

compilation: $(OBJECTS)
	$(CC) -o $(EXE) $(OBJECTS) $(LDFLAGS)

all:
	main

clean:
	$(RM) $(OBJECTS) $(EXE)
