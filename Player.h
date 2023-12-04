#ifndef PLAYER_H
#define PLAYER_H

// Include necessary headers
#include "GameMechs.h"
#include "objPos.h"
#include "objPosArrayList.h"
#include "Food.h"

// Player class declaration
class Player
{
public:
    // Enumeration representing player directions
    enum Dir { UP, DOWN, LEFT, RIGHT, STOP };

    // Constructor and destructor
    Player(GameMechs *thisGMRef, Food *f1);
    ~Player();

    // Getter for player position
    objPosArrayList *getPlayerPos();

    // Methods to update and move the player
    void updatePlayerDir();
    void movePlayer();

    // Methods to check for food consumption and self-collision
    bool checkFoodConsumption();
    bool checkSelfCollision();

    // Direction of the player
    enum Dir myDir;

private:
    // Player's position in the game
    objPosArrayList *playerPos;

    // Dimensions of the game board
    int bx, by;

    // Reference to the Food object
    Food *f1;

    // Reference to the main game mechanics
    GameMechs *mainGameMechsRef;
};

#endif
