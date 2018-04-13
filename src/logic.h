#ifndef LOGIC_H
#define LOGIC_H
/** @file logic.h */

#include <stdio.h>

typedef enum {
    INTERACTIVE_NO_TILES,
    INTERACTIVE,
    AUTO
} gamemode;

/**
 * try to open filename whith spefified mode, exit and print name on fopen error.
 * @param filename name of the file
 * @param mode mode of operation
 * @name of file in error message
 * @return file stream pointer
 */
FILE* exit_on_bad_file_open(const char* filename, const char* mode, const char* name);

/**
 * initializes file streams for tile list and gameboard returns gamemode.
 * @param [in] argc count of args to main
 * @param [in] argv array of args to main
 * @param [out] list_file pointer list file name
 * @param [out] board_file pointer to board file name
 */
gamemode init(int, char**, char**, char**);

/**
 * main game loop.
 * @param [in] mode gamemode in which game should be played
 * @param [in] list file name for tile list if applicable
 * @param [in] board file name for gameboard if applicable
 */
void run(gamemode, char*, char*);

#endif
