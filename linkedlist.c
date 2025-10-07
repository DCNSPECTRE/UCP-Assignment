#include "linkedlist.h"
/* This is my GENERIC linked list implementation that can store any type of data using void pointers */

/* This insert function inserts a node at the head of the list*/
/* head is a pointer to the head pointer of the list data is a void pointer to the data to be stored in the node */
void insertFirst(linkedListNode** head, void* data){
    linkedListNode* newNode = (linkedListNode*)malloc(sizeof(linkedListNode)); /* Allocates memory via malloc of size of the linked list node*/
    newNode->data = data; /* sets the data of the new node to the data passed in */
    newNode->next = *head; /* sets the next pointer of the new node to the current head of the list*/
    *head = newNode; /* sets the head of the list to the new node*/
}

/* This function returns the first node of the list */
void* removeFirst(linkedListNode** head){
    linkedListNode* temp; /* Temporary pointer to hold the node to be removed */
    void* data; /* pointer to hold the data of the node to be removed */

    data = NULL; /* initialises data to NULL in case the list is empty */

    /* If the head of the list is not null, it sets the temp node to be the head, the head becomes node in the list, the data becomes the data stored in temp and then we free temp.*/
    if(*head != NULL){
        temp = *head;
        *head = (*head)->next;
        data = temp->data;
        free(temp);
    }
    return data;
}

/* This function frees the entire linked list */
void freeList(linkedListNode** head, void (*freeData)(void*)){
    linkedListNode* temp; /* temporary pointer to hold the node to be freed */
    /* If the head is not null it iterates through the list freeing each node and its data if a freeData function is provided to the function pointer */
    while(*head != NULL){ 
        temp = *head;
        *head = (*head)->next;
        if(freeData != NULL){
            freeData(temp->data);
        }
        free(temp);
    }
}