CC=g++ -Wall

CFLAGS= -std=c++11 -c

# this target will compile all the files
all: start

start: Interval.o Day.o main.o
	$(CC) -std=c++11 main.o Interval.o Day.o -o start

Interval.o: Interval.cpp
	$(CC) $(CFLAGS) Interval.cpp

Day.o: Day.cpp
	$(CC) $(CFLAGS) Day.cpp

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp

clean:
	rm -rf *.o start
