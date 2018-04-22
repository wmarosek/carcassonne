#include "interactive.h"

#include "board.h"
#include "tlist.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARR_LEN(arr) sizeof(arr) / sizeof(*arr)
#define STR_EQ(s1, s2) (strcmp(s1, s2) == 0)

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

void init_tlist_interactive(sized_tlist* list) {
    free(list->tiles);
    list->tiles = 0;
    char name[64] = { 0 };
    while (true) {
        fputs("enter name of a file containing tile list: ", stdout);
        fgets(name, sizeof(name), stdin);
        name[strcspn(name, "\n")] = '\0';
        if (tlist_init(name, list)) {
            return;
        }
        fputs("initializing failed, try again.\n", stderr);
    }
}

void load_board_interactive(sized_board* board) {
    board_free(board);
    board->fields = 0;
    char name[64] = { 0 };
    while (true) {
        fputs("enter name of a file containing board: ", stdout);
        fgets(name, sizeof(name), stdin);
        name[strcspn(name, "\n")] = '\0';
        // mode auto to load board from file
        if (init_board(AUTO, name, board)) {
            return;
        }
        fputs("initializing failed, try again.\n", stderr);
    }
}

tile* choose_tile_interactive(sized_tlist* list, tile** t) {
    tile* temp = *t;
    fputs("choose tile (number): ", stdout);
    size_t choice;
    while (true) {
        scanf("%lu", &choice);
        // exhaust stdin
        for (int ch; (ch = getchar()) != EOF && ch != '\n' && ch != '\r';) { ; }
        if (choice == 0 || choice <= list->len) {
            break;
        }
        puts("choice out of bounds");
    }
    // choose right tile based on user input (numbering from 1 and ignore null pointers)
    for (size_t i = 0, count = 0; i < list->len; ++i) {
        if (list->tiles[i] && ++count == choice) {
            *t = list->tiles[i];
            list->tiles[i] = 0;
        }
    }
    // if current tile is not null put it back on the list
    if (temp) {
        // find empty space
        for (size_t i = 0; i < list->len; ++i) {
            // TODO: if it wont find empty space it will leak memory
            if (list->tiles[i] == 0) {
                list->tiles[i] = temp;
                break;
            }
        }
    }
    return temp;
}

typedef enum {
    ACT_GREETING,
    ACT_USAGE,
    ACT_HELP,
    ACT_PRINT_LIST,
    ACT_LOAD_LIST,
    ACT_PRINT_BOARD,
    ACT_LOAD_BOARD,
    ACT_CHOOSE_TILE,
    ACT_PRINT_MOVES,
    ACT_CHNG_PRMPT,
    ACT_QUIT,
    ACT_UNKNOWN,
} action;

// command enumerator, user command, command description
// if you want to abbrevietions and not have them printed in help command
// put them right after main command
// (only first command with specific enum value is printed)
const struct { action act; const char* cmd; const char* desc; } act_list[] = {
    // greeting
    { ACT_GREETING,     "greeting",     "greets player"                     },
    { ACT_GREETING,     "g",            "abbrev"                            },

    // usage
    { ACT_USAGE,        "usage",        "prints usage"                      },
    { ACT_USAGE,        "u",            "abbrev"                            },

    // help
    { ACT_HELP,         "help",         "prints this message"               },
    { ACT_HELP,         "h",            "abbrev"                            },
    { ACT_HELP,         "?",            "abbrev"                            },

    // list printing
    { ACT_PRINT_LIST,   "print list",   "prints tile list"                  },
    { ACT_PRINT_LIST,   "p l",          "abbrev"                            },

    // loading list file
    { ACT_LOAD_LIST,    "load list",    "load tile list file"               },
    { ACT_LOAD_LIST,    "l l",          "abbrev"                            },

    // board printing
    { ACT_PRINT_BOARD,  "print board",  "prints the board"                  },
    { ACT_PRINT_BOARD,  "p b",          "abbrev"                            },

    // loading board file
    { ACT_LOAD_BOARD,   "load board",   "load board file"                   },
    { ACT_LOAD_BOARD,   "l b",          "abbrev"                            },

    // choosing tile to place
    { ACT_CHOOSE_TILE,  "choose tile",  "choose tile to place"              },
    { ACT_CHOOSE_TILE,  "c t",          "abbrev"                            },

    // print aviable moves with current tile
    { ACT_PRINT_MOVES,  "print moves",  "print moves aviable"
                                        " with current tile"                },
    { ACT_PRINT_MOVES,  "p m",          "abbrev"                            },

    // chnaging prompt text
    { ACT_CHNG_PRMPT,   "prompt",       "change prompt text"                },

    // quiting
    { ACT_QUIT,         "quit",         "quits the game"                    },
    { ACT_QUIT,         "q",            "abbrev"                            },
    { ACT_QUIT,         "exit",         "abbrev"                            },
    { ACT_QUIT,         "e",            "abbrev"                            },
};

void help() {
    for (size_t i = 0; i < ARR_LEN(act_list); ++i) {
        // do not print commands marked as abbreviations
        // prints if desc different than 'abbrev'
        // (strcmp returns 0 if the same)
        if (!STR_EQ(act_list[i].desc, "abbrev")) {
            printf("%s: %s\n", act_list[i].cmd, act_list[i].desc);
        }
    }
}

char prompt[32] = "> ";

void change_prompt() {
    fputs("new prompt: ", stdout);
    fgets(prompt, sizeof(prompt), stdin);
    prompt[strcspn(prompt, "\n")] = '\0';
}

action handle_input() {
    fputs(prompt, stdout);

    char input[32] = { 0 };
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0';

    for (size_t i = 0; i < ARR_LEN(act_list); ++i) {
        if (STR_EQ(input, act_list[i].cmd)) {
            return act_list[i].act;
        }
    }
    return ACT_UNKNOWN;
}

void run_interactive(gamemode mode, const char* list_filename) {
    greeting();
    sized_tlist list;
    if (!tlist_init(list_filename, &list)) {
        init_tlist_interactive(&list);
    }

    sized_board board;
    if (!init_board(mode, 0, &board)) {
        load_board_interactive(&board);
    }

    tile* curr_tile = 0;

    while (true) {
        switch(handle_input()) {
        case ACT_GREETING:
            greeting();
            break;
        case ACT_USAGE:
            usage();
            break;
        case ACT_HELP:
            help();
            break;
        case ACT_PRINT_LIST:
            tlist_print(&list);
            break;
        case ACT_LOAD_LIST:
            init_tlist_interactive(&list);
            break;
        case ACT_PRINT_BOARD:
            print_board(&board);
            break;
        case ACT_LOAD_BOARD:
            load_board_interactive(&board);
            break;
        case ACT_CHOOSE_TILE:
            choose_tile_interactive(&list, &curr_tile);
            break;
        case ACT_PRINT_MOVES:
            print_board_legal_moves(&board, curr_tile);
            break;
        case ACT_CHNG_PRMPT:
            change_prompt();
            break;
        case ACT_QUIT:
            tlist_free(&list);
            board_free(&board);
            tile_free(curr_tile);
            free(curr_tile);
            return;
        default: fputs("unknown option\n", stderr);
        }
    }
}
