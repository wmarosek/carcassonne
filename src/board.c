#include "board.h"

// should this be array of pointers or array of structs,
// with pointers we could represent empty space by null pointer,
// with structs we would probably need additional switch specifing uninitalized state
tile* board_g[BOARD_SIZE][BOARD_SIZE] = {{ 0 }};
