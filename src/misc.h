#ifndef MISC_H
#define MISC_H
/** @file misc.h */

typedef enum {
    INTERACTIVE_NO_TILES,
    INTERACTIVE,
    AUTO
} gamemode;

/**
 * initializes file streams for tile list and gameboard returns gamemode.
 * @param argc count of args to main
 * @param argv array of args to main
 * @param list_file pointer list file name
 * @param board_file pointer to board file name
 */
gamemode init(int, char**, char**, char**);

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
 * @param list file name for tile list if applicable
 * @param board file name for gameboard if applicable
 */
void run(gamemode, char*, char*);

#endif
