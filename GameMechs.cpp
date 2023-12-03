#include "GameMechs.h"

GameMechs::GameMechs()
{
    boardSizeX = 20;
    boardSizeY = 10;
    exitFlag = false;
    input = 0;
}

GameMechs::GameMechs(int boardX, int boardY)
{
    boardSizeX = boardX;
    boardSizeY = boardY;
    exitFlag = false;
    input = 0;
    score = 0;
}

GameMechs::~GameMechs()
{
    // Add any necessary cleanup logic for GameMechs
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

void GameMechs::generateFood(objPosArrayList blockOff)
{
    srand(time(NULL));  // Seed the random number generator
    
    int vGrid[boardSizeX][boardSizeY];
    for(int k = 0; k < boardSizeX; k++){
        for(int j = 0; j < boardSizeY; j++){
            vGrid[k][j] = 0;
        }
    }

    objPos p;

    for(int i = 0; i < blockOff.getSize(); i++){
        blockOff.getElement(p,i);
        vGrid[p.x][p.y] = 1;
    }
    // Generate random x and y coordinates for the food
    int randX = rand() % (boardSizeX - 2) + 1;  // Avoid borders
    int randY = rand() % (boardSizeY - 2) + 1;

    // Ensure the generated position is not on the player's position
    while (vGrid[randX][randY] == 1) {
        randX = rand() % (boardSizeX - 2) + 1;
        randY = rand() % (boardSizeY - 2) + 1;
    }

    // Set the food position
    foodPos.x = randX;
    foodPos.y = randY;
    foodPos.symbol = '+';  // 

    // Add the food to the food list
    foodList.insertHead(foodPos);
}

void GameMechs::getFoodPos(objPos &returnPos)
{
    returnPos = foodPos;
}

void GameMechs::incrementScore(){
    score++;
}
int GameMechs::getScore(){
    return score;
}