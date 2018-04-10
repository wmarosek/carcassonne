#include "logic.h"
#include "interactive.h"
#include "tile.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    tile_list_t tile_list;
    size_t list_len;
    if (mode == INTERACTIVE_NO_TILES) {
        // hardcoded, not very nice, and might not be present
        // maybe have some kind of generating mechanism
        list_len = initialize_tile_list("default_tiles", &tile_list);
    } else {
        list_len = initialize_tile_list(list, &tile_list);
    }
    print_tile_list(tile_list, list_len);

    free(tile_list);
}
