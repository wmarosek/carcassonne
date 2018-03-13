#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum { CASTLE, ROAD, FIELD } element;
typedef struct tile {
    element up;
    element right;
    element down;
    element left;
    bool shield;
    bool temple;
};

typedef enum { INTERACTIVE, AUTO } gamemode;

void greeting(void) {
    printf("hello player!\n"
           "welcome to carcassonne game!\n"
           "something something\n");
}

int main(int argc, char* argv[]) {
    gamemode mode = AUTO;
    if (argc < 2) {
        mode = INTERACTIVE;
        greeting();
    }

    return EXIT_SUCCESS;
}
