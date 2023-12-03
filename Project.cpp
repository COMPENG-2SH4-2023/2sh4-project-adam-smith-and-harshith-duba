#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "Player.h"

using namespace std;

#define DELAY_CONST 100000

bool exitFlag;
Player *p1;
GameMechs *currGame;
objPosArrayList ppos;
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
    currGame = new GameMechs(20, 10);
    p1 = new Player(currGame);
    bx = currGame->getBoardSizeX();
    by = currGame->getBoardSizeY();
    
    p1->getPlayerPos(ppos);
    currGame->generateFood(ppos);
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
    exitFlag = currGame->getExitFlagStatus();
    p1->updatePlayerDir();
    p1->movePlayer();
}

void DrawScreen(void)
{
    MacUILib_clearScreen();
    int i, j, k, letter, printed;
    objPosArrayList pl;
    p1->getPlayerPos(pl);
    objPos p;
    pl.getHeadElement(p);
    int px = p.x;
    int py = p.y;
    char ps = p.symbol;

    objPos foodPos;
    currGame->foodList.getHeadElement(foodPos);
    int fx = foodPos.x;
    int fy = foodPos.y;
    char fs = foodPos.symbol;

    for (i = 0; i < by; i++)
    {
        for (j = 0; j < bx; j++)
        {
            for(k = 0; k < pl.getSize(); k++){
                pl.getElement(p, k);
                py = p.y;
                px = p.x;
                ps = p.symbol;
                if (i == py && j == px){
                    MacUILib_printf("%c", ps);
                    printed = true;
                }
            }
            if (i == 0 || i == by - 1 || j == 0 || j == bx - 1 && printed == false)
            {
                MacUILib_printf("#");
            }
            else if (i == fy && j == fx && printed == false)
            {
                MacUILib_printf("%c", fs);
            }
            else if (printed == false)
            {
                MacUILib_printf(" ");
            }
            printed = false;
        }
        MacUILib_printf("\n");
    }
    //DEBUG CODE MacUILib_printf("%d,%d", px, py);
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST);
}

void CleanUp(void)
{
    MacUILib_clearScreen();
    MacUILib_uninit();
    delete currGame;
    delete p1;
}
