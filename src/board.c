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

tile*** board_malloc(size_t size) {
    tile*** board = malloc(sizeof(tile**) * size);
    for (size_t i = 0; i < size; ++i) {
        board[i] = malloc(sizeof(tile*) * size);
        memset(board[i], 0, size);
    }
    return board;
}

void board_free(size_t size, tile*** board) {
    for (size_t i = 0; i < size; ++i) {
        for (size_t j = 0; j < size; ++j) {
            free(board[i][j]);
        }
        free(board[i]);
    }
    free(board);
}

bool can_place_tile(size_t size, const tile*** board,
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
