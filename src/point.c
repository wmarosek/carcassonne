#include "point.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

/*point.c*/

struct Point {
    int x;
    int y;
    Direction side;
};

Point* Point_new(int i, int j, Direction side) {
    Point* self = malloc(sizeof(Point));
    self->x = i;
    self->y = j;
    self->side = side;
    return self;
}

void Point_free(Point** selfPtr) {
    free(*selfPtr);
    *selfPtr = NULL;
}

int Point_getRow(Point* self) {
    return self->x;
}

int Point_getColumn(Point* self) {
    return self->y;
}

Direction Point_getSide(Point* self) {
    return self->side;
}


/* listnode.c*/

struct ListNode {
    Point* p;
    ListNode* next;
};

ListNode* ListNode_new(Point* p) {
    ListNode* self = malloc(sizeof(struct ListNode));
    self->next = NULL;
    self->p = p;
    return self;
}

void ListNode_free(ListNode** selfPtr) {
    Point_free(&(*selfPtr)->p);
    free(*selfPtr);
    *selfPtr = NULL;
}

void ListNode_setNext(ListNode* node, ListNode* newNode) {
    node->next = newNode;
}

ListNode* ListNode_getNext(ListNode* node) {
    return node->next;
}

Point* ListNode_getPoint(ListNode* node) {
    return node->p;
}

void ListNode_setPoint(ListNode* node, Point* p) {
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
    assert((selfPtr == NULL || *selfPtr == NULL) && "Null pointer on free()");
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

void List_addFirst(List* self, Point* p) {
    ListNode* node = ListNode_new(p);
    ListNode_setNext(node, self->items);
    self->items = node;
    self->size = List_count(self);
}
void List_insertAt(List* self, Point* point, int position) {
    assert((point == NULL) && "Null reference");
    assert((position < 0) && "Out of bounds");
    if (position >= self->size) position = self->size;

    if (position == 0) {
        List_addFirst(self, point);
        return;
    }

    ListNode* node = ListNode_new(point);

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

void List_addLast(List* self, Point* point) {
    assert((point == NULL) && "Null reference");
    List_insertAt(self, point, self->size++);
}

void List_removeFirst(List* self) {
    ListNode* node = self->items;
    assert((node == NULL) && "NUll reference");
    self->items = ListNode_getNext(node);
    ListNode_free(&node);
    self->size = List_count(self);
}

void List_removeAt(List* self, int position) {
    assert((position < 0 || position >= self->size) && "Out of bounds");

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

Point* List_getPoint(List* self, int position) {
    assert((position < 0 || position > self->size) && "Out of bounds");
    ListNode* cur = self->items;
    int i = 0;

    while (cur != NULL && i != position) {
        i++;
        cur = ListNode_getNext(cur);
    }
    return ListNode_getPoint(cur);
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

bool List_hasPoint(List* self, int i, int j, Direction side) {
    ListNode* cur = self->items;
    while (cur != NULL) {
        Point* point = ListNode_getPoint(cur);
        if (Point_getRow(point) == i && Point_getColumn(point) == j && Point_getSide(point) == side) return true;
        cur = ListNode_getNext(cur);
    }
    return false;
}
