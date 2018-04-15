#ifndef SIDE_H
#define SIDE_H

#include <stdbool.h>

typedef enum {
    COMPL_NOT_SET = 0,
    COMPL_NOT_COMPLETED = -1,
    COMPL_COMPLETED = 1,
} cmpl;

typedef enum Direction { NORTH, EAST, SOUTH, WEST } Direction;
typedef enum { CASTLE, ROAD, FIELD } element;

typedef struct {
    element type;
    cmpl completion;
} Side;

Side* Side_new(element type);

Side* Side_newDefault(void);

void Side_free(Side** selfPtr);

element Side_getType(Side* self);

void Side_setType(Side* self, element type);

int Side_isCompleted(Side* self);

void Side_setCompletionStatus(Side* self, int compl);

Direction Direction_getOpposite(Direction);

bool Direction_areOpposite(Direction, Direction);

#endif // !SIDE_H
