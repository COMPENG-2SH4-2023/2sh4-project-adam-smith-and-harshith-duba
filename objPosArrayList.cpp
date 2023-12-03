#include "objPosArrayList.h"

objPosArrayList::objPosArrayList()
{
    sizeList = 0;
    sizeArray = ARRAY_MAX_CAP;
    aList = new objPos[sizeArray];
}

objPosArrayList::~objPosArrayList()
{
    delete[] aList;
}

int objPosArrayList::getSize()
{
    return sizeList;
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
        aList[0] = thisPos;
        ++sizeList;
    }
}

void objPosArrayList::insertTail(objPos thisPos)
{
    if (sizeList < sizeArray)
    {
        aList[sizeList] = thisPos;
        ++sizeList;
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
        --sizeList;
    }
}

void objPosArrayList::removeTail()
{
    if (sizeList > 0)
    {
        --sizeList; // Simply decrease the size to remove the tail
    }
}

void objPosArrayList::getHeadElement(objPos &returnPos)
{
    if (sizeList > 0)
    {
        returnPos = aList[0];
    }
}

void objPosArrayList::getTailElement(objPos &returnPos)
{
    if (sizeList > 0)
    {
        returnPos = aList[sizeList - 1];
    }
}

void objPosArrayList::getElement(objPos &returnPos, int index)
{
    if (index >= 0 && index < sizeList)
    {
        returnPos = aList[index];
    }
}
