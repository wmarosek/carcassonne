#include "calculator.h"

#include <stdlib.h>
#include <stdio.h>

static int __completionToStatus(bool isCompleted) {
    if (isCompleted) return 1;
    else return -1;
}

int score(sized_board* board) {
    int score = 0, RS = 0, CS = 0, TS = 0;

    board_t tiles = board->tiles;
    size_t rows = board->size, columns = board->size;

    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < columns; j++) {

            tile* t = tiles[i][j];

            if (!tile_isEmpty(t)) {

                //1st Criteria: Castle
                if (tile_hasCastle(t)) {

                    int castleScore = 0;

                    if (tile_hasShield(t)) {
                        castleScore++;
                    }

                    size_t castleSegments = tile_numOfSegments(t, CASTLE);
                    Direction* sides = tile_getSegments(t, CASTLE, castleSegments);
                    if (castleSegments == 1) {
                        if (castleCompleted(tiles, rows, columns, i, j, sides[0])) {
                            castleScore += 2;
                        }
                        else {
                            castleScore += 1;
                        }
                    }
                    //SPECIAL CASE
                    // when castleSegments==2 - there can be 2 cities: each segment then should be calculated individually
                    else if (castleSegments == 2 && tile_getCenter(t) != CITY) {
                        for (size_t k = 0; k < castleSegments; k++) {
                            if (castleCompleted(tiles, rows, columns, i, j, sides[k])) {
                                castleScore += 2;
                            }
                            else {
                                castleScore += 1;
                            }
                        }
                    }
                    else {
                        bool completed = true;
                        for (size_t k = 0; k < castleSegments; k++) {
                            completed &= castleCompleted(tiles, rows, columns, i, j, sides[k]);
                            if (!completed) break; ///
                        }

                        if (completed) {
                            castleScore += 2;
                        }
                        else {
                            castleScore += 1;
                        }

                    }
                    //printf("CITY [%i][%i]: %i\n", i, j, cityScore);
                    score += castleScore;
                    CS += castleScore;
                    tile_freeSegments(&sides);
                }
                // 2nd Criteria: Road
                if (tile_hasRoad(t)) {
                    size_t roadSegments = tile_numOfSegments(t, ROAD);
                    Direction* sides = tile_getSegments(t, ROAD, roadSegments);
                    int roadScore = 0;

                    if(roadSegments == 2) {
                        roadScore += roadScoreForTwo(tiles,rows,columns,i,j, sides);
                    } else {
                        for (size_t k = 0; k < roadSegments; k++) {
                            if (roadCompleted(tiles, rows, columns, i, j, sides[k])) {
                                roadScore += 2;
                            }
                            else {
                                roadScore += 1;
                            }
                        }
                    }
                   
                    //printf("ROAD [%i][%i]: %i\n", i, j, roadScore);
                    score += roadScore;
                    RS += roadScore;
                    tile_freeSegments(&sides);
                }

                // 3rd Criteria: Chapel
                if (tile_hasTemple(t)) {
                    int templeScore = 0;
                    templeScore += (1 + tile_numOfNeighbours(tiles, rows, columns, i, j));
                    score += templeScore;
                    TS += templeScore;
                }
            }
        }
    }

    // clear all incompleted side statuses - in further executions this status may be updated, so it can't be constant
    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < columns; j++) {
            tile* t = tiles[i][j];
            if (!tile_isEmpty(t)) {
                for(int k = 0; k < 4; k++) {
                        tile_setSideCompletion(t,k,0);   
                }
            }
        }
    }
    
    return score;
}


