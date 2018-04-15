#ifndef BOARD_H
#define BOARD_H
/** @file board.h */

#include "tile.h"

#include "logic.h"

#include <stdbool.h>
#include <stddef.h>

typedef tile*** board_t;
typedef struct {
    board_t fields;
    size_t size;
} sized_board;

/**
 * get size of the game board interactily.
 * @return size of the board
 */
size_t get_board_size_interactive();

/**
 * get size of the game board traversing trough file.
 * @param fliename name of the board file
 * @return size of the board, (return size of the current board, need to add margin)
 */
size_t get_board_size(const char*);

/**
 * allocates a board and sets all tiles to empty (null).
 * remeber to free this, you can use {@code board_free} for this
 * @param [in] size size of a board side
 * @return board
 */
board_t board_alloc(size_t);

/**
 * returns struct sized_board, sets size and allocates fields, parses board in auto mode.
 * arguements only used in auto mode
 * @param [in] mode game mode
 * @param [in] filename name of board file
 * @return sized_board structure representing game board
 */
sized_board init_board(gamemode, const char*);

/**
 * frees array of tile pointers
 * @param [in] board game board pointer
 */
void board_free(sized_board*);

/**
 * check if specified tile can be placed in specified place on board.
 * @param [in] board pointer to game board
 * @param [in] t tile pointer
 * @param [in] y y coordinate of placement
 * @param [in] x x coordinate of placement
 * @return if can place tile
 */
bool can_place_tile(sized_board*, const tile*, size_t, size_t);

/**
 * place tile in specified location.
 * @param [out] place
 * @param [in] t tile to place
 */
void place_tile(tile**, tile*);

/**
 * assign tile pointers to board array based on specified file
 * @param [in] filename board file name
 * @param [in, out] board game board
 * @return success of operation
 */
bool parse_board(const char*, sized_board*);

/**
 * prints out board.
 * @param board pointer to sized_board to print
 */
void print_board(sized_board*);

// not done
/**
 * write board to file.
 * @param [in] filename board file name
 * @param [in] size size of tile list array
 * @param [in] board tile pointer array portraying board
 * @return success of operation
 */
bool write_board(const char*, sized_tlist*);

#endif
