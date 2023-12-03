#include "Food.h"


Food::Food(GameMechs* currGame){
    bx = currGame->getBoardSizeX();
    by = currGame->getBoardSizeY();
}

void Food::generateFood(objPosArrayList blockOff)
{
    srand(time(NULL));  // Seed the random number generator

    for(int j = 0; j < 3; j++)
        foodList.removeTail();
    
    int vGrid[bx][by];
    for(int k = 0; k < bx; k++){
        for(int j = 0; j < by; j++){
            vGrid[k][j] = 0;
        }
    }

    objPos p;

    for(int i = 0; i < blockOff.getSize(); i++){
        blockOff.getElement(p,i);
        vGrid[p.x][p.y] = 1;
    }
    char syms[5] = {'+','-','!','|','?'};
    for(int v = 0; v < 5; v++){
        // Generate random x and y coordinates for the food
        int randX = rand() % (bx - 2) + 1;  // Avoid borders
        int randY = rand() % (by - 2) + 1;
        // Ensure the generated position is not on the player's position
        while (vGrid[randX][randY] == 1) {
            randX = rand() % (bx - 2) + 1;
            randY = rand() % (by - 2) + 1;
        }

        // Set the food position
        foodPos.x = randX;
        foodPos.y = randY;
        foodPos.symbol = syms[v];  // 
        vGrid[randX][randY] = 1;
        // Add the food to the food list
        foodList.insertHead(foodPos);
    }
}

objPosArrayList Food::getFoodPos()
{
    return(foodList);
}