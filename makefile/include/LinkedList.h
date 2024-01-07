/* 
 * File:   LinkedList.h
 * Author: Rugal Bernstein
 *
 * Created on March 9, 2016, 1:59 PM
 */

#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include <stdbool.h>
#include "Node.h"
#ifdef __cplusplus
extern "C"
{
#endif

    typedef struct LinkedList
    {
        Node* head;
        Node* tail;
        int size;
    } LinkedList;
    /**
     * 
     * @return
     */
    LinkedList* createLinkedList();
    /**
     * 
     * @param list
     */
    void deleteLinkedList(LinkedList* list);
    /**
     * 
     * @param list
     * @param data
     */
    void addOnHead(LinkedList* list, int* data);
    /**
     * 
     * @param list
     * @param data
     */
    void addOnTail(LinkedList* list, int* data);
    /**
     * 
     * @param index
     * @return
     */
    Node * getNode(LinkedList* list, int index);
    /**
     * 
     * @param list
     * @param index
     */
    void removeIndex(LinkedList* list, int index);
    /**
     *
     * @param list
     * @return
     */
    int sizeOfList(LinkedList* list);
    /**
     * 
     * @param list
     * @return
     */
    int isEmpty(LinkedList* list);
    /**
     * 
     * @param list
     */
    void removeHead(LinkedList* list);
    /**
     * 
     * @param list
     */
    void removeTail(LinkedList* list);
    /**
     * 
     * @param list
     */
    void clear(LinkedList* list);
    /**
     *  Print content of given LinkedList object
     * @param list
     */
    void printLinkedList(LinkedList* list);
#ifdef __cplusplus
}
#endif

#endif /* LINKEDLIST_H */

