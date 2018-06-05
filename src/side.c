#include "side.h"

#include <stdlib.h>

side* side_new(element type) {
    side* self = malloc(sizeof(side));
    self->type = type;
    self->completion = 0;
    return self;
}

side* side_newDefault(void) {
    side* self = malloc(sizeof(side));
    self->type = -1;
    self->completion = 0;
    return self;
}

side* side_copy(side* self) {
    side* copy = side_newDefault();
    copy->type = self->type;
    copy->completion = self->completion;
    return copy;
}

void side_free(side** selfPtr) {
    free(*selfPtr);
    *selfPtr = NULL;
}

element side_getType(side* self) {
    return self->type;
}

void side_setType(side* self, element type) {
    self->type = type;
}

int side_isCompleted(side* self) {
    return self->completion;
}

void side_setCompletionStatus(side* self, int compl) {
    self->completion = compl;
}

direction direction_getOpposite(direction dir) {
    switch (dir) {
    case NORTH: return SOUTH;
    case EAST: return WEST;
    case SOUTH: return NORTH;
    case WEST: return EAST;
    }
    return -1;
}

bool direction_areOpposite(direction dir1, direction dir2) {
    return dir1 == direction_getOpposite(dir2);
}
