#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdlib.h>
 /* Node structure for linked list */
typedef struct linkedListNode{
    void* data; /* Pointer to hold data of any type making is a generic linked list*/
    struct linkedListNode* next;
}linkedListNode;

/* Function prototypes */
void insertFirst(linkedListNode** head, void* data);
void* removeFirst(linkedListNode** head);
void freeList(linkedListNode** head, void (*freeData)(void*));

#endif