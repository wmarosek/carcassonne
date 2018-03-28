#ifndef MISC_H
#define MISC_H

#include <stdbool.h>

typedef enum { INTERACTIVE, AUTO } gamemode;

bool setup();                           // set gamemode, set file pointers, etc.

void usage();                           // print usage
void greeting();                        // print greeting
void run();                             // game loop

#endif
