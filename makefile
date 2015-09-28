CC = g++
CFLAGS = -g -Wall -I/usr/local/Aria/include
LDFLAGS = -lAria -ldl -lrt -lpthread -L/usr/local/Aria/lib

main: main.o follow.o #goHome.o
	$(CC) $(CFLAGS) -o main main.o follow.o  $(LDFLAGS)

main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp

follow.o: follow.cpp follow.hh
	$(CC) $(CFLAGS) -c follow.cpp

#goHome.o: goHome.cpp goHome.hh
#	$(CC) $(CFLAGS) -c goHome.cpp

clean:
	rm *o main
