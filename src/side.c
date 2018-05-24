#include "side.h"

#include <stdlib.h>

Side* Side_new(element type) {
    Side* self = malloc(sizeof(Side));
    self->type = type;
    self->completion = 0;
    return self;
}

Side* Side_newDefault(void) {
    Side* self = malloc(sizeof(Side));
    self->type = -1;
    self->completion = 0;
    return self;
}

Side* Side_copy(Side* self) {
    Side* copy = Side_newDefault();
    copy->type = self->type;
    copy->completion = self->completion;
    return copy;
}

void Side_free(Side** selfPtr) {
    free(*selfPtr);
    *selfPtr = NULL;
}

element Side_getType(Side* self) {
    return self->type;
}

void Side_setType(Side* self, element type) {
    self->type = type;
}

int Side_isCompleted(Side* self) {
    return self->completion;
}

void Side_setCompletionStatus(Side* self, int compl) {
    self->completion = compl;
}

Direction Direction_getOpposite(Direction dir) {
    switch (dir) {
    case NORTH: return SOUTH;
    case EAST: return WEST;
    case SOUTH: return NORTH;
    case WEST: return EAST;
    }
    return -1;
}

bool Direction_areOpposite(Direction dir1, Direction dir2) {
    return dir1 == Direction_getOpposite(dir2);
}
