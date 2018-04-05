#ifndef TILE_H
#define TILE_H
/** @file tile.h */

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

/** @addtogroup Tile
 * enumerators and struct used to represent a tile
 * @{
 */
typedef enum { CASTLE, ROAD, FIELD } element;
typedef enum { NONE, SHIELD, TEMPLE } modifier;
typedef struct {
    element up;
    element right;
    element down;
    element left;
    modifier mod;
} tile;
/** @} */

element char_to_element(char);
modifier char_to_modifier(char);

/**
 * set tile values based on supplied string.
 * str must be at least 5 cells long
 * if tile pointer is NULL only return it
 * @param str string length 5 specifing tile
 * @param t tile pointer being assigned to
 * @return returns tile pointer
 */
tile* str_to_tile(const char[static 5], tile*);

/**
 * parse next tile in specified file stream.
 * ignores whitespace inside tile specification
 * @param file file stream pointer
 * @param t tile pointer being assigned to
 * @return success of operation, returns false if reaches EOF before parsing full tile
 */
bool parse_tile(FILE*, tile*);

/**
 * assign to tile values to tile array based on specified file.
 * @param file tile list file stream
 * @param list tile array
 * @param len length of array
 * @return success of operation, return false if parse tile fails, list / tile is NULL
 */
bool parse_tile_list(FILE*, tile*, size_t);

char element_to_char(element);
char modifier_to_char(modifier);

/**
 * set string based on supplied tile.
 * string must be at least 5 cells long, string is not null terminated,
 * if string pointer is NULL only return it
 * @param t tile pointer specifing string
 * @param buff string at least length 5, being assigned to
 * @return string representing tile, buff
 */
char* tile_to_str(const tile*, char[static 5]);

/**
 * {@code tile_to_str} wrapper, dynamically allocates memory for string.
 * remember to free() resulting pointer
 * @param t tile being converted
 * @return pointer to dynamically allocated string tile representation
 */
char* tile_to_str_malloc(const tile*);

/**
 * print single tile.
 * wraps around {@code tile_to_str}, no newline
 * @param t tile to print
 */
void print_tile(const tile*);

/**
 * print tile array, tiles are separated by newlines.
 * @param t tile array
 * @param len tile array length
 */
void print_tile_list(const tile*, size_t);

bool write_tile_list(const tile*, size_t);

// gameplay
int rate_tile(const tile*);                 // return a tile rating
tile choose_best_tile(const tile*, size_t); // choose best tile from the list based on rating

/**
 * roatate tile clockwise.
 * if tile pointer is NULL only return it
 * pointer returned for validity checks and function chaining
 * @param t tile to rotate
 * @return roatated tile
 */
tile* rotate_tile(tile*);

#endif
