#ifndef POINT_H
#define POINT_H

#include "side.h"

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct Point Point;

Point* Point_new(int i, int j, Direction side);

void Point_free(Point** selfPtr);

int Point_getRow(Point* self);

int Point_getColumn(Point* self);

Direction Point_getSide(Point* self);


typedef struct ListNode ListNode;

ListNode* ListNode_new(Point* p);

void ListNode_free(ListNode** selfPtr);

void ListNode_setNext(ListNode* node, ListNode* newNode);

ListNode* ListNode_getNext(ListNode* node);

Point* ListNode_getPoint(ListNode* node);

void ListNode_setPoint(ListNode* node, Point* p);


typedef struct List List;

List* List_new();

void List_free(List** selfPtr);

void List_addFirst(List* self, Point* p);

void List_insertAt(List* self, Point* p, int position);

void List_addLast(List* self, Point* p);

void List_removeFirst(List* self);

void List_removeAt(List* self, int position);

void List_removeLast(List* self);

Point* List_getPoint(List* self, int position);

int List_getSize(List* self);

int List_count(List* self);

bool List_hasPoint(List* self, int i, int j, Direction side);

#endif
