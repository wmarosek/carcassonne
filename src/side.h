#ifndef SIDE_H
#define SIDE_H
/** @file side.h */

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

/**
* creates an object of Side
* @param [in] the of a Side
* @return a pointer to an instance of Side
*/
Side* Side_new(element type);

/**
* creates a default object of Side
* @return a pointer to a default instance of Side
*/
Side* Side_newDefault(void);

/**
* creates a copy of Side object
* @param [in] Side object to bb copied
* @return a pointer to an new copy of Side
*/
Side* Side_copy(Side* self);

/**
* frees memory occupied by a Sdie object
* @param [in] adress of a pointer to Side obect to be freed
*/
void Side_free(Side** selfPtr);

/**
* gets the type of a Side 
* @param [in] Side object to be checked
* @return type of a Side object
*/
element Side_getType(Side* self);

/**
* sets the type of a Side 
* @param [in] Side object to be changed
* @param [in] new type of a Side 
*/
void Side_setType(Side* self, element type);

/**
* gets the status of Side's completion: 1 - YES, 0 - NOT SET, -1 - NO
* @param [in] Side object to be checeked
* @return status of Side's completion
*/
int Side_isCompleted(Side* self);

/**
* set the status of Side's completion: 1 - YES, 0 - NOT SET, -1 - NO
* @param [in] Side object to be changed
* @param [in] new type of a Side
*/
void Side_setCompletionStatus(Side* self, int compl);

/**
* gets the Direction opposive to the given: north/south, west/east
* @param [in] the given Direction
* @return the Direction opposive to the given 
*/
Direction Direction_getOpposite(Direction);

/**
* checks whether two Directions are opposite to each other
* @param [in] the first Direction
* @param [in] the second Direction
* @return true if Directions are opposite
*/
bool Direction_areOpposite(Direction, Direction);

#endif // !SIDE_H