bool castleCompleted(board_t board, int rows, int columns, int i, int j, Direction dir) {
    tile* t = board[i][j];

    int status = Side_isCompleted(tile_getSide(t, dir));
    switch (status) {
    case -1: // side was visited and assigned as an uncompleted
        return false;
    case 1:  // side was visited and assigned as completed
        return true;
    case 0: // side is not visited yet
        break;
    }

    // check new coordinates for movements into others pards of the city
    int in = i, jn = j;
    if (dir == NORTH) {
        if (i <= 0) {
            tile_setSideCompletion(t, dir, -1);
            return false;
        }
        in = i - 1;
    }
    else if (dir == EAST) {
        if (j >= columns - 1) {
            tile_setSideCompletion(t, dir, -1);
            return false;
        }
        jn = j + 1;
    }
    else if (dir == SOUTH) {
        if (i >= rows - 1) {
            tile_setSideCompletion(t, dir, -1);
            return false;
        }
        in = i + 1;
    }
    else if (dir == WEST) {
        if (j <= 0) {
            tile_setSideCompletion(t, dir, -1);
            return false;
        }
        jn = j - 1;
    }

    // list will contain the mentions of all visited city sides in this turn
    List* list = List_new();
    // add current tile to a list of visited files
    Point* pre = Point_new(i,j,dir);
    List_addLast(list, pre/*Point_new(i, j, dir)*/);
    // checking if a tile is a part of completed castle
    bool isCompl = tile_castleCompleted(board, rows, columns, in, jn, dir, list);
    // obtaining the index of completion depending on the status of completion
    int res = __completionToStatus(isCompl);
    // obtaining the size of a list of visited sides
    int size = List_getSize(list);


    for (int k = 0; k < size; k++) {
        Point* p = List_getPoint(list, k);
        tile* self = board[Point_getRow(p)][Point_getColumn(p)];
        //printf("[%i][%i]: %i \n", Point_getRow(p), Point_getColumn(p), Point_getSide(p));
        // assigning the index of completion to the visited side
        tile_setSideCompletion(self, Point_getSide(p), res);
    }

    List_free(&list);
    return isCompl;
}

bool tile_castleCompleted(board_t board, int rows, int columns, int i, int j, Direction dir, List* stack) {
    tile* t = board[i][j];

    if (tile_isEmpty(t)) { // if tile is free(empty) - means the side of a calling tile is open & city is not completed
        return false;
    }

    // if the status of the side is already stated -> no use of further investigation
    switch (tile_getSideCompletion(t, Direction_getOpposite(dir))) {
    case -1:
        return false;
    case 1:
        return true;
    }

    // adding a tile to a list of visited tiles (later every side of every tile from list will have the indicator of true/false completion
    List_addLast(stack, Point_new(i, j, Direction_getOpposite(dir)));

    // get number of city segments of a tile
    size_t numOfCastles = tile_numOfSegments(t, CASTLE);

    // simpliest case: 1 city tile automatically means that this is border
    if (numOfCastles == 1) {
        return true;
    }

    // 2 disjoint city segments 
    if (numOfCastles == 2 && tile_getCenter(t) != CITY) {
        return true;
    }

    // Cases when we have more than 1 side with castles
    Direction* sides = tile_getSegments(t, CASTLE, numOfCastles);
    bool isCompl = true;
    bool compl = true;
    int in, jn;
    for (size_t k = 0; k < numOfCastles; k++) {
        compl = true;

        // obtaining the coordinates for the next tile to be checked
        switch (sides[k]) {
        case NORTH:
            if (i <= 0) compl = false;          // if open side is board's border => castle is not completed
            else {
                in = i - 1; jn = j; 
            }
            break;
        case EAST:
            if (j >= columns - 1) compl = false; // if open side is board's border => castle is not completed
            else {
                in = i; jn = j + 1;
            }
            break;
        case SOUTH:
            if (i >= rows - 1) compl = false; // if open side is board's border => castle is not completed
            else {
                in = i + 1; jn = j; 
            }
            break;
        case WEST:
            if (j <= 0) compl = false; // if open side is board's border => castle is not completed
            else {
                in = i; jn = j - 1;
            }
        }

        //  CASES WHEN NOT TO CHECK THE TILE
        //  1) We've already visited the tile (avoid infinite looping)
        //  2) We've came from this tile (can be recognised when dir(previous direction of movements) is opposite to sides[k] (new direction of movement)
        //  3) We are heading to the initial tile's unvisited side
        if (compl && !List_hasPoint(stack, in, jn, Direction_getOpposite(sides[k])) && !Direction_areOpposite(dir, sides[k]) && compl /*&& !Point_isEqual(List_getPoint(stack,0),in,jn)*/) {
            List_addLast(stack, Point_new(i, j, sides[k]));
            //printf("%i,%i - %i\n", i, j, sides[k]);
            compl = tile_castleCompleted(board, rows, columns, in, jn, sides[k], stack);
        }

        // update the overall status: isCompl by default is true => 
        // --if any side gave false completion - the overall completion status changes immediately
        // --if side gave true completion - the overall completion status remains true
        isCompl &= compl;

        // if already detected open side => city is not completed => break loop + return false
        if (!isCompl) {
            break;
        }
    }
    return isCompl;
}

