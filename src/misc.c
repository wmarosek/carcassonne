#include "misc.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void greeting() {
    puts("hello player!\n"
         "welcome to a simple carcassonne based game!\n"
         "for usage run: carcassonne help\n");
}

void usage() {
    puts("usage: carcassonne [tiles-list-file] [board-file]\n"
         "tiles-list-file and board-file should be flies in current directory\n"
         "if both tiles-list-file and board-file specified run in auto mode\n"
         "if only tiles-list given use list specified in interactive mode\n"
         "if none file specified use default tile list for interactive mode\n");
}

gamemode init(int argc, char* argv[], char** list_file, char** board_file) {
    if (argc > 1 && strcmp(argv[1], "help") == 0) {
        usage();
        exit(EXIT_SUCCESS);
    }

    // argc is always at least 1 since program name is always first argument,
    // if zero additional arguments set mode to INTERACTIVE_NO_TILES,
    // if one set mode to INTERACTIVE,
    // else set to AUTO
    gamemode mode = argc - 1;

    if (mode == INTERACTIVE || mode == AUTO) {
        *list_file = argv[1];
        FILE* temp;
        // check if can open list file in rw mode
        if ((temp = fopen(*list_file, "rw")) == 0) {
            fputs("error opening tiles-list-file\n", stderr);
            exit(EXIT_FAILURE);
        }
        fclose(temp);
    }

    if (mode == AUTO) {
        *board_file = argv[2];
        FILE* temp;
        // check if can open board file in rw mode
        if ((temp = fopen(*board_file, "rw")) == 0) {
            fputs("error opening board-flie\n", stderr);
            exit(EXIT_FAILURE);
        }
        fclose(temp);
    }

    return mode;
}

void run(gamemode mode, char* list, char* board) {
    if (mode == INTERACTIVE_NO_TILES || mode == INTERACTIVE) {
        greeting();
    }
    // actual game logic here
}
