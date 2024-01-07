/* 
 * File:   String.h
 * Author: Rugal Bernstein
 *
 * Created on February 23, 2016, 2:53 PM
 */

#ifndef STRING_H
#define STRING_H

#ifdef __cplusplus
extern "C"
{
#endif

    typedef struct String String;
    /**
     * Get the length of this String.
     * @param s
     * @return 
     */
    int size(String* s);
    /**
     * Get the actually capacity of this String.
     * @param s
     * @return 
     */
    int capacity(String* s);
    /**
     * Get character array data from this String.
     * @param s
     * @return 
     */
    char* data(String* s);
    /**
     * Create a String object with given length.
     * 
     * @param length
     * @return 
     */
    String* createString(unsigned int size);
    /**
     * Dispose a String object.
     * @param s
     */
    void deleteString(String* s);
    /**
     * Append character onto the String object.
     * @param s
     * @param c
     * @return The number of character that appended.
     */
    int appendChar(String* s, char c);
    /**
     * Append given size of content of character array onto the String object.
     * @param s
     * @param ca
     * @param size
     * @return The number of character that appended.
     */
    int appendString(String* s, char* ca, int size);
    /**
     * Split an String object by space into an 2D array where each word are fit 
     * in its corresponding position.
     * @param str
     * @param length The total length of splitted 2D
     * @return The 2D array than contains all words
     *
     */
    //char** stringSplit2Array(String* str, int* length);
#ifdef __cplusplus
}
#endif

#endif /* STRING_H */

