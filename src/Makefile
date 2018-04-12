CFLAGS=-std=c11 -Wall -Wextra -Wlogical-op -Wdouble-promotion -Wconversion -Wsign-conversion -Wshadow -Wformat=2 -g  -Wjump-misses-init -pedantic

carcassonne: main.o board.o logic.o interactive.o side.o point.o tile.o calculator.o
	$(CC) $(CFLAGS) main.o board.o logic.o interactive.o side.o point.o tile.o calculator.o -o carcassonne

clean:
	rm *.o
