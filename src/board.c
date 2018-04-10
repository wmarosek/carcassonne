#include "board.h"

#include <ctype.h>
#include <stdlib.h>
#include <string.h>

size_t get_board_size() {
    fputs("input board size: ", stdout);
    size_t ret;
    scanf("%zu", &ret);
    return ret;
}

board_t board_malloc(size_t size) {
    board_t board = malloc(sizeof(tile**) * size);
    for (size_t i = 0; i < size; ++i) {
        board[i] = malloc(sizeof(tile*) * size);
        memset(board[i], 0, sizeof(tile*) * size);
    }
    return board;
}

void board_free(size_t size, board_t board) {
    for (size_t i = 0; i < size; ++i) {
        for (size_t j = 0; j < size; ++j) {
            free(board[i][j]);
        }
        free(board[i]);
    }
    free(board);
}

bool can_place_tile(size_t size, const board_t board,
                    const tile* t, size_t height, size_t width) {
    // if out of bounds return false
    if (height > size || width > size) {
        return false;
    }
    // return false if target cell is already populated
    if (board[height][width]) {
        return false;
    }
    // count amount of surrounding tiles
    int count = 0;
    // check if placement is on the edge and if neighbor tile is not null
    if (height != 0 && board[height - 1][width]) {
        // increase amount of surrounding tiles count
        ++count;
        // check if the types are the same
        if (board[height - 1][width]->down != t->up) {
            return false;
        }
    }
    if (height != size && board[height + 1][width]) {
        ++count;
        if (board[height + 1][width]->up != t->down) {
            return false;
        }
    }
    if (width != 0 && board[height][width - 1]) {
        ++count;
        if (board[height][width - 1]->right != t->left) {
            return false;
        }
    }
    if (width != size && board[height][width + 1]) {
        ++count;
        if (board[height][width + 1]->left != t->right) {
            return false;
        }
    }
    // return false if no surrounding tiles
    return count > 0;
}

void place_tile(tile** place, tile* t) {
    *place = t;
}

bool parse_board(const char* filename, size_t size, board_t* board) {
    FILE* file;
    if ((file = fopen(filename, "r")) == 0) {
        return false;
    }
    int ch;
    char str[5];
    size_t i = 0, j = 0, count = 0;
    while ((ch = getc(file)) != EOF) {
        if (ch == '\t') {
            ++j;
            count = 0;
        }
        if (ch == '\n') {
            ++i;
            j = 0;
            count = 0;
        }
        if (i > size || j > size) {
            return false;
        }
        if (isspace(ch)) {
            continue;
        }
        str[count++] = (char)ch;
        if (count == 5) {
            count = 0;
            make_tile_from_str(str, &(*board)[i][j]);
            ++j;
        }
    }
    fclose(file);
    return count == 0;
}
