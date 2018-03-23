#include <stdio.h>
#include <stdlib.h>

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
