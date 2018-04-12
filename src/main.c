#include "logic.h"
#include "calculator.h"
#include <stdlib.h>

int main(int argc, char* argv[]) {
    char* list = 0;
    char* board = 0;

    gamemode mode = init(argc, argv, &list, &board);

    run(mode, list, board);

    exit(EXIT_SUCCESS);
}
