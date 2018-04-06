#ifndef BOARD_H
#define BOARD_H
/** @file board.h */

#include "tile.h"

#include <stdbool.h>
#include <stddef.h>

/**
 * check if specified tile can be placed in specified place on board.
 * @param size board size
 * @param board tile pointer array
 * @param t tile pointer
 * @param height
 * @param width
 * @return if can place tile
 */
bool can_place_tile(size_t, tile*[*][*],
                    tile*, size_t, size_t);

/**
 * place tile in specified location.
 * @param place
 * @param t tile to place
 */
void place_tile(tile**, tile*);

/**
 * assign tile pointers to board array based on specified file
 * @param file board file stream
 * @param board 2 dimensional array of tile pointers
 * @param height board height
 * @param width board width
 * @return success of operation
 */
bool parse_board(FILE*, tile**, size_t, size_t);

/**
 * write board to file.
 * @param file board file stream
 * @param board tile pointer array portraying board
 * @return success of operation
 */
bool write_board(FILE*, const tile**);

#endif
