/* 
 * File:   List.h
 * Author: Rugal Bernstein
 *
 * Created on March 9, 2016, 1:00 PM
 * This is a generic data type node structure.
 */

#ifndef LIST_H
#define LIST_H

#ifdef __cplusplus
extern "C"
{
#endif

    typedef struct Node
    {
        int* data;
        struct Node* left;
        struct Node* right;
    } Node;
    /**
     * Create a node object before initialize it.
     * @return
     */
    Node* createNode();
    /**
     * Create a node object with initializing data.
     * @param data
     * @return 
     */
    Node* createNodeData(int* data);
    /**
     * Free current node object if it is not null.
     * @param node
     */
    void deleteNode(Node* node);
    /**
     * Add the given appending node object onto the right of current object.
     * If the right one is not null before appending, it will be replaced by new one.
     * @param current
     * @param appending
     */
    void appendNode(Node* current, Node * appending);
    /**
     * Set the data field of current object.
     * @param current
     * @param value
     */
    void setNodeData(Node* current, int* value);
    /**
     * Get the data field of node, the given object must not be NULL.
     * @param current
     * @return
     */
    int getNodeData(Node* current);
#ifdef __cplusplus
}
#endif

#endif /* LIST_H */

