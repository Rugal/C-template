#include <stdlib.h>
#include "Node.h"

#define SAFE_FREE(ob) do{  if (NULL != ob)  free(ob); ob = NULL; } while (0);

Node* createNode()
{
    Node* node = NULL;
    node = malloc(sizeof (Node));
    if (NULL != node)
    {
        node->data = NULL;
        node->left = NULL;
        node->right = NULL;
    }
    return node;
}

Node* createNodeData(int* data)
{
    Node* node = createNode();
    if (NULL != node)
        setNodeData(node, data);
    return node;
}

void deleteNode(Node* node)
{
    if (NULL == node)
        return;
    SAFE_FREE(node->data);
    node->left = node->right = NULL;
}

void appendNode(Node* current, Node * appending)
{
    if (NULL == current || NULL == appending)
        return;
    current->right = appending;
    appending->left = current;
}

void setNodeData(Node* current, int* value)
{
    if (NULL == current)
        return;
    if (current->data == NULL)
        current->data = malloc(sizeof (int));
    *(current->data) = *value;
}

int getNodeData(Node* current)
{
    return *(current->data);
}