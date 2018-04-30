#include "board.h"

#include <ctype.h>
#include <stdlib.h>
#include <string.h>

size_t board_get_size_interactive() {
    size_t ret;
    while (true) {
        fputs("input board size: ", stdout);
        if (scanf("%lu", &ret) == 1) {
            // exhaust stdin
            for (int ch; (ch = getchar()) != EOF && ch != '\n' && ch != '\r';) { ; }
            break;
        }
        puts("bad input");
        // exhaust stdin
        for (int ch; (ch = getchar()) != EOF && ch != '\n' && ch != '\r';) { ; }
    }
    return ret;
}

size_t board_get_size(const char* filename) {
    FILE* file;
    if ((file = fopen(filename, "r")) == 0) {
        return false;
    }
    int ch;
    size_t row = 0, col = 0, col_max = 0;
    size_t count = 0;
    while ((ch = getc(file)) != EOF) {
        // increase columns on empty tile
        if (ch == '\t') {
            ++col;
            if (count) {
                fclose(file);
                return 0;
            }
            count = 0;
        }
        // increase rows on newline
        if (ch == '\n') {
            ++row;
            col_max = col > col_max ? col : col_max;
            col = 0;
            if (count) {
                fclose(file);
                return 0;
            }
            count = 0;
        }
        // ignore whitespace
        if (isspace(ch)) {
            continue;
        }
        ++count;
        if (count == 5) {
            count = 0;
            ++col;
        }
    }
    fclose(file);
    return row > col_max ? row : col_max;
}

board_t board_alloc(size_t size) {
    board_t board = malloc(sizeof(tile**) * size);
    for (size_t i = 0; i < size; ++i) {
        board[i] = calloc(size, sizeof(tile*));
    }
    return board;
}

bool board_init(gamemode mode, const char* filename, sized_board* board) {
    if (mode == INTERACTIVE_NO_TILES || mode == INTERACTIVE) {
        board->size = board_get_size_interactive();
    } else {
        // margin
        board->size = board_get_size(filename) + 2;
    }
    board->tiles = board_alloc(board->size);
    if (mode == AUTO && !board_parse(filename, board)) {
        return false;
    }
    return true;
}

sized_board board_init_exit_on_err(gamemode mode, const char* filename) {
    sized_board board;
    if (!board_init(mode, filename, &board)) {
            fprintf(stderr, "error parsing board file: %s\n", filename);
            exit(EXIT_FAILURE);
    }
    return board;
}

void board_free(sized_board* board) {
    for (size_t i = 0; i < board->size; ++i) {
        for (size_t j = 0; j < board->size; ++j) {
            tile_free(board->tiles[i][j]);
            free(board->tiles[i][j]);
        }
        free(board->tiles[i]);
    }
    free(board->tiles);
    board->tiles = 0;
}

bool board_is_empty(const sized_board* board) {
    for (size_t i = 0; i < board->size; ++i) {
        for (size_t j = 0; j < board->size; ++j) {
            if (board->tiles[i][j]) {
                return false;
            }
        }
    }
    return true;
}

bool tile_can_place(const sized_board* board,
                    const tile* t, size_t y, size_t x) {
    // return false on null tile
    if (t == 0) {
        return false;
    }
    if (board_is_empty(board)) {
        return true;
    }
    // if out of bounds return false
    if (y > board->size || x > board->size) {
        return false;
    }
    // return false if target cell is already populated
    if (board->tiles[y][x]) {
        return false;
    }
    // count amount of surrounding tiles
    int count = 0;
    // check if placement is on the edge and if neighbor tile is not null
    if (y != 0 && board->tiles[y - 1][x]) {
        // increase amount of surrounding tiles count
        ++count;
        // check if the types are the same
        if (board->tiles[y - 1][x]->down->type != t->up->type) {
            return false;
        }
    }
    if (y < board->size - 1 && board->tiles[y + 1][x]) {
        ++count;
        if (board->tiles[y + 1][x]->up->type != t->down->type) {
            return false;
        }
    }
    if (x != 0 && board->tiles[y][x - 1]) {
        ++count;
        if (board->tiles[y][x - 1]->right->type != t->left->type) {
            return false;
        }
    }
    if (x < board->size - 1 && board->tiles[y][x + 1]) {
        ++count;
        if (board->tiles[y][x + 1]->left->type != t->right->type) {
            return false;
        }
    }
    // return false if no surrounding tiles
    return count > 0;
}

