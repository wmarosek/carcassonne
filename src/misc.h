#ifndef MISC_H
#define MISC_H

#include <stdbool.h>
#include <stdio.h>

typedef enum {
    INTERACTIVE_NO_TILES,
    INTERACTIVE,
    AUTO
} gamemode;

gamemode init(int, char**, FILE*, FILE*);       // set gamemode, set file pointers, etc.

void usage();                                   // print usage
void greeting();                                // print greeting

void run(gamemode, FILE*, FILE*);               // game loop

#endif
