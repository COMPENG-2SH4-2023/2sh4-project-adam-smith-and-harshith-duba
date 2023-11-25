#include "Player.h"


Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;
    playerPos = objPos(10,5,'*');
    // more actions to be included
}


Player::~Player()
{
    // delete any heap members here
}

void Player::getPlayerPos(objPos &returnPos)
{
    // return the reference to the playerPos array list
    playerPos.getObjPos(returnPos);
}

void Player::updatePlayerDir()
{
    // PPA3 input processing logic   
    char input = mainGameMechsRef->getInput();
    mainGameMechsRef->clearInput();
    if(input != 0)  // if not null character
    {
        switch(input)
        {
            case ' ':
                mainGameMechsRef->setExitTrue();
                break;
            case 'w':
                if(myDir != DOWN)
                    myDir = UP;
                break;
            // Add more key processing here
            case 'a':
                if(myDir != RIGHT)
                    myDir = LEFT;
                break;
            case 's':
                if(myDir != UP)
                    myDir = DOWN;
                break;
            case 'd':
                if(myDir != LEFT)
                    myDir = RIGHT;
                break;
            default:
                break;
        }
        input = 0;
    }
}

void Player::movePlayer()
{
    // PPA3 Finite State Machine logic
    if(myDir == LEFT){
        playerPos.x--;
    }
    else if(myDir == RIGHT){
        playerPos.x++;
    }
    else if(myDir == DOWN){
        playerPos.y++;
    }
    else if(myDir == UP){
        playerPos.y--;
    }
    //border wraparound
    if(playerPos.y == 0){
        playerPos.y = mainGameMechsRef->getBoardSizeY()-2;
    }
    else if(playerPos.y == mainGameMechsRef->getBoardSizeY()-1){
        playerPos.y = 1;
    }
    if(playerPos.x == mainGameMechsRef->getBoardSizeX()-1){
        playerPos.x = 1;
    }
    else if(playerPos.x == 0){
        playerPos.x = mainGameMechsRef->getBoardSizeX()-2;
    }
}