bool tile_roadCompleted(board_t board, int rows, int columns, int i, int j, Direction dir, List* stack) {
    tile* t = board[i][j];

    if (tile_isEmpty(t)) return false;

    // if the status of the side is already stated -> no use of further investigation
    switch (tile_getSideCompletion(t, Direction_getOpposite(dir))) {
    case -1:
        return false;
    case 1:
        return true;
    }

    // adding a tile to a list of visited tiles (later every side of every tile from list will have the indicator of true/false completion
    List_addLast(stack, Point_new(i, j, Direction_getOpposite(dir)));

    if (tile_hasCrossroads(t) || tile_hasTemple(t) || tile_numOfSegments(t,ROAD)==1) return true;

    int in = i, jn = j;

    if (tile_getSideElement(t,NORTH) == ROAD && i != 0 && dir != SOUTH) {
        in = i - 1; dir = NORTH;
    }
    else if (tile_getSideElement(t,EAST) == ROAD && j != columns - 1 && dir != WEST) {
        jn = j + 1; dir = EAST;
    }
    else if (tile_getSideElement(t,SOUTH) == ROAD && i != rows - 1 && dir != NORTH) {
        in = i + 1; dir = SOUTH;
    }
    else if (tile_getSideElement(t,WEST) == ROAD && j != 0 && dir != EAST) {
        jn = j - 1; dir = WEST;
    } else {
        return false;
    }

    List_addLast(stack, Point_new(i,j,dir));
    return tile_roadCompleted(board,rows,columns, in, jn, dir, stack);
}
/*
bool tile_roadCompleted(board_t board, int rows, int columns, int i, int j, Direction dir) {
    tile* t = board[i][j];

    if (tile_isEmpty(t)) return false;

    if (tile_hasCrossroads(t) || tile_hasTemple(t) || tile_numOfSegments(t,ROAD)==1) return true;

    if (tile_getSideElement(t,NORTH) == ROAD && i != 0 && dir != SOUTH) {
        return tile_roadCompleted(board, rows, columns, i - 1, j, NORTH);
    }
    else if (tile_getSideElement(t,EAST) == ROAD && j != columns - 1 && dir != WEST) {
        return tile_roadCompleted(board, rows, columns, i, j + 1, EAST);
    }
    else if (tile_getSideElement(t,SOUTH) == ROAD && i != rows - 1 && dir != NORTH) {
        return tile_roadCompleted(board, rows, columns, i + 1, j, SOUTH);
    }
    else if (tile_getSideElement(t,WEST) == ROAD && j != 0 && dir != EAST) {
        return tile_roadCompleted(board, rows, columns, i, j - 1, WEST);
    }
    return false;
}*/

