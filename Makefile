CFLAGS = -lcurses -std=c++11
CC = g++

typings: typings.cpp
	$(CC) $(CFLAGS) typings.cpp -o typings 

clean:
	rm -f *.o typings 
