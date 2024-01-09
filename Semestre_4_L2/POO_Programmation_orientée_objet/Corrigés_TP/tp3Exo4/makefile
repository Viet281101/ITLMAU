CC=g++ -Wall -Wextra -g -fsanitize=address -std=c++17

test : test-intreliee
	./test-intreliee
	echo "OK"

test-intreliee : test-intreliee.cpp intreliee_t.hpp intreliee_t.o
	$(CC) test-intreliee.cpp intreliee_t.o -o test-intreliee

intreliee_t.o : intreliee_t.hpp intreliee_t.cpp
	$(CC) -c intreliee_t.cpp
clean:
	rm intreliee_t.o test-intreliee 

