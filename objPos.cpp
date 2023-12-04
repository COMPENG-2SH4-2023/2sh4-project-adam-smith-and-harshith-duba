#include "objPos.h"

objPos::objPos()
{
    x = 0;             // Default constructor, initializes x-coordinate to 0
    y = 0;             // Initializes y-coordinate to 0
    symbol = 0;        // Initializes symbol to NULL
}

objPos::objPos(objPos &o)
{
    x = o.x;           // Copy constructor, copies x-coordinate from another objPos object
    y = o.y;           // Copies y-coordinate from another objPos object
    symbol = o.symbol; // Copies symbol from another objPos object
}

objPos::objPos(int xPos, int yPos, char sym)
{
    x = xPos;          // Parameterized constructor, initializes x-coordinate with provided value
    y = yPos;          // Initializes y-coordinate with provided value
    symbol = sym;      // Initializes symbol with provided value
}

void objPos::setObjPos(objPos o)
{
    x = o.x;           // Set the object's position using another objPos object
    y = o.y;           // Copy x and y coordinates
    symbol = o.symbol; // Copy symbol
}

void objPos::setObjPos(int xPos, int yPos, char sym)
{
    x = xPos;          // Set the object's position using individual values
    y = yPos;          // Set x and y coordinates
    symbol = sym;      // Set symbol
}

void objPos::getObjPos(objPos &returnPos)
{
    returnPos.setObjPos(x, y, symbol);  // Get the object's position
}

char objPos::getSymbol()
{
    return symbol;     // Get the symbol representing the object
}

bool objPos::isPosEqual(const objPos* refPos)
{
    return (refPos->x == x && refPos->y == y);  // Check if two positions are equal
}

char objPos::getSymbolIfPosEqual(const objPos* refPos)
{
    if (isPosEqual(refPos))
        return getSymbol();  // Get the symbol if positions are equal
    else
        return 0;            // Return 0 if positions are not equal
}
