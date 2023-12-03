#ifndef GAMEMECHS_H
#define GAMEMECHS_H

#include <cstdlib>
#include <time.h>
#include "objPos.h"
#include "objPosArrayList.h"

class GameMechs
{
private:
    char input;
    bool exitFlag;
    int boardSizeX;
    int boardSizeY;
    objPosArrayList foodList; // New member to store food positions

public:
    GameMechs();
    GameMechs(int boardX, int boardY);

    bool getExitFlagStatus();
    void setExitTrue();

    char getInput();
    void setInput(char this_input);
    void clearInput();

    int getBoardSizeX();
    int getBoardSizeY();

    void generateFood(); // New method to generate random food
    void getFoodList(objPosArrayList &returnList); // New method to get the list of food positions
};

#endif