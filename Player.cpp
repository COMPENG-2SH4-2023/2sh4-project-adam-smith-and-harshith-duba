#include "Player.h"


Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;
    bx = mainGameMechsRef->getBoardSizeX();
    by = mainGameMechsRef->getBoardSizeY();
    // more actions to be included
    playerPos = new objPosArrayList();
    objPos p;
    p = objPos(10,5,'@');
    playerPos->insertHead(p); // instantiates first player position
}


Player::~Player()
{
    // delete any heap members here
    delete playerPos;
}

void Player::getPlayerPos(objPosArrayList &returnPos)
{
    // return the reference to the playerPos array list
    returnPos = *playerPos;
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
    objPos p;
    playerPos->getHeadElement(p);
    int x = p.x;
    int y = p.y;

    if(myDir == LEFT){
        x--;
        p = objPos(x,y,'@');
        playerPos->insertHead(p);
    }
    else if(myDir == RIGHT){
        x++;
        p = objPos(x,y,'@');
        playerPos->insertHead(p);
    }
    else if(myDir == DOWN){
        y++;
        p = objPos(x,y,'@');
        playerPos->insertHead(p);
    }
    else if(myDir == UP){
        y--;
        p = objPos(x,y,'@');
        playerPos->insertHead(p);
    }
    //border wraparound
    if(y == 0){
        y = by-2;
        playerPos->removeHead();
        p = objPos(x,y,'@');
        playerPos->insertHead(p);
    }
    else if(y == by-1){
        y = 1;
        playerPos->removeHead();
        p = objPos(x,y,'@');
        playerPos->insertHead(p);
    }
    if(x == bx-1){
        x = 1;
        playerPos->removeHead();
        p = objPos(x,y,'@');
        playerPos->insertHead(p);
    }
    else if(x == 0){
        x = bx-2;
        playerPos->removeHead();
        p = objPos(x,y,'@');
        playerPos->insertHead(p);
    }

    if(mainGameMechsRef->getScore() > 3){
        bool suicided = this->checkSelfCollision();
        if(suicided == true){
            mainGameMechsRef->setExitTrue();
            playerPos->removeHead();
        }
    }

    bool foodConsumed = this->checkFoodConsumption();
    if(myDir != STOP && !foodConsumed){
        playerPos->removeTail();
    }
    else if(myDir != STOP && foodConsumed){
        mainGameMechsRef->generateFood(*playerPos);
        mainGameMechsRef->incrementScore();
    }
}

// returns true if collided with food, false if not
bool Player::checkFoodConsumption(){
    objPos p,f;
    playerPos->getHeadElement(p);
    mainGameMechsRef->getFoodPos(f);
    if(p.x == f.x && p.y == f.y){
        return true;
    }
    else
        return false;
}

// returns true if collided with self, false if not
bool Player::checkSelfCollision(){
    objPos p, h; //head and body segment position

    int vGrid[bx][by];
    for(int k = 0; k < bx; k++){
        for(int j = 0; j < by; j++){
            vGrid[k][j] = 0;
        }
    }

    for(int i = 1; i < playerPos->getSize(); i++){
        playerPos->getElement(p,i);
        vGrid[p.x][p.y] = 1;
    }


    playerPos->getHeadElement(h);
    if(vGrid[h.x][h.y] == 1)
        return true;
    else
        return false;
}