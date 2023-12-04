#include "Player.h"

Player::Player(GameMechs *thisGMRef, Food *food1)
{
    // Initialize member variables
    mainGameMechsRef = thisGMRef;
    f1 = food1;
    myDir = STOP;

    // Get dimensions of the game board
    bx = mainGameMechsRef->getBoardSizeX();
    by = mainGameMechsRef->getBoardSizeY();

    // Initialize player position
    playerPos = new objPosArrayList();
    objPos p(bx / 2, by / 2, '@');
    playerPos->insertHead(p); // Instantiate first player position
}

Player::~Player()
{
    // Destructor: clean up dynamically allocated memory
    playerPos->kill();
    delete playerPos;
}

objPosArrayList *Player::getPlayerPos()
{
    // Return the reference to the playerPos array list
    return playerPos;
}

void Player::updatePlayerDir()
{
    // Update player direction based on input
    char input = mainGameMechsRef->getInput();
    mainGameMechsRef->clearInput();

    if (input != 0) // If not null character
    {
        switch (input)
        {
        case ' ':
            mainGameMechsRef->setExitTrue();
            break;
        case 'w':
            if (myDir != DOWN)
                myDir = UP;
            break;
        // Add more key processing here
        case 'a':
            if (myDir != RIGHT)
                myDir = LEFT;
            break;
        case 's':
            if (myDir != UP)
                myDir = DOWN;
            break;
        case 'd':
            if (myDir != LEFT)
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
    // Move the player based on the current direction
    objPos p;
    playerPos->getHeadElement(p);
    int x = p.x;
    int y = p.y;

    // Move in the specified direction
    if (myDir == LEFT)
    {
        x--;
        p = objPos(x, y, '@');
        playerPos->insertHead(p);
    }
    else if (myDir == RIGHT)
    {
        x++;
        p = objPos(x, y, '@');
        playerPos->insertHead(p);
    }
    else if (myDir == DOWN)
    {
        y++;
        p = objPos(x, y, '@');
        playerPos->insertHead(p);
    }
    else if (myDir == UP)
    {
        y--;
        p = objPos(x, y, '@');
        playerPos->insertHead(p);
    }

    // Border wraparound logic
    if (y == 0)
    {
        y = by - 2;
        playerPos->removeHead();
        p = objPos(x, y, '@');
        playerPos->insertHead(p);
    }
    else if (y == by - 1)
    {
        y = 1;
        playerPos->removeHead();
        p = objPos(x, y, '@');
        playerPos->insertHead(p);
    }
    if (x == bx - 1)
    {
        x = 1;
        playerPos->removeHead();
        p = objPos(x, y, '@');
        playerPos->insertHead(p);
    }
    else if (x == 0)
    {
        x = bx - 2;
        playerPos->removeHead();
        p = objPos(x, y, '@');
        playerPos->insertHead(p);
    }

    // Check for self-collision
    if (playerPos->getSize() > 5)
    {
        bool suicided = this->checkSelfCollision();
        if (suicided == true)
        {
            mainGameMechsRef->setExitTrue();
            mainGameMechsRef->setLoseTrue();
            playerPos->removeHead();
        }
    }

    // Check for food consumption
    bool foodConsumed = this->checkFoodConsumption();
    if (myDir != STOP && !foodConsumed)
    {
        playerPos->removeTail();
    }
    else if (myDir != STOP && foodConsumed)
    {
        f1->generateFood(*playerPos);
    }
}

// Returns true if collided with food, false if not
bool Player::checkFoodConsumption()
{
    objPosArrayList fl = f1->getFoodPos();
    objPos p, f;
    bool hit = false;
    int sum;
    playerPos->getHeadElement(p);
    for (int k = 0; k < 5; k++)
    {
        fl.getElement(f, k);
        if (p.x == f.x && p.y == f.y)
        {
            hit = true;
            // Normal food, 1 score
            if (f.symbol == '+')
                mainGameMechsRef->incrementScore(1);
            else if (f.symbol == '-') // Bad food -1 score
                mainGameMechsRef->incrementScore(-1);
            else if (f.symbol == '!') // Great food score +5
                mainGameMechsRef->incrementScore(5);
            else if (f.symbol == '|') // Terrible food, sets score to 0
                mainGameMechsRef->incrementScore(mainGameMechsRef->getScore() * -1);
            else if (f.symbol == '?')
            { // Strange food "randomly" does actions based on factors of coordinates and score (bad things more likely) stacks each modifier if they line up
                sum = f.x + f.y + mainGameMechsRef->getScore();
                if (sum % 5 == 0)
                    mainGameMechsRef->incrementScore(10); // Increases by 10 if sum is divisible by 5
                if (sum % 2 == 0)
                    mainGameMechsRef->incrementScore((mainGameMechsRef->getScore() / 2) * -1); // Halves the score if sum is even
                if (sum % 13 == 0)
                    mainGameMechsRef->incrementScore(-100); // Extreme bad luck! Divisible by 13 -100 score
                if (sum % 7 == 0)
                    mainGameMechsRef->incrementScore(100); // Good luck! Divisible by 7 +100 score
                // It is possible for nothing to happen as well ex. any prime number not listed above,
            }
        }
    }
    return hit;
}

// Returns true if collided with self, false if not
bool Player::checkSelfCollision()
{
    objPos p, h; // Head and body segment position

    // Initialize a 2D array to represent the visited grid
    int vGrid[bx][by];
    for (int k = 0; k < bx; k++)
    {
        for (int j = 0; j < by; j++)
        {
            vGrid[k][j] = 0;
        }
    }

    // Mark visited positions on the grid
    for (int i = 1; i < playerPos->getSize(); i++)
    {
        playerPos->getElement(p, i);
        vGrid[p.x][p.y] = 1;
    }

    // Check for collision with the head
    playerPos->getHeadElement(h);
    if (vGrid[h.x][h.y] == 1)
        return true;
    else
        return false;
}
