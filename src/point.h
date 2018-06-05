#ifndef POINT_H
#define POINT_H

#include "side.h"

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct point point;

point* point_new(int i, int j, direction side);

void point_free(point** selfPtr);

int point_getRow(point* self);

int point_getColumn(point* self);

direction point_getSide(point* self);


typedef struct ListNode ListNode;

ListNode* ListNode_new(point* p);

void ListNode_free(ListNode** selfPtr);

void ListNode_setNext(ListNode* node, ListNode* newNode);

ListNode* ListNode_getNext(ListNode* node);

point* ListNode_getPoint(ListNode* node);

void ListNode_setPoint(ListNode* node, point* p);


typedef struct List List;

List* List_new();

void List_free(List** selfPtr);

void List_addFirst(List* self, point* p);

void List_insertAt(List* self, point* p, int position);

void List_addLast(List* self, point* p);

void List_removeFirst(List* self);

void List_removeAt(List* self, int position);

void List_removeLast(List* self);

ListNode* List_getNodeAt(List* self, int position);

point* List_getPoint(List* self, int position);

int List_getSize(List* self);

int List_count(List* self);

bool List_hasPoint(List* self, int i, int j, direction side);

#endif
