#include "GameMechs.h"

#include "GameMechs.h"

GameMechs::GameMechs()
{
    boardSizeX = 20;
    boardSizeY = 10;
    exitFlag = false;
    input = 0;
    srand(time(NULL)); // Initialize random seed
}

GameMechs::GameMechs(int boardX, int boardY)
{
    boardSizeX = boardX;
    boardSizeY = boardY;
    exitFlag = false;
    input = 0;
    srand(time(NULL)); // Initialize random seed
}

bool GameMechs::getExitFlagStatus()
{
    return exitFlag;
}

char GameMechs::getInput()
{
    return input;
}

int GameMechs::getBoardSizeX()
{
    return boardSizeX;
}

int GameMechs::getBoardSizeY()
{
    return boardSizeY;
}

void GameMechs::setExitTrue()
{
    exitFlag = true;
}

void GameMechs::setInput(char this_input)
{
    input = this_input;
}

void GameMechs::clearInput()
{
    input = 0;
}

void GameMechs::generateFood()
{
    // Generate random x and y coordinates for the food
    int foodX = rand() % (boardSizeX - 2) + 1; // Avoid placing food on the borders
    int foodY = rand() % (boardSizeY - 2) + 1;

    // Create a new food position and add it to the food list
    objPos foodPos(foodX, foodY, '*');
    foodList.insertTail(foodPos);
}

void GameMechs::getFoodList(objPosArrayList &returnList)
{
    // Get the list of food positions
    foodList = returnList;
}