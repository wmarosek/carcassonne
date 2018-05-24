#ifndef TILE_H
#define TILE_H
/** @file tile.h */

#include "side.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

/** @addtogroup Tile
* enumerators and struct used to represent a tile
* @{
*/
typedef enum { NONE, SHIELD, TEMPLE, CROSSROASDS, CITY } modifier;
typedef struct {
    Side* up;
    Side* right;
    Side* down;
    Side* left;
    modifier mod;
} tile;
/** @} */

/**
* set tile pointer to valid memory.
* remember to free this
* @param [out] ptr pointer to tile pointer
* @return valid tile pointer
*/
tile* tile_alloc(tile**);

/**
 * convert character to element.
 * @param [in] ch character to convert to element
 * @return element converted from char
 */
element elem_from_char(char);

/**
 * convert character to modifier.
 * @param [in] ch character to convert to modifier
 * @return modifier converted from char
 */
modifier mod_form_char(char);

/**
* set tile values based on supplied string.
* str must be at least 5 cells long
* if tile pointer is NULL only return it
* @param [in] str string length 5 specifying tile
* @param [out] t tile pointer being assigned to
* @return returns tile pointer
*/
tile* tile_from_str(const char[static 5], tile*);

/**
* set tile pointer to valid memory and initialize according to string.
* remember to free this
* @param [in] string 5 cell long string specifying tile
* @param [out] ptr pointer to tile pointer
* @return pointer to initialized tile
*/
tile* tile_alloc_from_str(const char[static 5], tile**);

/**
 * allocate copy of supplied tile.
 * @param [in] orig pointer to tile to copy
 * @return pointer to allocated copied tile
 */
tile* tile_alloc_from_tile(const tile*);

/**
 * frees all Sides, not the tile pointer!
 * @param [in] t tile pointer to free
 */
void tile_free(tile*);

/**
* parse next tile in specified file stream.
* ignores whitespace inside tile specification
* @param [in] file file stream pointer
* @param [out] t tile pointer being assigned to
* @return success of operation, returns false if reaches EOF before parsing full tile
*/
bool tile_parse(FILE*, tile**);

/**
 * convert element to character.
 * @param [in] e element to convert
 * @return char element representation
 */
char elem_to_char(element);

/**
 * convert modifier to character.
 * @param [in] m modifier to convert
 * @return char modifier representation
 */
char mod_to_char(modifier);

/**
* set string based on supplied tile.
* string must be at least 5 cells long, string is not null terminated,
* if string pointer is NULL only return it
* @param [in] t tile pointer specifying string
* @param [out] buff string at least length 5, being assigned to
* @return string representing tile, buff
*/
char* tile_to_str(const tile*, char[static 5]);

/**
* {@code tile_to_str} wrapper, dynamically allocates memory for string.
* remember to free() resulting pointer
* @param [in] t tile being converted
* @return pointer to dynamically allocated string tile representation
*/
char* tile_to_str_alloc(const tile*);

/**
* print single tile.
* wraps around {@code tile_to_str}, no newline
* @param [in] t tile to print
*/
void tile_print(const tile*);

// TODO: not done
/**
* gieve tile a ratign based on current state of a game.
* @param [in] t pointer to tile to be reviewed
* @return number indicating how good a tile is considering state of the game
*/
int tile_rate(const tile*);

// TODO: not done
/**
* find the best tile depeding on the state of a game.
* @param [in] list of aviable tiles
* @param [in] len length of the list
* @param [in] size size of the board
* @param [in] board gameboard
*/
tile tile_choose_best(const tile*, size_t, size_t, const tile***);

/**
* rotate tile clockwise.
* if tile pointer is NULL only return it
* pointer returned for validity checks and function chaining
* @param [in,out] t tile to rotate
* @return rotated tile
*/
tile* tile_rotate(tile*);

typedef enum {
    ROT_NO,
    ROT_90,
    ROT_180,
    ROT_270,
} rotation_t;

/**
 * print rotation amount, eg ROT_90 => 90 deg.
 * @param [in] rot rotation to print
 */
void rotation_print(rotation_t);

/**
 * rotate tile by specified amount.
 * @param [in] rot how much to rotate
 * @param [in,out] t tile poiner to be rotated
 * @return tile pointer to rotated tile
 */
tile* tile_rotate_amount(rotation_t, tile*);

/**
 * check if tile is empty.
 * @param [in] t tile pointer to check if no tile is placed there on the board
 * @return bool if there is tile
 */
bool tile_isEmpty(const tile*);

/**
 * return element of tile in direction.
 * @param [in] t tile pointer
 * @param [in] dir direction of element we want to get
 * @return element of tile in specified direction
 */
element tile_getSideElement(const tile*, Direction);

/**
 * get side in specified directon.
 * @param [in] t tile pointer to get side from
 * @param dir directon
 * @return Side
 */
Side* tile_getSide(const tile*, Direction); 

/**
 * set completition status for tile direction.
 * @param [in] t tile pointer
 * @param [in] dir direction
 * @param [in] status status of completition
 */
void tile_setSideCompletion(const tile*, Direction, int status);

/**
 * get side completition status.
 * @param [in] t tile pointer to get completition status in directions from.
 * @param [in] dir direction
 * @return completition status
 */
int tile_getSideCompletion(const tile*, Direction);

/**
 * get tile modifier.
 * @param [in] t tile pointer
 * @return modifier
 */
modifier tile_getCenter(const tile*);

/**
 * get amount of segments of with element on specified tile.
 * @param [in] t tile pointer
 * @param [in] type element to check amount of
 * @return amount of segments with element on tile
 */
size_t tile_numOfSegments(const tile* self, element);

Direction* tile_getSegments(const tile*, element, size_t);

/**
 * free segments set pointer to null.
 * @param [in,out] selfPtr segments pointer to pointer to free
 */
void tile_freeSegments(Direction**);

/**
 * check if tile has castle.
 * @param [in] t tile pointer
 * @return if tile has castle
 */
bool tile_hasCastle(const tile*);

/**
 * check if tile has road.
 * @param [in] t tile pointer
 * @return if tile has road
 */
bool tile_hasRoad(const tile*);

/**
 * check if tile has temple.
 * @param [in] t tile pointer
 * @return if tile has temple
 */
bool tile_hasTemple(const tile*);

/**
 * check if tile has crossroads.
 * @param [in] t tile pointer
 * @return if tile has crossroads
 */
bool tile_hasCrossroads(const tile*);

/**
 * check if tile has shield.
 * @param [in] t tile pointer
 * @return if tile has shield
 */
bool tile_hasShield(const tile*);

/** 
 * check if tile's opposite sides are similar
 * @param [in] t tile pointer
 * @return if tile is symmetric
 */
bool tile_isSymmetric(const tile*);

/** 
 * check if all tile's sides are similar
 * @param [in] t tile pointer
 * @return if tile is uniform
 */
bool tile_isUniform(const tile*);


#endif
