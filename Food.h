#ifndef FOOD_H
#define FOOD_H

#include <cstdlib>
#include <time.h>

#include "objPos.h"
#include "objPosArrayList.h"
#include "GameMechs.h"

class Food
{
public:
    // Constructor: Initializes the food with a reference to the current game
    Food(GameMechs* currGame);

    // Destructor
    ~Food();

    int bx, by;          // Board dimensions
    objPos foodPos;       // Current food position
    objPosArrayList foodList;  // List to store the food positions

    // Generates a new food position that is not blocked by obstacles
    void generateFood(objPosArrayList blockOff);

    // Returns the list containing the current food position
    objPosArrayList getFoodPos();
};

#endif
