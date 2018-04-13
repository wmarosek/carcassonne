#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <stdlib.h>
#include <stdio.h>
#include "tile.h"
#include "point.h"
#include "board.h"


int score(board_t board, int rows, int columns);

bool tile_roadCompleted(board_t board, int rows, int columns, int i, int j, Direction dir);

bool roadCompleted(board_t board, int rows, int columns, int i, int j, Direction dir);

bool tile_castleCompleted(board_t board, int rows, int columns, int i, int j, Direction dir, List* stack);

bool castleCompleted(board_t board, int rows, int columns, int i, int j, Direction dir);

int tile_numOfNeighbours(board_t board, int rows, int columns, int i, int j);

#endif