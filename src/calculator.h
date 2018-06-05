#ifndef CALCULATOR_H
#define CALCULATOR_H

#include "tile.h"
#include "point.h"
#include "board.h"

#include <stdlib.h>
#include <stdio.h>


int score(sized_board* board);

int roadScoreForTwo(board_t board, int rows, int columns,int i, int j, direction* sides);

bool tile_roadCompleted(board_t board, int rows, int columns, int i, int j, direction dir, List* stack);

bool roadCompleted(board_t board, int rows, int columns, int i, int j, direction dir);

bool tile_castleCompleted(board_t board, int rows, int columns, int i, int j, direction dir, List* stack);

bool castleCompleted(board_t board, int rows, int columns, int i, int j, direction dir);

int tile_numOfNeighbours(board_t board, int rows, int columns, int i, int j);

void board_setStatuses(board_t board, List* list, int res);

#endif
