#ifndef BOARD_H
#define BOARD_H
/** @file board.h */

#include "tile.h"

#include <stdbool.h>
#include <stddef.h>

/**
 * get size of the game board.
 * @return size of the board
 */
size_t get_board_size();

/**
 * frees array of tile pointers
 * @param size size of the array
 * @param array of tile pointers
 */
void free_board(size_t, tile* [*][*]);

/**
 * check if specified tile can be placed in specified place on board.
 * @param size board size
 * @param board tile pointer array
 * @param t tile pointer
 * @param height
 * @param width
 * @return if can place tile
 */
bool can_place_tile(size_t, const tile* [*][*],
                    const tile*, size_t, size_t);

/**
 * place tile in specified location.
 * @param place
 * @param t tile to place
 */
void place_tile(tile**, tile*);

/**
 * assign tile pointers to board array based on specified file
 * @param filename board file name
 * @param size board size
 * @param board 2 dimensional array of tile pointers
 * @return success of operation
 */
bool parse_board(const char*, size_t, tile* [*][*]);

/**
 * write board to file.
 * @param filename board file name
 * @param board tile pointer array portraying board
 * @param size size of tile list array
 * @return success of operation
 */
bool write_board(const char*, size_t, const tile* [*][*]);

#endif