int roadScoreForTwo(board_t board, int rows, int columns,int i, int j, Direction* sides) {
    tile* t = board[i][j];
    
    switch(Side_isCompleted(tile_getSide(t,sides[0]))*Side_isCompleted(tile_getSide(t,sides[1]))) {
        case 1:
            return 2;
        case -1:
            return 1;
    }
        
    List* path = List_new();
    bool isCompl = true;
    int in, jn;

    for(size_t k = 0; k < 2; k++) {
        List_addLast(path,Point_new(i,j,sides[k]));
        in = i, jn = j;
    
        if (sides[k] == NORTH) {
            if (i <= 0) {
                isCompl = false;
                continue;
            }
            in = i - 1;
        }
        else if (sides[k] == EAST) {
            if (j >= columns - 1) {
                isCompl = false;
                continue;
            }
            jn = j + 1;
        }
        else if (sides[k] == SOUTH) {
            if (i >= rows - 1) {
                isCompl = false;
                continue;
            }
            in = i + 1;
        }
        else if (sides[k] == WEST) {
            if (j <= 0) {
                isCompl = false;
                continue;
            }
            jn = j - 1;
        }

        isCompl &= tile_roadCompleted(board,rows,columns,in,jn,sides[k],path);
    }
    
    int res = __completionToStatus(isCompl);

    board_setStatuses(board,path,res);

    switch(res) {
        case 1: return 2;
        case -1: return 1;
        default: return 0;
    }
}

void board_setStatuses(board_t board, List* list, int res) {
    if(!list) return;
    
    ListNode* node = List_getNodeAt(list,0);
    ListNode* next = NULL;
    while(node != NULL) {
        Point* p = ListNode_getPoint(node);
        tile* self = board[Point_getRow(p)][Point_getColumn(p)];
        tile_setSideCompletion(self, Point_getSide(p), res);
        
        next = ListNode_getNext(node);
        ListNode_free(&node);
        node = next;
    }

    free(list);
}

bool roadCompleted(board_t board, int rows, int columns, int i, int j, Direction dir) {
    tile* t = board[i][j];

    int status = Side_isCompleted(tile_getSide(t,dir));

    switch (status) {
    case -1: // side was visited and assigned as an uncompleted
        return false;
    case 1:  // side was visited and assigned as completed
        return true;
    case 0: // side is not visited yet
        break;
    }

    // check new coordinates for movements into others pards of the city
    int in = i, jn = j;
    
    if (dir == NORTH) {
        if (i <= 0) {
            tile_setSideCompletion(t, dir, -1);
            return false;
        }
        in = i - 1;
    }
    else if (dir == EAST) {
        if (j >= columns - 1) {
            tile_setSideCompletion(t, dir, -1);
            return false;
        }
        jn = j + 1;
    }
    else if (dir == SOUTH) {
        if (i >= rows - 1) {
            tile_setSideCompletion(t, dir, -1);
            return false;
        }
        in = i + 1;
    }
    else if (dir == WEST) {
        if (j <= 0) {
            tile_setSideCompletion(t, dir, -1);
            return false;
        }
        jn = j - 1;
    }

    // list will contain the mentions of all visited city sides in this turn
    List* list = List_new();
    // add current tile to a list of visited files
    Point* pre = Point_new(i,j,dir);
    List_addLast(list, pre/*Point_new(i, j, dir)*/);
    // checking if a tile is a part of completed castle
    bool isCompl = tile_roadCompleted(board,rows,columns, in, jn, dir, list);
    // obtaining the index of completion depending on the status of completion
    int res = __completionToStatus(isCompl);

    board_setStatuses(board,list,res);

    return isCompl;
}


// to calculator
int tile_numOfNeighbours(board_t board, int rows, int columns, int i, int j) {
    int count = 0;
    // checking left column
    if (i > 0) {
        if (!tile_isEmpty(board[i - 1][j])) {
            count++;
        }
        if (j > 0 && !tile_isEmpty(board[i - 1][j - 1])) {
            count++;
        }
        if (j < columns - 1 && !tile_isEmpty(board[i - 1][j + 1])) {
            count++;
        }
    }

    // right column
    if (i < rows - 1) {
        if (!tile_isEmpty(board[i + 1][j])) {
            count++;
        }
        if (j > 0 && !tile_isEmpty(board[i + 1][j - 1])) {
            count++;
        }
        if (j < columns - 1 && !tile_isEmpty(board[i + 1][j + 1])) {
            count++;
        }
    }

    // central column
    if (j > 0 && !tile_isEmpty(board[i][j - 1])) {
        count++;
    }
    if (j < columns - 1 && !tile_isEmpty(board[i][j + 1])) {
        count++;
    }
    return count;
}