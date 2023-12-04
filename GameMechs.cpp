#include "GameMechs.h"

GameMechs::GameMechs()
{
    // Default constructor: Initialize board size and flags
    boardSizeX = 20;   // Default width of the game board
    boardSizeY = 10;   // Default height of the game board
    exitFlag = false;  // Default exit flag status
    loseFlag = false;  // Default lose flag status
    input = 0;         // Default user input
    score = 0;         // Default player score
}

GameMechs::GameMechs(int boardX, int boardY)
{
    // Parameterized constructor: Initialize board size and flags
    boardSizeX = boardX;   // Set the width of the game board
    boardSizeY = boardY;   // Set the height of the game board
    exitFlag = false;      // Default exit flag status
    loseFlag = false;      // Default lose flag status
    input = 0;             // Default user input
    score = 0;             // Default player score
}

GameMechs::~GameMechs()
{
    // Destructor: Cleanup any dynamic memory or resources
    foodList.kill();  // Release memory used by the food list
}

bool GameMechs::getExitFlagStatus()
{
    return exitFlag;  // Return the status of the exit flag
}

bool GameMechs::getLoseFlagStatus()
{
    return loseFlag;  // Return the status of the lose flag
}

char GameMechs::getInput()
{
    return input;     // Return the current user input
}

int GameMechs::getBoardSizeX()
{
    return boardSizeX;  // Return the width of the game board
}

int GameMechs::getBoardSizeY()
{
    return boardSizeY;  // Return the height of the game board
}

void GameMechs::setExitTrue()
{
    exitFlag = true;  // Set the exit flag to true
}

void GameMechs::setLoseTrue()
{
    loseFlag = true;  // Set the lose flag to true
}

void GameMechs::setInput(char this_input)
{
    input = this_input;  // Set the user input
}

void GameMechs::clearInput()
{
    input = 0;  // Clear the user input
}

void GameMechs::incrementScore(int num)
{
    score += num;  // Increment the player's score by the specified amount
}

int GameMechs::getScore()
{
    return score;  // Return the player's score
}
