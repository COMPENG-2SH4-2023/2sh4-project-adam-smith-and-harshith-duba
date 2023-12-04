#ifndef OBJPOS_ARRAYLIST_H
#define OBJPOS_ARRAYLIST_H

#define ARRAY_MAX_CAP 200

#include "objPos.h"

class objPosArrayList
{
private:
    objPos *aList;   // Dynamic array to store objPos elements
    int sizeList;    // Current number of elements in the list
    int sizeArray;   // Capacity of the dynamic array

public:
    objPosArrayList();   // Constructor: initializes the object
    ~objPosArrayList();  // Destructor: cleans up dynamically allocated memory

    int getSize();  // Returns the current number of elements in the list

    // Inserts an objPos element at the beginning of the list
    void insertHead(objPos thisPos);

    // Inserts an objPos element at the end of the list
    void insertTail(objPos thisPos);

    // Removes the objPos element at the beginning of the list
    void removeHead();

    // Removes the objPos element at the end of the list
    void removeTail();

    // Deallocates the dynamic array and sets the list size to 0
    void kill();

    // Retrieves the objPos element at the beginning of the list
    void getHeadElement(objPos &returnPos);

    // Retrieves the objPos element at the end of the list
    void getTailElement(objPos &returnPos);

    // Retrieves the objPos element at a specified index in the list
    void getElement(objPos &returnPos, int index);
};

#endif
