#include "objPosArrayList.h"

objPosArrayList::objPosArrayList()
{
    sizeList = 0;           // Initialize the current number of elements to 0
    sizeArray = ARRAY_MAX_CAP;  // Set the capacity of the dynamic array
    aList = new objPos[sizeArray];  // Allocate memory for the dynamic array
}

objPosArrayList::~objPosArrayList()
{
    // delete[] aList;
}

void objPosArrayList::kill()
{
    delete[] aList;  // Deallocate the dynamic array to prevent memory leaks
}

int objPosArrayList::getSize()
{
    return sizeList;  // Return the current number of elements in the list
}

void objPosArrayList::insertHead(objPos thisPos)
{
    if (sizeList < sizeArray)
    {
        // Shift elements to make space for the new head
        for (int i = sizeList; i > 0; --i)
        {
            aList[i] = aList[i - 1];
        }
        aList[0] = thisPos;  // Insert the new head at the beginning of the list
        ++sizeList;  // Increment the size of the list
    }
}

void objPosArrayList::insertTail(objPos thisPos)
{
    if (sizeList < sizeArray)
    {
        aList[sizeList] = thisPos;  // Insert the new element at the end of the list
        ++sizeList;  // Increment the size of the list
    }
}

void objPosArrayList::removeHead()
{
    if (sizeList > 0)
    {
        // Shift elements to remove the head
        for (int i = 0; i < sizeList - 1; ++i)
        {
            aList[i] = aList[i + 1];
        }
        --sizeList;  // Decrement the size of the list
    }
}

void objPosArrayList::removeTail()
{
    if (sizeList > 0)
    {
        --sizeList;  // Simply decrease the size to remove the tail
    }
}

void objPosArrayList::getHeadElement(objPos &returnPos)
{
    if (sizeList > 0)
    {
        returnPos = aList[0];  // Retrieve the element at the beginning of the list
    }
}

void objPosArrayList::getTailElement(objPos &returnPos)
{
    if (sizeList > 0)
    {
        returnPos = aList[sizeList - 1];  // Retrieve the element at the end of the list
    }
}

void objPosArrayList::getElement(objPos &returnPos, int index)
{
    if (index >= 0 && index < sizeList)
    {
        returnPos = aList[index];  // Retrieve the element at the specified index
    }
}
