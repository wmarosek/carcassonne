#include "logic.h"

#include "board.h"
#include "interactive.h"
#include "tile.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void handle_args(int argc, char* argv[]) {
    if (argc < 1) {
        return;
    }

    const struct { const char* arg; void (*func)(); } arg_list[] = {
        { "usage",      usage },
        { "--usage",    usage },
        { "help",       usage },
        { "--help",     usage },
        { "-h",         usage },
    };

    for (int i = 1; i < argc; ++i) {
        for (size_t j = 0; j < sizeof(arg_list) / sizeof(*arg_list); ++j) {
            if (strcmp(argv[i], arg_list[j].arg) == 0) {
                arg_list[j].func();
                exit(EXIT_SUCCESS);
            }
        }
    }
}



#define CHECK_VALID_FILE(file, name)                    \
    FILE* temp;                                         \
    if ((temp = fopen(file, "rw")) == 0) {              \
        fprintf(stderr, "error opening %s\n", name);    \
        exit(EXIT_FAILURE);                             \
    }                                                   \
    fclose(temp);

gamemode init(int argc, char* argv[], char** list_file, char** board_file) {
    handle_args(argc, argv);

    // argc is always at least 1 since program name is always first argument,
    // if zero additional arguments set mode to INTERACTIVE_NO_TILES,
    // if one set mode to INTERACTIVE,
    // else set to AUTO
    gamemode mode = argc - 1;

    if (mode == INTERACTIVE || mode == AUTO) {
        *list_file = argv[1];
        // check if can open list file in rw mode
        CHECK_VALID_FILE(*list_file, "tile-list file")
    }

    if (mode == AUTO) {
        *board_file = argv[2];
        // check if can open list file in rw mode
        CHECK_VALID_FILE(*board_file, "board file")
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
    run_interactive(&tile_list, list_len);
    free(tile_list);
}
