#include "ai.h"
#include <time.h>
#include <limits.h>
#include <math.h>

#define ROTATION_MOVES 4

void ai_makeMove(sized_board* board,sized_tlist* list,move* m) {
    if(m == NULL) {
        puts("No more moves available");
        return;
    }

    tile* t = tlist_eraseAt(list,move_getTileIndex(m));
    tile_rotate_amount(move_getRotation(m),t);
    board->tiles[move_getRow(m)][move_getColumn(m)] = t;
    move_free(&m);
}

move* ai_bruteForce(sized_board* board, sized_tlist* list) {
    bool placed = false;
    int best = INT_MIN, row,column,value,rotations;
    Point* maxPoint = NULL;
    move* bestMove = move_default();

    // get the List of Points for available moves
    List* moves = getAllPossibleMoves(board);

    for(int i = 0; i < List_getSize(moves); i++) {
        Point* p = List_getPoint(moves,i);
        row = Point_getRow(p); column = Point_getColumn(p);
        for(int j = 0; j < list->size; j++) {
            // identify to no. of rotations required
            if(tile_isSymmetric(list->tiles[j])) {
                if(tile_isUniform(list->tiles[j])) {    // if all the sides of a tile are the same
                    rotations = 1;
                } else {                                // if opposite sides are identical
                    rotations = 2;
                }
            } else {
                rotations = 4;
            }

            for(int k = 0; k < rotations; k++) {
                // check if tile is applicable at the point
                if(tile_can_place(board,list->tiles[j],row,column)) {
                    // make move
                    board->tiles[row][column] = list->tiles[j];
                    // evaluate
                    value = score(board);
                    // analyze
                    if(value > best) {
                        move_set(bestMove,row,column,j,k,-1);
                        best = value;    
                    }
                    // undo move
                    board->tiles[row][column] = NULL;
                }
                // rotate tile
                tile_rotate(list->tiles[j]);
            }
            // rotate to the initial state
            tile_rotate_amount(ROTATION_MOVES-rotations,list->tiles[j]);
        }
    }

    // if failed to get any move 
    if(best == INT_MIN) {
        move_free(&bestMove);
        bestMove = NULL;
    }
   
    List_free(&moves);
    return bestMove;
}

List* getAllPossibleMoves(sized_board* board) {
   List* list = List_new();

   if(board_is_empty(board)) {
       // if board is empty - the optimal solution will be to place tile in the middle of the board
       List_addFirst(list,Point_new((board->size)/2,(board->size)/2,0));
   }
   else
        for(size_t i = 0; i < board->size; i++) {
            for(size_t j = 0; j < board->size; j++) {
                if(tile_isEmpty(board->tiles[i][j]) && board_tileHasNeighbour(board,i,j)) {
                    List_addLast(list,Point_new(i,j,0)); 
                }
            }
        }
    return list;
}

List* getMovesForTile(sized_board* board, tile* t) {
    List* list = List_new();
    for(size_t i = 0; i < board->size; i++) {
        for(size_t j = 0; j < board->size; j++) {
            if(tile_can_place(board,t,j,i)) {
                List_addLast(list,Point_new(i,j,0)); 
            }
        }
    }
    return list;
}

int getEmptyCells(sized_board* board) {
    int num = 0;
    for(size_t i = 0; i < board->size; i++) {
        for(size_t j = 0; j < board->size; j++) {
            if(tile_isEmpty(board->tiles[i][j])) num++;
        }
    }
    return num;
}