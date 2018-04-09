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
 * allocates a board and sets all tiles to empty (null).
 * remeber to free this, you can use {@code board_free} for this
 * @param [in] size size of a board side
 * @return board
 */
tile*** board_malloc(size_t);

/**
 * frees array of tile pointers
 * @param [in] size size of the array
 * @param [in] array of tile pointers
 */
void board_free(size_t, tile***);

/**
 * check if specified tile can be placed in specified place on board.
 * @param [in] size board size
 * @param [in] board tile pointer array
 * @param [in] t tile pointer
 * @param [in] height
 * @param [in] width
 * @return if can place tile
 */
bool can_place_tile(size_t, const tile* [*][*],
                    const tile*, size_t, size_t);

/**
 * place tile in specified location.
 * @param [out] place
 * @param [in] t tile to place
 */
void place_tile(tile**, tile*);

/**
 * assign tile pointers to board array based on specified file
 * @param [in] filename board file name
 * @param [in] size board size
 * @param [in, out] board 2 dimensional array of tile pointers
 * @return success of operation
 */
bool parse_board(const char*, size_t, tile* [*][*]);

/**
 * write board to file.
 * @param [in] filename board file name
 * @param [in] size size of tile list array
 * @param [in] board tile pointer array portraying board
 * @return success of operation
 */
bool write_board(const char*, size_t, const tile* [*][*]);

#endif
