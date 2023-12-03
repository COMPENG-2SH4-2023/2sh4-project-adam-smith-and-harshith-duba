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
    int score;

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

    objPos foodPos;  // Added foodPos member
    objPosArrayList foodList;
    void generateFood(objPosArrayList blockOff);
    void getFoodPos(objPos &returnPos);

    void incrementScore(int num);
    int getScore();
};

#endif
