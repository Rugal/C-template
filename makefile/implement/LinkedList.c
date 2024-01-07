#include <stdlib.h>
#include <stdio.h>
#include "Node.h"
#include "LinkedList.h"

#define CLEAR_HEAD do{deleteNode(list->head);initialize(list);}while(0)

LinkedList* initialize(LinkedList* list)
{
    if (NULL == list)
        return NULL;
    list->size = 0;
    list->head = list->tail = NULL;
    return list;
}
//----------------------------------------------

Node * getNode(LinkedList* list, int index)
{
    if (list == NULL || list->size <= index || index < 0)
        return NULL;
    Node* it = list->head;
    for (int i = 0; i < index; it = it->right, i++);
    return it;
}

LinkedList* createLinkedList()
{
    LinkedList* list = malloc(sizeof (LinkedList));
    return initialize(list);
}

int isEmpty(LinkedList* list)
{
    if (NULL == list)
        return -1;
    return list->size == 0;
}

int sizeOfList(LinkedList* list)
{
    if (NULL == list)
        return -1;
    return list->size;
}

void deleteLinkedList(LinkedList* list)
{
    if (NULL == list)
        return;
    clear(list);
}

void clear(LinkedList* list)
{
    if (NULL == list)
        return;
    while (!isEmpty(list))
        removeHead(list);
}

void addOnHead(LinkedList* list, int* data)
{
    if (list == NULL)
        return;
    //Going to add on head
    Node* temp = createNodeData(data);
    //different length
    if (isEmpty(list) == 1)//if empty
        list->tail = list->head = temp;
    else
    {
        appendNode(temp, list->head);
        list->head = temp;
    }
    list->size++;
}

void addOnTail(LinkedList* list, int* data)
{
    if (list == NULL)
        return;
    //Going to add on head
    Node* temp = createNodeData(data);
    //different length
    if (isEmpty(list) == 1)//if empty
        list->tail = list->head = temp;
    else
    {
        appendNode(list->tail, temp);
        list->tail = temp;
    }
    list->size++;
}

void removeIndex(LinkedList* list, int index)
{
    if (list == NULL || list->size <= index || index < 0)
        return;
    //---------------------------------------
    if (index == 0)
    {
        removeHead(list);
        return;
    }
    if (index == list->size - 1)
    {
        removeTail(list);
        return;
    }
    //----------------------------------------
    Node* it = getNode(list, index);
    Node* left = it->left;
    Node* right = it->right;
    if (NULL != left)
        left->right = right;
    if (NULL != right)
        right->left = left;
    deleteNode(it);
    list->size--;
}

void printLinkedList(LinkedList* list)
{
    if (NULL == list)
        return;
    for (Node* it = list->head; it != NULL; it = it->right)
        printf("%d ", *it->data);
}

void removeHead(LinkedList* list)
{
    if (NULL == list)
        return;
    if (list->size > 1)
    {
        list->head = list->head->right; //move right
        deleteNode(list->head->left);
        list->head->left = NULL; //Set NULL to left of head node
        list->size--;
    }
    else
        CLEAR_HEAD;
}

void removeTail(LinkedList* list)
{
    if (list->size > 1)
    {
        list->tail = list->tail->left; //move right
        deleteNode(list->tail->right);
        list->tail->right = NULL; //Set NULL to left of head node
        list->size--;
    }
    else
        CLEAR_HEAD;
}