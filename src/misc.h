#ifndef MISC_H
#define MISC_H
/** @file misc.h */

#include <stdbool.h>
#include <stdio.h>

typedef enum {
    INTERACTIVE_NO_TILES,
    INTERACTIVE,
    AUTO
} gamemode;

/**
 * initializes file streams for tile list and gameboard returns gamemode.
 * @param argc count of args to main
 * @param argv array of args to main
 * @param list file stream for tile list
 * @param board file stream for gameboard
 */
gamemode init(int, char**, FILE*, FILE*);

/**
 * print usage.
 */
void usage();

/**
 * print greeting.
 */
void greeting();

/**
 * main game loop.
 * @param mode gamemode in which game should be played
 * @param list file stream for tile list if applicable
 * @param board file stream for gameboard if applicable
 */
void run(gamemode, FILE*, FILE*);

#endif
