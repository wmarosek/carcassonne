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

FILE* exit_on_bad_file_open(const char* filename, const char* mode, const char* name) {
    FILE* file;
    if ((file = fopen(filename, mode)) == 0) {
        fprintf(stderr, "error opening %s\n", name);
        exit(EXIT_FAILURE);
    }
    return file;
}

void check_valid_file(const char* filename, const char* mode, const char* name) {
    FILE* temp = exit_on_bad_file_open(filename, mode, name);
    fclose(temp);
}

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
        check_valid_file(*list_file, "rw", "tile-list file");
    }

    if (mode == AUTO) {
        *board_file = argv[2];
        // check if can open list file in rw mode
        check_valid_file(*board_file, "rw", "board file");
    }

    return mode;
}

void run(gamemode mode, char* list_filename, char* board_filename) {
    if (mode == INTERACTIVE_NO_TILES) {
        // hardcoded, not very nice, and might not be present
        // maybe have some kind of generating mechanism
        list_filename = "default_tiles";
    }
    if (mode == INTERACTIVE || mode == INTERACTIVE_NO_TILES) {
        run_interactive(mode, list_filename);
    }
}
