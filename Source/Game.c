#include <stdlib.h>
#include <stdio.h>
#include "assert.h"

#include "Game.h"
#include "Map.h"
#include "Player.h"
#include "Treasure.h"

struct Game_s{
    Map *map;
    Player *player;
    Treasure *treasure;
};

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
}

void gameFree(Game* this) {
    if (this != NULL) {  //Check that the object is not NULL before freeing the memory
        freeMap(this->map);
        freePlayer(this->player);
        freeTreasure(this->treasure);

        free(this);
    }
}
