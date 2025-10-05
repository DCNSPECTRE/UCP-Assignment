#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdlib.h>

typedef struct linkedListNode{
    void* data;
    struct linkedListNode* next;
}linkedListNode;

void insertFirst(linkedListNode** head, void* data);
void* removeFirst(linkedListNode** head);
void freeList(linkedListNode** head, void (*freeData)(void*));

#endif