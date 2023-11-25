#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "Player.h"

using namespace std;

#define DELAY_CONST 100000

bool exitFlag;
Player *p1;
GameMechs *currGame;
int bx,by;

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);



int main(void)
{

    Initialize();

    while(exitFlag == false)  
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
    //default
    MacUILib_init();
    MacUILib_clearScreen();
    exitFlag = false;
    //added
    currGame = new GameMechs(20,10); //Resize board (x,y)
    p1 = new Player(currGame);
    bx = currGame->getBoardSizeX();
    by = currGame->getBoardSizeY();
}

void GetInput(void)
{
    if(MacUILib_hasChar() == 1){
        char in = MacUILib_getChar();
        bool unprinted = true;
        while(unprinted){
            if(in != currGame->getInput()){
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
    objPos plr;
    p1->getPlayerPos(plr);
    int px = plr.x;
    int py = plr.y;
    char ps = plr.symbol;

    for (i = 0; i<by; i++){
        for(j = 0; j<bx; j++){
            if(i == 0 || i == by-1|| j == 0 || j == bx-1){
                MacUILib_printf("#");        
            }
            else if(i == py && j == px){
                MacUILib_printf("%c",ps);
            }
            else{
                MacUILib_printf(" ");
            }
            /*   THIS IS OLD CODE FOR PRINTING THE LETTERS (MIGHT BE USEFUL FOR FOOD)
            else{
                for(k = 0; k < LETTERS; k++){
                    if(i==listt[k].y && j == listt[k].x){
                        MacUILib_printf("%c", listt[k].symbol);
                        printed = 1;
                    }
                }
                if(printed == 0){
                    MacUILib_printf(" ");
                }
            }
            printed = 0; */
        }
        MacUILib_printf("\n");
    }
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    MacUILib_clearScreen();    
  
    MacUILib_uninit();

    delete currGame;
    delete p1;
}
