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
    if (MacUILib_hasChar() == 1)
    {
        char in = MacUILib_getChar();
        bool unprinted = true;
        while (unprinted)
        {
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
    p1->updatePlayerDir();
    p1->movePlayer();
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
    for (i = 0; i < by; i++)
    {
        int ct = 0;
        for (j = 0; j < bx; j++)
        {
            for(k = 0; k < ppos->getSize(); k++){
                ppos->getElement(p, k);
                py = p.y;
                px = p.x;
                ps = p.symbol;
                if (i == py && j == px && printed == false){
                    line[ct] = ps;
                    ct++;
                    printed = true;
                }
            }
            for(int o = 0; o < 5; o++){
                f1->getFoodPos().getElement(foodPos, o);
                int fx = foodPos.x;
                int fy = foodPos.y;
                char fs = foodPos.symbol;
                if (i == fy && j == fx && printed == false){
                    line[ct] = fs;
                    ct++;
                    printed = true;
                }
            }
            if (i == 0 || i == by - 1 || j == 0 || j == bx - 1 && printed == false)
            {
                line[ct] = '#';
                ct++;
            }
            else if (printed == false)
            {
                line[ct] = ' ';
                ct++;
            }
            printed = false;
        }
        line[ct] = '\0';
        MacUILib_printf("%s",line);
        MacUILib_printf("\n");
    }
    //MacUILib_printf("%d,%d", px, py); //debug code
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST);
}

void CleanUp(void)
{
    MacUILib_clearScreen();
    
    MacUILib_printf("Game Ended. You Scored: %d.\n", currGame->getScore());

    MacUILib_uninit();

    delete currGame;
    delete p1;
}
