#include "misc.h"

#include <stdlib.h>
#include <string.h>

void greeting() {
    printf("hello player!\n"
           "welcome to a simple carcassonne based game!\n"
           "for usage run: carcassonne help\n");
}

void usage() {
    printf("usage: carcassonne [tiles-list-file] [board-file]\n"
           "tiles-list-file and board-file should be flies in current directory\n"
           "if both tiles-list-file and board-file specified run in auto mode\n"
           "if only tiles-list given use list specified in interactive mode\n"
           "if none file specified use default tile list for interactive mode\n");
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
