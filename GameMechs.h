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
    char input;            // Stores user input
    bool exitFlag, loseFlag; // Flags indicating game status
    int boardSizeX;         // Width of the game board
    int boardSizeY;         // Height of the game board
    int score;              // Player's score

public:
    GameMechs();                                // Default constructor
    GameMechs(int boardX, int boardY);         // Parameterized constructor
    ~GameMechs();                               // Destructor

    bool getExitFlagStatus();                   // Get the status of the exit flag
    void setExitTrue();                         // Set the exit flag to true

    bool getLoseFlagStatus();                   // Get the status of the lose flag
    void setLoseTrue();                         // Set the lose flag to true

    char getInput();                            // Get user input
    void setInput(char this_input);             // Set user input
    void clearInput();                          // Clear user input

    int getBoardSizeX();                        // Get the width of the game board
    int getBoardSizeY();                        // Get the height of the game board

    objPos foodPos;                             // Current position of the food
    objPosArrayList foodList;                   // List of food positions
    void generateFood(objPosArrayList blockOff); // Generate food on the game board
    void getFoodPos(objPos &returnPos);         // Get the position of the food

    void incrementScore(int num);               // Increment the player's score
    int getScore();                             // Get the player's score
};

#endif
