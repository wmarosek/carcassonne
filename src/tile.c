#include "tile.h"

#include <assert.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

tile* make_tile(tile** ptr) {
    return *ptr = malloc(sizeof(tile));
}

element char_to_element(char ch) {
    assert(ch == 'c' || ch == 'r' || ch == 'f');
    switch (tolower(ch)) {
    case 'c': return CASTLE;
    case 'r': return ROAD;
        // returns FIELD for anything different form 'c' and 'r'
    default: return FIELD;
    }
}

modifier char_to_modifier(char ch) {
    switch (tolower(ch)) {
    case '*': return SHIELD;
    case 't': return TEMPLE;
    default: return NONE;
    }
}

tile* str_to_tile(const char str[/*static*/ 5], tile* t) {
    if (t) {
        t->up = Side_new(char_to_element(str[0]));
        t->right = Side_new(char_to_element(str[1]));
        t->down = Side_new(char_to_element(str[2]));
        t->left = Side_new(char_to_element(str[3]));

        //t->up = char_to_element(str[0]);
        //t->right = char_to_element(str[1]);
        //t->down = char_to_element(str[2]);
        //t->left = char_to_element(str[3]);
        t->mod = char_to_modifier(str[4]);
    }
    return t;
}

tile* make_tile_from_str(const char str[/*static*/ 5], tile** ptr) {
    return str_to_tile(str, make_tile(ptr));
}

bool parse_tile(FILE* file, tile* t) {
    int ch;
    char str[5];
    size_t i = 0;
    while ((ch = getc(file)) != EOF) {
        if (ch == '\t') {
            return true;
        }
        if (isspace(ch)) {
            continue;
        }
        str[i++] = (char)ch;
        if (i == 5) {
            str_to_tile(str, t);
            return true;
        }
    }
    return false;
}

bool parse_tile_list(const char* filename, tile_list_t list, size_t len) {
    if (!list) {
        return false;
    }
    FILE* file;
    if ((file = fopen(filename, "r")) == 0) {
        return false;
    }
    for (size_t i = 0; i < len; ++i) {
        // if any tile parsing fails return false
        if (!parse_tile(file, &list[i])) {
            fclose(file);
            return false;
        }
    }
    fclose(file);
    return true;
}

size_t find_tile_list_len(const char* filename) {
    FILE* list = fopen(filename, "r");
    size_t count = 0;
    if (list) {
        int ch;
        while ((ch = getc(list)) != EOF) {
            while ((ch = getc(list)) != EOF && isspace(ch)) {
                continue;
            }
            if (ch != EOF && !isspace(ch)) {
                ++count;
            }
            while ((ch = getc(list)) != EOF && !isspace(ch)) {
                continue;
            }
        }
        fclose(list);
    }
    return count;
}

size_t initialize_tile_list(const char* filename, tile_list_t* list) {
    size_t len = find_tile_list_len(filename);
    *list = malloc(sizeof(tile) * len);
    if (!parse_tile_list(filename, *list, len)) {
        free(*list);
        fputs("error parsing tile list\n", stderr);
        exit(EXIT_FAILURE);
    }
    return len;
}

char element_to_char(element e) {
    switch (e) {
    case CASTLE: return 'c';
    case ROAD: return 'r';
    case FIELD: return 'f';
    default: return '\0';
    }
}

char modifier_to_char(modifier m) {
    switch (m) {
    case SHIELD: return '*';
    case TEMPLE: return 't';
    default: return '_';
    }
}

char* tile_to_str(const tile* t, char buff[/*static*/ 5]) {
    if (t && buff) {    // check if pointers are not null
        buff[0] = element_to_char(tile_getSideElement(t,NORTH));
        buff[1] = element_to_char(tile_getSideElement(t, EAST));
        buff[2] = element_to_char(tile_getSideElement(t, SOUTH));
        buff[3] = element_to_char(tile_getSideElement(t,WEST));
        buff[4] = modifier_to_char(t->mod);
    }
    else if (buff) {  // null tile pointer should mean empty board cell
        buff[0] = '\t';
        memset(&buff[1], '\0', 4);
    }
    return buff;
}

