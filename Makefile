CC = g++
CFLAGS = -O1
OBJS = main.o input.o levels.o logfile.o poisson.o wmanager.o
all : $(OBJS)
	$(CC) $(CFLAGS) -o sim_elev $(OBJS)
clean :
	rm *.o sim_elev

