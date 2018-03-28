#include "misc.h"

#include <stdlib.h>

int main(int argc, char* argv[]) {
    gamemode mode = AUTO;
    if (argc < 2) {
        mode = INTERACTIVE;
        greeting();
    }

    return EXIT_SUCCESS;
}
