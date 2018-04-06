#include "board.h"

bool can_place_tile(size_t size, tile* board[size][size],
                    tile* t, size_t height, size_t width) {
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
    // check if placement is on the edge and if neighbour tile is not null
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
