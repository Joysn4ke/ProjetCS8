#include <stdlib.h>
#include <stdio.h>
#include "assert.h"

#include "Common.h"
#include "Player.h"

struct Player_s{
    int position_x;
    int position_y;
    int health;
};

extern Player* newPlayer() {
    Player* this = (Player*)calloc(1, sizeof(Player));
    assert(this != NULL);  //Memory allocation's verification
    return this;
}

extern void playerInitialisation(Player* this, int localX, int localY) {
    assert(this != NULL);  //Valid object's verification
    if (0 <= localX && localX < LINE && 0 <= localY && localY < COLUMN) {
        this->position_x = localX;
        this->position_y = localY;
    } else {
        this->position_x = 0;
        this->position_y = 0;
    }
    this->health = HEALTHPLAYER;
}

extern void freePlayer(Player* this) {
    if (this != NULL) {  //Check that the object is not NULL before freeing the memory
        free(this);
    }
}


// Getter & Setter
extern int getPosPlayerX(Player* player) {
    assert(player != NULL);
    return player->position_x;
}

extern int getPosPlayerY(Player* player) {
    assert(player != NULL);
    return player->position_y;
}

extern void setPosPlayerX(Player* player, int x) {
    assert(player != NULL);
    assert(x >= 0 && x < LINE);
    player->position_x = x;
}

extern void setPosPlayerY(Player* player, int y) {
    assert(player != NULL);
    assert(y >= 0 && y < COLUMN);
    player->position_y = y;
}
