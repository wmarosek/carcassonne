#include "logic.h"

#include <stdlib.h>

int main(int argc, char* argv[]) {
    handle_args(argc, argv);
    run(argc, argv);
    exit(EXIT_SUCCESS);
}
