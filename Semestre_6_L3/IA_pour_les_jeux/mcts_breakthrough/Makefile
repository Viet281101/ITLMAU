
CC=g++
CFLAGS=-std=c++11 -Wall -O2
IGN=-Wno-unused-variable -Wno-stringop-truncation

##### BREAKTHROUGH
mcts_player: mybt.h mcts_player.cpp
	$(CC) $(CFLAGS) $(IGN) mcts_player.cpp -o $@

clean:
	rm -r -f mcts_player
