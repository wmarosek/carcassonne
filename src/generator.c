#include "tlist.h"

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

void tileGenerator(const char* default_tiles,const char* new_tiles, int num);

int main(int argc, char* argv[]) {
    if(argc != 4) {
        puts("Wrong input!\n"
             "Format: [DEFAULT_TILES_FILE] [NEW_TILES_FILE] [NUM_OF_NEW_TILES]");
        return EXIT_FAILURE;
    }

    tileGenerator(argv[1], argv[2], atoi(argv[3]));
    return EXIT_SUCCESS;
}

void tileGenerator(const char* default_tiles,const char* new_tiles, int num) {
    sized_tlist default_list = tlist_init_exit_on_err(default_tiles);
    
    sized_tlist new_list;
    new_list.size = num;
    new_list.tiles = malloc(num * sizeof(tile*));

    srand(time(NULL));
    for(int i = 0; i < num; i++) {
        new_list.tiles[i] = default_list.tiles[rand() % default_list.size];
    }

    tlist_write(&new_list,new_tiles);
    tlist_free(&default_list);
    tlist_free(&new_list);
}
