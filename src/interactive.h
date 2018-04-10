#ifndef INTERACTIVE_H
#define INTERACTIVE_H
/** @file interactive.h */

#include "tile.h"

/**
 * print usage.
 */
void usage();

/**
 * print greeting.
 */
void greeting();

/**
 * print interactive help
 */
void help();

/**
 * interactive mode logic and game loop.
 * @param tile_list tile list
 * @param list_len list length
 */
void run_interactive(tile_list_t*, size_t);

#endif
