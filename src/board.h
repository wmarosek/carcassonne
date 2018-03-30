#ifndef BOARD_H
#define BOARD_H

#include "tile.h"

#include <stdbool.h>
#include <stddef.h>

#define BOARD_SIZE 60
extern tile* g_board[BOARD_SIZE][BOARD_SIZE];

bool can_place_tile(size_t, size_t, tile*);     // check if can place tile
void place_tile(tile**, tile*);                 // place tile in specified space

bool parse_board();                             // read board file, populate board array
bool write_board();                             // write board file

#endif
