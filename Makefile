CC=g++ -Wall

CFLAGS= -std=c++11 -c

# this target will compile all the files
all: test

test: Session.o main.o
	$(CC) -std=c++11 main.o Session.o -o test

Session.o: Session.cpp
	$(CC) $(CFLAGS) Session.cpp

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp

clean:
	rm -rf *.o test
