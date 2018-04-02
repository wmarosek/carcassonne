#include "misc.h"

#include <stdlib.h>
#include <string.h>

void greeting() {
    printf("hello player!\n"
           "welcome to carcassonne game!\n"
           "something something\n");
}

void usage() {
    printf("carcassonne [tiles-list-file] [board-file]\n"
           "auto mode run if both aruments specified, otherwise interactieve\n");
}

gamemode init(int argc, char* argv[], FILE* list, FILE* board) {

    if (argc > 1 && strcmp(argv[1], "help") == 0) {
        usage();
        exit(EXIT_SUCCESS);
    }

    // HACK: 0 args - set INTERACTIVE_NO_TILES, 1 - INTERACTIVE, 2 - AUTO
    gamemode mode = argc - 1;

    // TODO: open files and set file ptrs here
    return mode;
}

void run(gamemode mode, FILE* list, FILE* board) {
    if (mode == INTERACTIVE_NO_TILES || mode == INTERACTIVE) {
        greeting();
    }
    // actual game logic here
}
