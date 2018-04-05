#ifndef TILE_H
#define TILE_H

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

// define type representing single tile
typedef enum { CASTLE, ROAD, FIELD } element;
typedef enum { NONE, SHIELD, TEMPLE } modifier;
typedef struct {
    element up;
    element right;
    element down;
    element left;
    modifier mod;
} tile;

element char_to_element(char);
modifier char_to_modifier(char);
tile* str_to_tile(tile*, char[static 5]);
bool parse_tile(tile*, FILE*);
bool parse_tile_list(tile*, size_t, FILE*); // populate g_tile_list

char element_to_char(element);
char modifier_to_char(modifier);

// probably avoid calling this directly or make sure buff is at least 5 cells long
char* tile_to_str(const tile*, char[static 5]);
// remember to free() result
char* tile_to_str_malloc(const tile*);
void print_tile(const tile*);
void print_tile_list(const tile*, size_t);

bool write_tile_list(const tile*, size_t);

// gameplay
int rate_tile(const tile*);                 // return a tile rating
tile choose_best_tile(const tile*, size_t); // choose best tile from the list based on rating

// rotate clockwise tile supplied by pointer,
// return pointer for checking validity or chaining function calls
// if pointer is null only return it
tile* rotate_tile(tile*);

#endif
