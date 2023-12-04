#ifndef OBJPOS_H
#define OBJPOS_H

class objPos
{
    public:
        int x;           // X-coordinate of the position
        int y;           // Y-coordinate of the position
        char symbol;     // Symbol representing the object at this position

        objPos();                  // Default constructor
        objPos(objPos &o);         // Copy constructor
        objPos(int xPos, int yPos, char sym);  // Parameterized constructor

        void setObjPos(objPos o);         // Set the object's position using another objPos object
        void setObjPos(int xPos, int yPos, char sym);  // Set the object's position using individual values
        void getObjPos(objPos &returnPos);  // Get the object's position
        char getSymbol();             // Get the symbol representing the object

        bool isPosEqual(const objPos* refPos);  // Check if two positions are equal

        char getSymbolIfPosEqual(const objPos* refPos);  // Get the symbol if positions are equal
};

#endif