char* tile_to_str_malloc(const tile* t) {
    return tile_to_str(t, malloc(sizeof(char) * 5));
}

void print_tile(const tile* t) {
    char buff[5];
    printf("%.*s", 5, tile_to_str(t, buff));
}

void print_tile_list(const tile* t, size_t len) {
    for (unsigned int i = 0; i < len; ++i) {
        print_tile(&t[i]);
        putchar('\n');
    }
}

tile* rotate_tile(tile* t) {
    if (t) {
        Side* u = t->up;
        Side* r = t->right;
        Side* d = t->down;
        Side* l = t->left;
        t->up = l;
        t->right = u;
        t->down = r;
        t->left = d;
    }
    return t;
}

bool tile_isEmpty(const tile* t) {
    return t->isEmpty;
}

element tile_getSideElement(const tile* t, Direction dir) {
    switch (dir) {
    case NORTH: return Side_getType(t->up);
    case EAST: return Side_getType(t->right);
    case SOUTH: return Side_getType(t->down);
    case WEST: return Side_getType(t->left);
    }
}

Side* tile_getSide(const tile* t, Direction dir) {
    switch (dir) {
    case NORTH: return t->up;
    case EAST: return t->right;
    case SOUTH: return t->down;
    case WEST: return t->left;
    }
}

void tile_setSideCompletion(const tile* t, Direction dir, int status) {
    switch (dir) {
    case NORTH:
        Side_setCompletionStatus(t->up, status);
        break;
    case EAST:
        Side_setCompletionStatus(t->right, status);
        break;
    case SOUTH:
        Side_setCompletionStatus(t->down, status);
        break;
    case WEST:
        Side_setCompletionStatus(t->left, status);
    }
}

int tile_getSideCompletion(const tile* t, Direction dir) {
    switch (dir) {
    case NORTH:
        return Side_isCompleted(t->up);
    case EAST:
        return Side_isCompleted(t->right);
    case SOUTH:
        return Side_isCompleted(t->down);
    case WEST:
        return Side_isCompleted(t->left);
    }
    return 0;
}

modifier tile_getCenter(const tile* t) {
    return t->mod;
}

int tile_numOfSegments(const tile* t, element type) {
    int count = 0;

    if (Side_getType(t->up) == type) {
        count++;
    }
    if (Side_getType(t->right) == type) {
        count++;
    }
    if (Side_getType(t->down) == type) {
        count++;
    }
    if (Side_getType(t->left) == type) {
        count++;
    }

    return count;
}

Direction* tile_getSegments(const tile* t, element type, int count) {
    Direction* segments = malloc(count * sizeof(Direction));
    int i = 0;

    if (Side_getType(t->up) == type) {
        segments[i++] = NORTH;
    }
    if (Side_getType(t->right) == type) {
        segments[i++] = EAST;
    }
    if (Side_getType(t->down) == type) {
        segments[i++] = SOUTH;
    }
    if (Side_getType(t->left) == type) {
        segments[i++] = WEST;
    }

    return segments;
}

void tile_freeSegments(Direction** selfPtr) {
    Direction* self = *selfPtr;
    free(self);
    *selfPtr = NULL;
}

bool tile_hasCastle(const tile* t) {
    return Side_getType(t->up) == CASTLE || Side_getType(t->right) == CASTLE || Side_getType(t->down) == CASTLE || Side_getType(t->left) == CASTLE;
}

bool tile_hasRoad(const tile* t) {
    return Side_getType(t->up) == ROAD || Side_getType(t->right) == ROAD || Side_getType(t->down) == ROAD || Side_getType(t->left) == ROAD;
}

bool tile_hasTemple(const tile* t) {
    return tile_getCenter(t) == TEMPLE;
}

bool tile_hasCrossroads(const tile* t) {
    return tile_getCenter(t) == CROSSROASDS;
}

bool tile_hasShield(const tile* t) {
    return t->shield;
}
