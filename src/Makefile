CFLAGS=-std=c11 -Wall -Wextra -Wduplicated-cond -Wduplicated-branches -Wlogical-op -Wrestrict -Wnull-dereference -Wdouble-promotion -Wconversion -Wsign-conversion -Wshadow -Wformat=2 -g  -Wjump-misses-init -pedantic

carcassonne: main.o board.o file.o misc.o tile.o 
	$(CC) $(CFLAGS) main.o board.o file.o misc.o tile.o -o carcassonne

clean:
	rm *.o
