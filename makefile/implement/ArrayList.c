#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "ArrayList.h"

#define DEFAULT_CAPACITY 4

ArrayList* extend(ArrayList* list)
{
    list->capacity *= 2;
    char** temp = malloc(list->capacity * sizeof(char*));
    memset(temp, 0, list->capacity * sizeof(char*));
    for(int i=0; i < list->size; i++)
        temp[i] = list->array[i];
    free(list->array);
    list->array = temp;
    return list;
}

ArrayList* createArrayList()
{
    ArrayList* list = malloc(sizeof(ArrayList));
    list->size=0;
    list->capacity=DEFAULT_CAPACITY;
    list->array=malloc(list->capacity * sizeof(char*));
    memset(list->array, 0, list->capacity * sizeof(char*));
    return list;
}

void deleteArrayList(ArrayList* list)
{
    assert(list != NULL);
    for(int i=0; i<list->size; i++)
        if(NULL != list->array[i])
            free(list->array[i]);
    if(NULL != list->array)
        free(list->array);
    free(list);
}

void addWord(ArrayList* list, char* word)
{
    assert(list != NULL);
    if(list->size >= list->capacity)
        extend(list);
    list->array[list->size] = malloc((strlen(word) + 1) * sizeof(char));
    strcpy(list->array[list->size++], word);
}
