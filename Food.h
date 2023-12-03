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

        Food(GameMechs* currGame);
        ~Food();
        int bx,by;
        objPos foodPos;  // Added foodPos member
        objPosArrayList foodList;
        void generateFood(objPosArrayList blockOff);
        objPosArrayList getFoodPos();
};

#endif