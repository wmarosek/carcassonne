#include "tile.h"

#include <assert.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

tile* tile_alloc(tile** ptr) {
    return *ptr = malloc(sizeof(tile));
}

element elem_from_char(char ch) {
    assert(ch == 'c' || ch == 'r' || ch == 'f');
    switch (tolower(ch)) {
    case 'c': return CASTLE;
    case 'r': return ROAD;
    default: return FIELD;
    }
}

modifier mod_from_char(char ch) {
    switch (tolower(ch)) {
    case '*': return SHIELD;
    case 't': return TEMPLE;
    default: return NONE;
    }
}

tile* tile_from_str(const char str[static 5], tile* t) {
    if (t) {
        t->up = Side_new(elem_from_char(str[0]));
        t->right = Side_new(elem_from_char(str[1]));
        t->down = Side_new(elem_from_char(str[2]));
        t->left = Side_new(elem_from_char(str[3]));
        t->mod = mod_from_char(str[4]);
    }
    return t;
}

tile* tile_alloc_from_str(const char str[static 5], tile** ptr) {
    return tile_from_str(str, tile_alloc(ptr));
}

bool tile_parse(FILE* file, tile** t) {
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
            tile_alloc_from_str(str, t);
            return true;
        }
    }
    return false;
}

bool tlist_parse(const char* filename, sized_tlist* list) {
    if (!list && !list->list) {
        return false;
    }
    FILE* file;
    if ((file = fopen(filename, "r")) == 0) {
        return false;
    }
    for (size_t i = 0; i < list->len; ++i) {
        // if any tile parsing fails return false
        if (!tile_parse(file, &list->list[i])) {
            fclose(file);
            return false;
        }
    }
    fclose(file);
    return true;
}

size_t tlist_get_len(const char* filename) {
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

bool tlist_init(const char* filename, sized_tlist* list) {
    list->len = tlist_get_len(filename);
    list->list = malloc(sizeof(tile*) * list->len);
    memset(list->list, 0, sizeof(tile*) * list->len);
    return tlist_parse(filename, list);
}

sized_tlist tlist_init_exit_on_err(const char* filename) {
    sized_tlist list;
    if (!tlist_init(filename, &list)) {
        free(list.list);
        fputs("error parsing tile list\n", stderr);
        exit(EXIT_FAILURE);
    }
    return list;
}

char elem_to_char(element e) {
    switch (e) {
    case CASTLE: return 'c';
    case ROAD: return 'r';
    case FIELD: return 'f';
    default: return '\0';
    }
}

char mod_to_char(modifier m) {
    switch (m) {
    case SHIELD: return '*';
    case TEMPLE: return 't';
    default: return '_';
    }
}

char* tile_to_str(const tile* t, char buff[static 5]) {
    if (t && buff) {    // check if pointers are not null
        buff[0] = elem_to_char(tile_getSideElement(t, NORTH));
        buff[1] = elem_to_char(tile_getSideElement(t, EAST));
        buff[2] = elem_to_char(tile_getSideElement(t, SOUTH));
        buff[3] = elem_to_char(tile_getSideElement(t, WEST));
        buff[4] = mod_to_char(t->mod);
    }
    else if (buff) {    // null tile pointer should mean empty board cell
        buff[0] = '\t';
        memset(&buff[1], '\0', 4);
    }
    return buff;
}

char* tile_to_str_alloc(const tile* t) {
    return tile_to_str(t, malloc(sizeof(char) * 5));
}

void tile_print(const tile* t) {
    char buff[5];
    printf("%.*s", 5, tile_to_str(t, buff));
}

void tlist_print(const sized_tlist* list) {
    for (size_t i = 0; i < list->len; ++i) {
        tile_print(list->list[i]);
        putchar('\n');
    }
}

tile* tile_rotate(tile* t) {
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
    return t == 0;
}

element tile_getSideElement(const tile* t, Direction dir) {
    switch (dir) {
    case NORTH: return Side_getType(t->up);
    case EAST: return Side_getType(t->right);
    case SOUTH: return Side_getType(t->down);
    case WEST: return Side_getType(t->left);
    }
    return 0;
}

Side* tile_getSide(const tile* t, Direction dir) {
    switch (dir) {
    case NORTH: return t->up;
    case EAST: return t->right;
    case SOUTH: return t->down;
    case WEST: return t->left;
    }
    return 0;
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
    case NORTH: return Side_isCompleted(t->up);
    case EAST: return Side_isCompleted(t->right);
    case SOUTH: return Side_isCompleted(t->down);
    case WEST: return Side_isCompleted(t->left);
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

Direction* tile_getSegments(const tile* t, element type, size_t count) {
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
    free(*selfPtr);
    *selfPtr = NULL;
}

bool tile_hasCastle(const tile* t) {
    return Side_getType(t->up) == CASTLE
        || Side_getType(t->right) == CASTLE
        || Side_getType(t->down) == CASTLE
        || Side_getType(t->left) == CASTLE;
}

bool tile_hasRoad(const tile* t) {
    return Side_getType(t->up) == ROAD
        || Side_getType(t->right) == ROAD
        || Side_getType(t->down) == ROAD
        || Side_getType(t->left) == ROAD;
}

bool tile_hasTemple(const tile* t) {
    return tile_getCenter(t) == TEMPLE;
}

bool tile_hasCrossroads(const tile* t) {
    return tile_getCenter(t) == CROSSROASDS;
}

bool tile_hasShield(const tile* t) {
    return t->mod == SHIELD;
}
