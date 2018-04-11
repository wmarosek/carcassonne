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

size_t initialize_tile_list_interactive(tile_list_t* p_list) {
    free(*p_list);
    *p_list = 0;
    char name[64] = { 0 };
    fputs("enter name of a file containing tile list: ", stdout);
    fgets(name, sizeof(name), stdin);
    int ch;
    // exhaust stdin
    while ((ch = getchar()) != '\n' && ch != EOF) {
        continue;
    }
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

const struct { action act; const char* cmd; const char* desc; } act_list[] = {
    { ACT_GREETING,     "greeting",     "greets player"         },
    { ACT_USAGE,        "usage",        "prints usage"          },
    { ACT_HELP,         "?",            "prints this message"   },
    { ACT_HELP,         "help",         "prints this message"   },
    { ACT_LIST,         "list",         "prints tile list"      },
    { ACT_QUIT,         "quit",         "quits the game"        },
    { ACT_LOAD,         "load",         "load tile list file"   }
};

void help() {
    // handle special case
    puts("prompt: change prompt text");
    for (size_t i = 0; i < sizeof(act_list) / sizeof(*act_list); ++i) {
        printf("%s: %s\n", act_list[i].cmd, act_list[i].desc);
    }
}

char prompt[32] = "> ";

action handle_input() {
    fputs(prompt, stdout);

    char input[32] = { 0 };
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0';

    for (size_t i = 0; i < sizeof(act_list) / sizeof(*act_list); ++i) {
        if (strcmp(input, act_list[i].cmd) == 0) {
            return act_list[i].act;
        }
    }

    // handle special option
    if (strcmp(input, "prompt") == 0) {
        fputs("new prompt: ", stdout);
        fgets(prompt, sizeof(prompt), stdin);
        prompt[strcspn(prompt, "\n")] = '\0';
        return handle_input();
    }

    return ACT_UNKNOWN;
}

void run_interactive(tile_list_t* tile_list, size_t list_len) {
    while (true) {
        switch(handle_input()) {
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
