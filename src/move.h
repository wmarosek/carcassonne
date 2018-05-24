#ifndef MOVE_H
#define MOVE_H

#include <stdbool.h>

typedef struct move move;

move* move_default(void);
move* move_new(int row, int col,int index, int rotation);
move* move_newFromScore(int score);
void move_free(move** seflPtr);
int move_getRow(move* self);
int move_getColumn(move* self);
int move_getTileIndex(move* self);
int move_getRotation(move* self);
int move_getScore(move* self);
void move_set(move* self,int row, int col,int index, int rotation, int score);
void move_setPoint(move* self,int row, int col);
void move_setTile(move* self,int index, int rotation);
void move_setScore(move* self, int score);
bool move_isEmpty(move* self);
bool move_isEqual(move* self, move* m);
void move_print(move* self);

#endif