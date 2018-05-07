#ifndef BOARD_H
#define BOARD_H
/** @file board.h */

#include "tile.h"

#include "logic.h"

#include <stdbool.h>
#include <stddef.h>

typedef tile*** board_t;
typedef struct {
    board_t tiles;
    size_t size;
} sized_board;

/**
 * get size of the game board interactily.
 * @return size of the board
 */
size_t board_get_size_interactive();

/**
 * get size of the game board traversing trough file.
 * @param fliename name of the board file
 * @return size of the board, (return size of the current board, need to add margin)
 */
size_t board_get_size(const char*);

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
 * @param [out] board sized_board pointer
 * @return success of operation
 */
bool board_init(gamemode, const char*, sized_board*);

/**
 * inits board, exit on error.
 * @param [in] mode game mode
 * @param [in] filename name of the board file
 * @return initialized board
 */
sized_board board_init_exit_on_err(gamemode, const char*);

/**
 * frees array of tile pointers
 * @param [in] board game board pointer
 */
void board_free(sized_board*);

/**
 * check if board has no tiles on it.
 * @param [in] board game board
 * @return if board is empty
 */
bool board_is_empty(const sized_board*);

/**
 * check if specified tile can be placed in specified place on board.
 * @param [in] board pointer to game board
 * @param [in] t tile pointer
 * @param [in] y y coordinate of placement
 * @param [in] x x coordinate of placement
 * @return if can place tile
 */
bool tile_can_place(const sized_board*, const tile*, size_t, size_t);

/**
 * rotation in which tile can be placed in the cell
 * @param [in] board
 * @param [in] tile
 * @param h height at which to check if can place
 * @param w width at which to check
 * @param rotation with which tile can be placed, if tile can't be placed return ROT_NO
 */
rotation_t tile_can_place_rotated(const sized_board*, const tile*, size_t, size_t);

/**
 * place tile in specified location.
 * @param [out] place
 * @param [in] t tile to place
 */
void tile_place(tile**, tile*);

/**
 * assign tile pointers to board array based on specified file
 * @param [in] filename board file name
 * @param [in, out] board game board
 * @return success of operation
 */
bool board_parse(const char*, sized_board*);

/**
 * prints out board.
 * @param board pointer to sized_board to print
 */
void board_print(const sized_board*);

/**
 * prints the board with x on empty cells on which tile specified could be placed.
 * @param [in] board game board pointer
 * @param [in] t tile pointer
 */
void board_print_legal_moves(const sized_board*, tile*);

/**
 * write board to file.
 * @param [in] board tile pointer array portraying board
 * @param [in] filename board file name
 * @return success of operation
 */
bool board_write(const sized_board*, const char*);

/**
 * copy tiles from board src to board dest with offset h height and w width,
 * if dest board had allocated tiles they are not free - memory leak.
 * @param [in] src pointer to source board
 * @param [in] h height offset
 * @param [in] w width offset
 * @param [out] dest pointer to destination board
 */
void board_copy_offsetted(const sized_board*, size_t, size_t, sized_board*);

/**
 * copy tiles from board src to board dest,
 * if dest board had allocated tiles they are not free - memory leak.
 * @param [in] src pointer to source board
 * @param [out] dest pointer to destination board
 */
void board_copy(const sized_board*, sized_board*);

/**
 * move tiles on the board by h height and w width,
 * pointers to original board tiles become invalid.
 * @param [in] h height offset
 * @param [in] w width offset
 * @param [out] board with moved tiles
 */
void board_move(size_t, size_t, sized_board*);

/**
 * resize board,
 * pointers to original board tiles become invalid.
 * @param [in] size new size of the board
 * @param [in, out] board to resize
 */
void board_resize(size_t, sized_board*);

#endif
