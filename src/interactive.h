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
 * @param [in] list sized_tlist pointer
 */
void run_interactive(sized_tlist*);

#endif
