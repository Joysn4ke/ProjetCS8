#include <stdlib.h>
#include <stdio.h>
#include "assert.h"

#include "Common.h"
#include "Player.h"

struct Player_s{
    int position_x;
    int position_y;;
};

Player* newPlayer() {
    Player* this = (Player*)calloc(1, sizeof(Player));
    assert(this != NULL);  //Memory allocation's verification
    return this;
}

void playerInitialisation(Player* this, int localX, int localY) {
    assert(this != NULL);  //Valid object's verification
    if (0 <= localX && localX < LINE && 0 <= localY && localY < COLUMN) {
        this->position_x = localX;
        this->position_y = localY;
    } else {
        this->position_x = 0;
        this->position_y = 0;
    }
}

void freePlayer(Player* this) {
    if (this != NULL) {  //Check that the object is not NULL before freeing the memory
        free(this);
    }
}


// Getter & Setter
int getPlayerX(Player* player) {
    assert(player != NULL);
    return player->position_x;
}

int getPlayerY(Player* player) {
    assert(player != NULL);
    return player->position_y;
}

void setPlayerX(Player* player, int x) {
    assert(player != NULL);
    assert(x >= 0 && x < LINE);
    player->position_x = x;
}

void setPlayerY(Player* player, int y) {
    assert(player != NULL);
    assert(y >= 0 && y < COLUMN);
    player->position_y = y;
}