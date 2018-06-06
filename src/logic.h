#ifndef LOGIC_H
#define LOGIC_H
/** @file logic.h */

#include <stdio.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

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
 * print usage, help etc.
 * @param [in] amount of arguments to program
 * @param [in] arguments to the program
 */
void handle_args(int argc, char* argv[]);

/**
 * main game loop.
 * @param [in] amount of arguments to program
 * @param [in] arguments to the program
 */
void run(int argc, char* argv[]);

#endif
