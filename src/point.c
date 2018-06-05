#include "point.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#define throw(MSG) assert(0 && MSG);

/*point.c*/

struct point {
    int x;
    int y;
    direction side;
};

point* point_new(int i, int j, direction side) {
    point* self = malloc(sizeof(point));
    self->x = i;
    self->y = j;
    self->side = side;
    return self;
}

void point_free(point** selfPtr) {
    free(*selfPtr);
    *selfPtr = NULL;
}

int point_getRow(point* self) {
    return self->x;
}

int point_getColumn(point* self) {
    return self->y;
}

direction point_getSide(point* self) {
    return self->side;
}


/* listnode.c*/

struct ListNode {
    point* p;
    ListNode* next;
};

ListNode* ListNode_new(point* p) {
    ListNode* self = malloc(sizeof(struct ListNode));
    self->next = NULL;
    self->p = p;
    return self;
}

void ListNode_free(ListNode** selfPtr) {
    point_free(&(*selfPtr)->p);
    free(*selfPtr);
    *selfPtr = NULL;
}

void ListNode_setNext(ListNode* node, ListNode* newNode) {
    node->next = newNode;
}

ListNode* ListNode_getNext(ListNode* node) {
    return node->next;
}

point* ListNode_getPoint(ListNode* node) {
    return node->p;
}

void ListNode_setPoint(ListNode* node, point* p) {
    node->p = p;
}


/*pointlist.c*/

struct List {
    int size;
    ListNode* items;
};

List* List_new(void) {
    List* self = malloc(sizeof(struct List));
    self->size = 0;
    self->items = NULL;
    return self;
}

void List_free(List** selfPtr) {
    if (selfPtr == NULL || *selfPtr == NULL) throw("Null pointer on free()");
    ListNode* cur = (*selfPtr)->items;
    ListNode* temp = NULL;
    while (cur != NULL) {
        temp = ListNode_getNext(cur);
        ListNode_free(&cur);
        cur = temp;
    }
    free(*selfPtr);
    *selfPtr = NULL;
}

void List_addFirst(List* self, point* p) {
    ListNode* node = ListNode_new(p);
    ListNode_setNext(node, self->items);
    self->items = node;
    self->size = List_count(self);
}
void List_insertAt(List* self, point* p, int position) {
    if (p == NULL) throw("Null reference");
	if (position < 0) throw("Out of bounds");
    if (position >= self->size) position = self->size;

    if (position == 0) {
        List_addFirst(self, p);
        return;
    }

    ListNode* node = ListNode_new(p);

    ListNode* cur = self->items;
    int i = 0;
    while (cur != NULL && i != position - 1) {
        cur = ListNode_getNext(cur);
        i++;
    }
    ListNode_setNext(node, ListNode_getNext(cur));
    ListNode_setNext(cur, node);
    self->size = List_count(self);
}

void List_addLast(List* self, point* p) {
    if (p == NULL) throw("Null reference");
    if(p != NULL)
    List_insertAt(self, p, self->size++);
}

void List_removeFirst(List* self) {
    ListNode* node = self->items;
    if (node == NULL) throw("Null reference");
    self->items = ListNode_getNext(node);
    ListNode_free(&node);
    self->size = List_count(self);
}

void List_removeAt(List* self, int position) {
    if (position < 0 || position >= self->size) throw("Out of bounds");

    if (position == 0) {
        List_removeFirst(self);
        return;
    }

    ListNode* cur = self->items;
    int i = 0;
    while (cur != NULL && i != position - 1) {
        i++;
        cur = ListNode_getNext(cur);
    }
    ListNode* node = ListNode_getNext(cur);
    ListNode_setNext(cur, ListNode_getNext(node));
    ListNode_free(&node);
    self->size = List_count(self);
}

void List_removeLast(List* self) {
    List_removeAt(self, self->size - 1);
}

ListNode* List_getNodeAt(List* self, int position) {
    if (position < 0 || position > self->size) throw("Out of bounds");
    ListNode* cur = self->items;
    int i = 0;

    while (cur != NULL && i != position) {
        i++;
        cur = ListNode_getNext(cur);
    }
    return cur;
}

point* List_getPoint(List* self, int position) {
    return ListNode_getPoint(List_getNodeAt(self,position));
}

int List_getSize(List* self) {
    return (int)self->size;
}

int List_count(List* self) {
    int count = 0;
    ListNode* cur = self->items;
    while (cur != NULL) {
        count++;
        cur = ListNode_getNext(cur);
    }
    return count;
}

bool List_hasPoint(List* self, int i, int j, direction side) {
    ListNode* cur = self->items;
    while (cur != NULL) {
        point* p = ListNode_getPoint(cur);
        if (point_getRow(p) == i && point_getColumn(p) == j && point_getSide(p) == side) return true;
        cur = ListNode_getNext(cur);
    }
    return false;
}
