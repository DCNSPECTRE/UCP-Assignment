#include "linkedlist.h"

void insertFirst(linkedListNode** head, void* data){
    linkedListNode* newNode = (linkedListNode*)malloc(sizeof(linkedListNode));
    newNode->data = data;
    newNode->next = *head;
    *head = newNode;
}

void* removeFirst(linkedListNode** head){
    linkedListNode* temp;
    void* data;

    data = NULL;

    if(*head != NULL){
        temp = *head;
        *head = (*head)->next;
        data = temp->data;
        free(temp);
    }
    return data;
}

void freeList(linkedListNode** head, void (*freeData)(void*)){
    linkedListNode* temp;
    while(*head != NULL){
        temp = *head;
        *head = (*head)->next;
        if(freeData != NULL){
            freeData(temp->data);
        }
        free(temp);
    }
}