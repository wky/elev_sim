CC = gcc
CFLAGS = -O1

all : main.o
	$(CC) $(CFLAGS) -o sim_elev main.o

main.o : main.cpp
	$(CC) $(CFLAGS) -c  -o main.o main.cpp

clean :
	rm *.o sim_elev

