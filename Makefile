CFLAGS = -g -Wall -Weffc++ -Wextra -pedantic

run:    
	g++ ${CFLAGS} test.cpp -o test.out

clean:
	rm -rf *.out
	rm -rf *.dSYM
