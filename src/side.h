#ifndef SIDE_H
#define SIDE_H
/** @file side.h */

#include <stdbool.h>

typedef enum {
    COMPL_NOT_SET = 0,
    COMPL_NOT_COMPLETED = -1,
    COMPL_COMPLETED = 1,
} cmpl;

typedef enum direction { NORTH, EAST, SOUTH, WEST } direction;
typedef enum { CASTLE, ROAD, FIELD } element;

typedef struct {
    element type;
    cmpl completion;
} side;

/**
* creates an object of Side
* @param [in] the of a Side
* @return a pointer to an instance of Side
*/
side* side_new(element type);

/**
* creates a default object of Side
* @return a pointer to a default instance of Side
*/
side* side_newDefault(void);

/**
* creates a copy of Side object
* @param [in] Side object to bb copied
* @return a pointer to an new copy of Side
*/
side* side_copy(side* self);

/**
* frees memory occupied by a Sdie object
* @param [in] adress of a pointer to Side obect to be freed
*/
void side_free(side** selfPtr);

/**
* gets the type of a Side 
* @param [in] Side object to be checked
* @return type of a Side object
*/
element side_getType(side* self);

/**
* sets the type of a Side 
* @param [in] Side object to be changed
* @param [in] new type of a Side 
*/
void side_setType(side* self, element type);

/**
* gets the status of Side's completion: 1 - YES, 0 - NOT SET, -1 - NO
* @param [in] Side object to be checeked
* @return status of Side's completion
*/
int side_isCompleted(side* self);

/**
* set the status of Side's completion: 1 - YES, 0 - NOT SET, -1 - NO
* @param [in] Side object to be changed
* @param [in] new type of a Side
*/
void side_setCompletionStatus(side* self, int compl);

/**
* gets the Direction opposive to the given: north/south, west/east
* @param [in] the given Direction
* @return the Direction opposive to the given 
*/
direction direction_getOpposite(direction);

/**
* checks whether two Directions are opposite to each other
* @param [in] the first Direction
* @param [in] the second Direction
* @return true if Directions are opposite
*/
bool direction_areOpposite(direction, direction);

#endif // !SIDE_H
