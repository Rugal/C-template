#define _GNU_SOURCE
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "String.h"

#define DEFAULT_LENGTH 20

struct String
{
    unsigned int size;
    unsigned int capacity;
    char* data;
};

int size(String* s)
{
    assert(NULL != s);
    /*if (NULL == s)*/
        /*return -1;*/
    return s->size;
}

char* data(String* s)
{
    assert(NULL != s);
    return s->data;
}

int capacity(String* s)
{
    if (NULL == s)
    {
        return -1;
    }
    return s->capacity;
}

String* createString(unsigned int size)
{
    String* s = malloc(sizeof (String));
    s->data = malloc(sizeof (char) * size);
    memset(s->data, 0, sizeof (char) * size);
    s->size = 0;
    s->capacity = size;
    return s;
}

/**
 * Dispose a String object.
 * @param s
 */
void deleteString(String* s)
{
    if (NULL == s)
        return;
    if (NULL != s->data)
        free(s->data);
    free(s);
}

int extent(String *s)
{
    if (NULL == s)
        return -1;
    s->capacity *= 2;
    char *temp = malloc(sizeof (char) * s->capacity);
    memset(temp, 0, sizeof (char) * s->capacity);
    strncpy(temp, s->data, s->size);
    free(s->data);
    s->data = temp;
    return 0;
}

int appendChar(String* s, char c)
{
    if (NULL == s)
        return 0;
    if (s->capacity <= s->size)
        if (extent(s) == -1)
            return 0;
    s->data[s->size++] = c;
    return 1;
}

int appendString(String* s, char* ca, int size)
{
    assert(s != NULL);
    for (int i = 0; i < size; i++)
        appendChar(s, ca[i]);
    return size;
}
