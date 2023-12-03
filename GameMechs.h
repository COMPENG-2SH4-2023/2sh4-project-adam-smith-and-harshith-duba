#ifndef GAMEMECHS_H
#define GAMEMECHS_H

#include <cstdlib>
#include <time.h>

#include "objPos.h"
#include "objPosArrayList.h"

using namespace std;

class GameMechs
{
private:
    char input;
    bool exitFlag;
    int boardSizeX;
    int boardSizeY;
    objPosArrayList foodList;
    objPos foodPos;  // Added foodPos member

public:
    GameMechs();
    GameMechs(int boardX, int boardY);
    ~GameMechs();

    bool getExitFlagStatus();
    void setExitTrue();

    char getInput();
    void setInput(char this_input);
    void clearInput();

    int getBoardSizeX();
    int getBoardSizeY();

    void generateFood(objPos blockOff);
    void getFoodPos(objPos &returnPos);
};

#endif
