#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "assert.h"

#include "Game.h"
#include "Map.h"
#include "Player.h"
#include "Treasure.h"
#include "Common.h"

// struct Game_s{
//     Map *map;
//     Player *player;
//     Treasure *treasure;
// };

Game* newGame() {
    Game* this = (Game*)calloc(1, sizeof(Game));
    assert(this != NULL);  //Memory allocation's verification

    this->map = newMap();
    this->player = newPlayer();
    this->treasure = newTreasure();  //Test Leak Memmory

    return this;
}

void gameInitialisation(Game* this) {
    assert(this != NULL);  //Valid object's verification

    //rand() % (MAX - MIN + 1) + MIN;
    int playerX = rand() % (LINE - 0 + 1) + 0;
    int playerY = rand() % (COLUMN - 0 + 1) + 0;

    int treasureX = LINE - 1;
    int treasureY = COLUMN - 1;

    do {
        treasureX = rand() % (LINE - 0 + 1) + 0;
        treasureY = rand() % (COLUMN - 0 + 1) + 0;
    } while (treasureX == playerX || treasureY == playerY);


    playerInitialisation(this->player, playerX, playerY);
    treasureInitialisation(this->treasure, treasureX, treasureY);
    mapInitialisation(this->map);
    this->map->grid[this->player->position_x][this->player->position_y] = 'j';
}

void freeGame(Game* this) {
    if (this != NULL) {  //Check that the object is not NULL before freeing the memory
        freeMap(this->map);
        freePlayer(this->player);
        freeTreasure(this->treasure);

        free(this);
    }
}
