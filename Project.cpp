#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "Player.h"
#include "Food.h"
using namespace std;

#define DELAY_CONST 100000

bool exitFlag;
Player *p1 = NULL;
GameMechs *currGame = NULL;
objPosArrayList *ppos = NULL;
objPos p;
Food *f1;
int bx, by;

// Function prototypes
void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);

int main(void)
{
    Initialize();

    while (exitFlag == false)
    {
        GetInput();
        RunLogic();
        DrawScreen();
        LoopDelay();
    }
    CleanUp();
}

void Initialize(void)
{
    MacUILib_init();
    MacUILib_clearScreen();
    exitFlag = false;

    // Initialize the game mechanics, player, and food
    currGame = new GameMechs(30, 15);
    bx = currGame->getBoardSizeX();
    by = currGame->getBoardSizeY();
    f1 = new Food(currGame);
    p1 = new Player(currGame, f1);
    ppos = p1->getPlayerPos();
    f1->generateFood(*ppos);
}

void GetInput(void)
{
    // Check for user input and update the game mechanics
    if (MacUILib_hasChar() == 1)
    {
        char in = MacUILib_getChar();
        bool unprinted = true;
        while (unprinted)
        {
            // Set the input in the game mechanics if it has changed
            if (in != currGame->getInput())
            {
                currGame->setInput(in);
                unprinted = false;
            }
            else
                in = MacUILib_getChar();
        }
    }
}

void RunLogic(void)
{
    // Update player direction and move player
    p1->updatePlayerDir();
    p1->movePlayer();
    // Update the exit flag based on game mechanics
    exitFlag = currGame->getExitFlagStatus();
}

void DrawScreen(void)
{
    MacUILib_clearScreen();
    int i, j, k, letter, printed;
    ppos = p1->getPlayerPos();
    ppos->getHeadElement(p);

    int px = p.x;
    int py = p.y;
    char ps = p.symbol;

    objPos foodPos;
    f1->getFoodPos().getHeadElement(foodPos);
    int fx = foodPos.x;
    int fy = foodPos.y;
    char fs = foodPos.symbol;
    char line[bx];
    int ct = 0;

    // Iterate through each row of the game board
    for (i = 0; i < by; i++)
    {
        // Reset the counter for each new row
        int ct = 0;

        // Iterate through each column of the game board
        for (j = 0; j < bx; j++)
        {
            // Check if the current position matches the player's position and hasn't been printed yet
            for (k = 0; k < ppos->getSize(); k++)
            {
                ppos->getElement(p, k);
                py = p.y;
                px = p.x;
                ps = p.symbol;
                if (i == py && j == px && printed == false)
                {
                    line[ct] = ps; // Assign the player's symbol to the line array
                    ct++;
                    printed = true; // Set the flag to indicate the symbol has been printed
                }
            }

            // Check if the current position matches the food's position and hasn't been printed yet
            for (int o = 0; o < 5; o++)
            {
                f1->getFoodPos().getElement(foodPos, o);
                int fx = foodPos.x;
                int fy = foodPos.y;
                char fs = foodPos.symbol;
                if (i == fy && j == fx && printed == false)
                {
                    line[ct] = fs; // Assign the food's symbol to the line array
                    ct++;
                    printed = true; // Set the flag to indicate the symbol has been printed
                }
            }

            // Check if the current position is at the border of the game board and hasn't been printed yet
            if (i == 0 || i == by - 1 || j == 0 || j == bx - 1 && printed == false)
            {
                line[ct] = '#'; // Assign '#' to represent the border
                ct++;
            }
            else if (printed == false)
            {
                line[ct] = ' '; // Assign ' ' to represent an empty space
                ct++;
            }
            printed = false; // Reset the printed flag for the next iteration
        }

        // Null-terminate the line array to create a C-style string
        line[ct] = '\0';

        // Print the line to the screen
        MacUILib_printf("%s", line);
        MacUILib_printf("\n");
    }

    // Print the player's score
    MacUILib_printf("score: %d\n", currGame->getScore());

    // Get the player's head element for additional information
    ppos->getHeadElement(p);
    py = p.y;
    px = p.x;
    char d = 'S';
    switch (p1->myDir)
    {
    case 0:
        d = 'U';
        break;
    case 2:
        d = 'L';
        break;
    case 1:
        d = 'D';
        break;
    case 3:
        d = 'R';
    }

    // Print additional debugging information
    MacUILib_printf("\n======DEBUG MESSAGE======\n");
    MacUILib_printf("Board Size: %d X %d\n", bx, by);
    MacUILib_printf("Player Direction: %c\n", d);
    MacUILib_printf("Player Position: %d, %d\n", px, py); // Debug code
}

void LoopDelay(void)
{
    // Introduce a delay to control the speed of the game
    MacUILib_Delay(DELAY_CONST);
}

void CleanUp(void)
{
    MacUILib_clearScreen();

    // Display game over message with the final score
    if (currGame->getLoseFlagStatus() == true)
        MacUILib_printf("You Lost! You Scored: %d.\n", currGame->getScore());
    else
        MacUILib_printf("Game Ended. You Scored: %d.\n", currGame->getScore());

    // Clean up and release allocated memory
    MacUILib_uninit();
    delete currGame;
    delete p1;
}
