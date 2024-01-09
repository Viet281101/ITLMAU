CC=g++ -Wall -Wextra -g -fsanitize=address -std=c++17

test : test-intreliee2
	./test-intreliee2
	echo "OK"

test-intreliee2 : test-intreliee2.cpp intreliee2_t.hpp intreliee2_t.o
	$(CC) test-intreliee2.cpp intreliee2_t.o -o test-intreliee2

intreliee_t2.o : intreliee_t.hpp intreliee_t.cpp
	$(CC) -c intreliee2_t.cpp
clean:
	rm intreliee2_t.o test-intreliee2

