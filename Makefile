CC = g++
CFLAGS = -O1
OBJS = main.o input.o storage.o log.o level_info.o poisson.o
all : $(OBJS)
	$(CC) $(CFLAGS) -o sim_elev $(OBJS)

clean :
	rm *.o sim_elev

