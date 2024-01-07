/* 
 * File:   ArrayList.h
 * Author: Rugal Bernstein
 *
 * Created on March 22, 2016, 1:59 PM
 */

#ifndef ArrayList_H
#define ArrayList_H
#ifdef __cplusplus
extern "C"
{
#endif

    typedef struct
    {
        int size;
        int capacity;
        char** array;
    }ArrayList;

    /**
     * Create an ArrayList object.
     */
    ArrayList* createArrayList();
    /**
     * Delete an ArrayList object.
     */
    void deleteArrayList(ArrayList* list);
    /**
     * Add a word into a list;
     */
    void addWord(ArrayList* list, char* word);

#ifdef __cplusplus
}
#endif

#endif /* ArrayList_H */
