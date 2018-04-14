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
    bool shield;
    modifier mod;
    bool isEmpty;
} tile;
/** @} */

typedef tile* tile_list_t;
typedef struct {
    tile_list_t list;
    size_t len;
} sized_tlist;

/**
* set tile pointer to valid memory.
* remember to free this
* @param [out] ptr pointer to tile pointer
* @return valid tile pointer
*/
tile* tile_alloc(tile**);

element char_to_element(char);
modifier char_to_modifier(char);

/**
* set tile values based on supplied string.
* str must be at least 5 cells long
* if tile pointer is NULL only return it
* @param [in] str string length 5 specifying tile
* @param [out] t tile pointer being assigned to
* @return returns tile pointer
*/
tile* str_to_tile(const char[static 5], tile*);

/**
* set tile pointer to valid memory and initialize according to string.
* remember to free this
* @param [in] string 5 cell long string specifying tile
* @param [out] ptr pointer to tile pointer
* @return pointer to initialized tile
*/
tile* tile_alloc_from_str(const char[static 5], tile**);

/**
* parse next tile in specified file stream.
* ignores whitespace inside tile specification
* @param [in] file file stream pointer
* @param [out] t tile pointer being assigned to
* @return success of operation, returns false if reaches EOF before parsing full tile
*/
bool parse_tile(FILE*, tile*);

/**
* assign tile values to tile array based on specified file.
* @param [in] filename tile list file name
* @param [out] list sized_tlist list
* @return success of operation, return false if parse tile fails, list / tile is NULL
*/
bool parse_tile_list(const char*, sized_tlist*);

/**
* reads file to find out how big tile list to allocate.
* @param [in] filename name of tile list file
* @return length the tile list should be
*/
size_t get_tile_list_len(const char*);

/**
* allocates and initializes tile list based on tile list file.
* remeber to free this, if filename is bad program will exit
* @param [in] filename name of the tile list file
* @param [out] list pointer to sized_tlist struct
* @return length of initialized tile list
*/
sized_tlist* init_tile_list(const char*, sized_tlist*);

char element_to_char(element);
char modifier_to_char(modifier);

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
void print_tile(const tile*);

/**
* print tile array, tiles are separated by newlines.
* @param [in] t tile array
* @param [in] len tile array length
*/
void print_tile_list(const sized_tlist*);

// not done
bool write_tile_list(const sized_tlist*);

/**
* gieve tile a ratign based on current state of a game.
* @param [in] t pointer to tile to be reviewed
* @return number indicating how good a tile is considering state of the game
*/
int rate_tile(const tile*);

/**
* find the best tile depeding on the state of a game.
* @param [in] list of aviable tiles
* @param [in] len length of the list
* @param [in] size size of the board
* @param [in] board gameboard
*/
tile choose_best_tile(const tile*, size_t, size_t, const tile***);

/**
* rotate tile clockwise.
* if tile pointer is NULL only return it
* pointer returned for validity checks and function chaining
* @param [in,out] t tile to rotate
* @return rotated tile
*/
tile* rotate_tile(tile*);

bool tile_isEmpty(const tile*);

element tile_getSideElement(const tile*, Direction);

Side* tile_getSide(const tile*, Direction); 

void tile_setSideCompletion(const tile*, Direction, int status);

int tile_getSideCompletion(const tile*, Direction);

modifier tile_getCenter(const tile*);

int tile_numOfSegments(const tile* self, element);

Direction* tile_getSegments(const tile*, element, size_t);

void tile_freeSegments(Direction**);

bool tile_hasCastle(const tile*);

bool tile_hasRoad(const tile*);

bool tile_hasTemple(const tile*);

bool tile_hasCrossroads(const tile*);

bool tile_hasShield(const tile*);
#endif
