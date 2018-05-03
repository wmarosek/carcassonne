#ifndef TLIST_H
#define TLIST_H
/** @file tlist.h */

#include "tile.h"

#include <stdbool.h>

typedef tile** tlist_t;
typedef struct {
    tlist_t tiles;
    size_t size;
} sized_tlist;

/**
* assign tile values to tile array based on specified file.
* @param [in] filename tile list file name
* @param [out] list sized_tlist list
* @return success of operation, return false if parse tile fails, list / tile is NULL
*/
bool tlist_parse(const char*, sized_tlist*);

/**
* reads file to find out how big tile list to allocate.
* @param [in] filename name of tile list file
* @return length the tile list should be
*/
size_t tlist_get_len(const char*);

/**
* allocates and initializes tile list based on tile list file.
* remeber to free this, if filename is bad program will exit
* @param [in] filename name of the tile list file
* @param [out] list pointer to sized_tlist struct
* @return status of operation
*/
bool tlist_init(const char*, sized_tlist*);

/**
 * wrapper around {@code init_tlist} exits on error.
 * @param [in] filename name of the tile list file
 * @retunr sized_tlist aviable tile list
 */
sized_tlist tlist_init_exit_on_err(const char*);

// TODO: not done
/**
* print tile array, tiles are separated by newlines.
* @param [in] t tile array
* @param [in] len tile array length
*/
void tlist_print(const sized_tlist*);

/**
 * free tlist, set pointer to null.
 * @param [in,out] list sized_list pointer to free
 */
void tlist_free(sized_tlist*);

/**
 * write tlist to file.
 * @param [in] list sized_tlist pointer, list of aviable tiles
 * @param [in] filename name of tile file to write to
 */
bool tlist_write(const sized_tlist*, const char*);

#endif
