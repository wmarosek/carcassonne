#ifndef FILE_H
#define FILE_H

#include <stdbool.h>
#include <stdio.h>

extern FILE* g_fTiles;
extern FILE* g_fBoard;

bool open_files();
bool write_files();

#endif