rotation_t tile_can_place_rotated(const sized_board* board,
                                  const tile* t, size_t y, size_t x) {
    tile temp = { t->up, t->right, t->down, t->left, t->mod };
    for (rotation_t rot = ROT_90; rot <= ROT_270; ++rot) {
        if (tile_can_place(board, tile_rotate_amount(rot, &temp), y, x)) {
            return rot;
        }
    }
    return ROT_NO;
}

void tile_place(tile** place, tile* t) {
    *place = t;
}

// TODO: take margin into consideration
bool board_parse(const char* filename, sized_board* board) {
    FILE* file;
    if ((file = fopen(filename, "r")) == 0) {
        return false;
    }
    int ch;
    char str[5];
    // i: rows, j: columns, count: current tile letter counter
    size_t i = 0, j = 0, count = 0;
    while ((ch = getc(file)) != EOF) {
        // increase columns on empty tile
        if (ch == '\t') {
            ++j;
            if (count != 0) {
                fclose(file);
                return false;
            }
            count = 0;
        }
        // increase rows on newline
        if (ch == '\n') {
            ++i;
            j = 0;
            if (count != 0) {
                fclose(file);
                return false;
            }
            count = 0;
        }
        // out of bounds
        if (i > board->size || j > board->size) {
            fclose(file);
            return false;
        }
        // ignore whitespace
        if (isspace(ch)) {
            continue;
        }
        // generate tile string and parse it, assign correct values to the board
        str[count++] = (char)ch;
        if (count == 5) {
            count = 0;
            tile_alloc_from_str(str, &(board->tiles)[i][j]);
            ++j;
        }
    }
    fclose(file);
    return count == 0;
}

void board_print(const sized_board* board) {
    // pass null tile pointer for can_place_tile to always fail
    board_print_legal_moves(board, 0);
}

void board_print_legal_moves(const sized_board* board, tile* t) {
    // print rows
    for (size_t i = 0; i < board->size; ++i) {
        // print up
        for (size_t j = 0; j < board->size; ++j) {
            if (board->tiles[i][j]) {
                printf("  %c  ", elem_to_char(board->tiles[i][j]->up->type));
            } else {
                fputs("     ", stdout);
            }
            // print separator
            if (j < board->size - 1) {
                putchar('|');
            }
        }
        putchar('\n');
        // print mid
        for (size_t j = 0; j < board->size; ++j) {
            if (board->tiles[i][j]) {
                printf(" %c%c%c ",
                       elem_to_char(board->tiles[i][j]->left->type),
                       mod_to_char(board->tiles[i][j]->mod),
                       elem_to_char(board->tiles[i][j]->right->type));
            } else {
                printf("  %c  ", tile_can_place(board, t, i, j) ? 'x' : ' ');
            }
            if (j < board->size - 1) {
                putchar('|');
            }
        }
        putchar('\n');
        // print down
        for (size_t j = 0; j < board->size; ++j) {
            if (board->tiles[i][j]) {
                printf("  %c  ", elem_to_char(board->tiles[i][j]->down->type));
            } else {
                fputs("     ", stdout);
            }
            if (j < board->size - 1) {
                putchar('|');
            }
        }
        putchar('\n');
        // print separator
        if (i < board->size - 1) {
            for (size_t j = 1; j < board->size * 6; ++j) {
                putchar(j % 6 ? '-' : '+');
            }
        }
        putchar('\n');
    }
}

bool board_write(const sized_board* board, const char* filename) {
    FILE* file;
    if ((file = fopen(filename, "w")) == 0) {
        return false;
    }
    char str[5];
    for (size_t i = 0; i < board->size; ++i) {
        for (size_t j = 0; j < board->size; ++j) {
            fprintf(file,
                    "%s ",
                    tile_to_str(board->tiles[i][j], str));
        }
        fprintf(file, "\n");
    }
    fclose(file);
    return true;
}
