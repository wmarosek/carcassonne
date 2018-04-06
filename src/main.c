#include "misc.h"

#include <stdlib.h>

int main(int argc, char* argv[]) {
    FILE* list = 0;
    FILE* board = 0;

    gamemode mode = init(argc, argv, &list, &board);

    run(mode, list, board);

    if (list) {
        fclose(list);
    }
    if (board) {
        fclose(board);
    }

    exit(EXIT_SUCCESS);
}
