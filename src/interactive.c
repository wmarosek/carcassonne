#include "interactive.h"

#include "board.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void greeting() {
    puts("hello player!\n"
         "welcome to a simple carcassonne based game!\n"
         "for usage run: carcassonne help\n"
         "for help type '?'\n");
}

void usage() {
    puts("usage: carcassonne [tiles-list-file] [board-file]\n"
         "tiles-list-file and board-file should be flies in current directory\n"
         "if both tiles-list-file and board-file specified run in auto mode\n"
         "if only tiles-list given use list specified in interactive mode\n"
         "if none file specified use default tile list for interactive mode\n");
}

void help() {
    puts("aviable commands:\n"
         "greeting: greats player\n"
         "usage: prints usage\n"
         "?: prints this message\n"
         "list: prints tile list\n"
         "quit: quits the game\n");
}

size_t initialize_tile_list_interactive(tile_list_t* p_list) {
    free(*p_list);
    *p_list = 0;
    char name[64] = { 0 };
    fputs("enter name of a file containing tile list: ", stdout);
    scanf("%s", name);
    return initialize_tile_list(name, p_list);
}

typedef enum {
    ACT_GREETING,
    ACT_USAGE,
    ACT_HELP,
    ACT_LIST,
    ACT_QUIT,
    ACT_LOAD,
    ACT_UNKNOWN
} action;

action prompt() {
    fputs("> ", stdout);
    char input[32] = { 0 };
    scanf("%s", input);
    if (strcmp(input, "greeting") == 0) {
        return ACT_GREETING;
    }
    if (strcmp(input, "usage") == 0) {
        return ACT_USAGE;
    }
    if (strcmp(input, "?") == 0
        || strcmp(input, "help") == 0) {
        return ACT_HELP;
    }
    if (strcmp(input, "list") == 0) {
        return ACT_LIST;
    }
    if (strcmp(input, "load") == 0) {
        return ACT_LOAD;
    }
    if (strcmp(input, "quit") == 0) {
        return ACT_QUIT;
    }
    return ACT_UNKNOWN;
}

void run_interactive(tile_list_t* tile_list, size_t list_len) {
    while (true) {
        switch(prompt()) {
        case ACT_GREETING: greeting(); break;
        case ACT_USAGE: usage(); break;
        case ACT_HELP: help(); break;
        case ACT_LIST: print_tile_list(*tile_list, list_len); break;
        case ACT_LOAD:
            initialize_tile_list_interactive(tile_list);
            break;
        case ACT_QUIT: return;
        default: fputs("unknown option\n", stderr);
        }
    }
}
