#include "interactive.h"

#include "board.h"
#include "tlist.h"

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

void write_tlist_interactive(sized_tlist* list) {
    char filename[64] = { 0 };
    fputs("enter name to save list as: ", stdout);
    fgets(filename, ARR_LEN(filename), stdin);
    filename[strcspn(filename, "\n")] = '\0';
    tlist_write(list, filename);
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

void write_board_interactive(sized_board* board) {
    char filename[64] = { 0 };
    fputs("enter name to save board as: ", stdout);
    fgets(filename, ARR_LEN(filename), stdin);
    filename[strcspn(filename, "\n")] = '\0';
    board_write(board, filename);
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

void rotate_tile_interactive(tile** t) {
    rotation_t rot;
    while (true) {
        fputs("rotate by: (0) 0 deg, (1) 90 deg, (2) 180 deg, (3) 270 deg: ",
              stdout);
        if (scanf("%d", (int*)&rot) && rot >= 0 && rot <= 3) {
            tile_rotate_amount(rot, *t);
            for (int ch; (ch = getchar()) != EOF && ch != '\n' && ch != '\r';) { ; }
            return;
        }
        for (int ch; (ch = getchar()) != EOF && ch != '\n' && ch != '\r';) { ; }
        fputs("bad input\n", stderr);
    }
}

// zmień x y na h w
// numerowanie od 1 nie 0
// naprawic info o rotacji
// jakaś niezła imba daje rzeczy których nie ma
void place_tile_interactive(sized_board* board, sized_tlist* list, tile** t) {
    if (*t == 0) {
        choose_tile_interactive(list, t);
    }
    size_t h, w;
    while (true) {
        fputs("where to place tile (h w): ", stdout);
        if (scanf("%lu %lu", &h, &w) == 2) {
            for (int ch; (ch = getchar()) != EOF && ch != '\n' && ch != '\r';) { ; }
            if (h > board->size || w > board->size) {
                fputs("out of bounds\n", stderr);
                continue;
            }
            // czy to x y jest dobrze?
            if (can_place_tile(board, *t, h, w)) {
                place_tile(&board->fields[h][w], *t);
                *t = 0;
                return;
            }
            //rotation_t rot;
            //if ((rot = can_place_tile_rotated(board, *t, h, w))) {
            //    fputs("tile can't be placed right now "
            //          "but could be placed if it was rotated by ", stdout);
            //    rotation_print(rot);
            //    putchar('\n');
            //    return;
            //}
            fputs("can't place tile here\n", stderr);
        } else {
            for (int ch; (ch = getchar()) != EOF && ch != '\n' && ch != '\r';) { ; }
            fputs("bad input\n", stderr);
        }
    }
}

typedef enum {
    ACT_GREETING,
    ACT_USAGE,
    ACT_HELP,
    ACT_PRINT_LIST,
    ACT_LOAD_LIST,
    ACT_WRITE_LIST,
    ACT_PRINT_BOARD,
    ACT_LOAD_BOARD,
    ACT_WRITE_BOARD,
    ACT_CHOOSE_TILE,
    ACT_PRINT_TILE,
    ACT_ROTATE_TILE,
    ACT_PRINT_MOVES,
    ACT_PLACE_TILE,
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

    { ACT_WRITE_LIST,   "write list",   "write list to file"                },

    // board printing
    { ACT_PRINT_BOARD,  "print board",  "prints the board"                  },
    { ACT_PRINT_BOARD,  "p b",          "abbrev"                            },

    // loading board file
    { ACT_LOAD_BOARD,   "load board",   "load board file"                   },
    { ACT_LOAD_BOARD,   "l b",          "abbrev"                            },

    { ACT_WRITE_BOARD,  "write board",  "write board to file"               },

    // choosing tile to place
    { ACT_CHOOSE_TILE,  "choose tile",  "choose tile to place"              },
    { ACT_CHOOSE_TILE,  "c t",          "abbrev"                            },

    // print choosen tile
    { ACT_PRINT_TILE,   "print tile",   "print current tile"                },

    { ACT_ROTATE_TILE,  "rotate tile",  "rotate current tile"               },

    // print aviable moves with current tile
    { ACT_PRINT_MOVES,  "print moves",  "print moves aviable"
                                        " with current tile"                },
    { ACT_PRINT_MOVES,  "p m",          "abbrev"                            },

    // ask where to place current tile
    { ACT_PLACE_TILE,   "place tile",   "place choosen tile"                },

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

bool run_prompt(sized_tlist* list, sized_board* board, tile** ctile) {
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
        tlist_print(list);
        break;
    case ACT_LOAD_LIST:
        init_tlist_interactive(list);
        break;
    case ACT_WRITE_LIST:
        write_tlist_interactive(list);
        break;
    case ACT_PRINT_BOARD:
        print_board(board);
        break;
    case ACT_LOAD_BOARD:
        load_board_interactive(board);
        break;
    case ACT_WRITE_BOARD:
        write_board_interactive(board);
        break;
    case ACT_CHOOSE_TILE:
        choose_tile_interactive(list, ctile);
        break;
    case ACT_PRINT_TILE:
        tile_print(*ctile);
        putchar('\n');
        break;
    case ACT_ROTATE_TILE:
        rotate_tile_interactive(ctile);
        break;
    case ACT_PRINT_MOVES:
        print_board_legal_moves(board, *ctile);
        break;
    case ACT_PLACE_TILE:
        place_tile_interactive(board, list, ctile);
        break;
    case ACT_CHNG_PRMPT:
        change_prompt();
        break;
    case ACT_QUIT:
        return false;
    default:
        fputs("unknown option\n", stderr);
    }
    return true;
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

    tile* ctile = 0;

    while (run_prompt(&list, &board, &ctile)) { ; }

    tlist_free(&list);
    board_free(&board);
    tile_free(ctile);
    free(ctile);
}
