#ifndef AI_H
#define AI_H

#include "move.h"
#include "tile.h"
#include "point.h"
#include "board.h"
#include "tlist.h"
#include "calculator.h"

/**
* Finds the best move by Brute Force Search Algorithm 
* @param [in] game board
* @param [in] list with available tiles
* @return best move
*/
move* ai_bruteForce(sized_board* board, sized_tlist* list);

/**
* Makes the move: takes a tile from the lsit and places it on the board
* @param [in] game board
* @param [in] list with available tiles
* @param [in] the move to be done
*/
void ai_makeMove(sized_board* board, sized_tlist* list, move* m);

/**
* Determines all board's cells available for moves 
* @param [in] game board
* @return list of cells available for moves
*/
List* getAllPossibleMoves(sized_board* board);

/**
* Determines all board's cells available for the tile to be placed
* @param [in] game board
* @param [in] tile to be placed
* @return list of cells available for moves
*/
List* getMovesForTile(sized_board* board, tile* t);

/**
* Determines the number of free cells
* @param [in] game sized_board
* @return number of free cells
*/
int getEmptyCells(sized_board* board);

#endif
