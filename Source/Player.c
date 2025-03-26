#include <stdlib.h>
#include <stdio.h>
#include "assert.h"

#include "Common.h"
#include "Player.h"

// struct Player_s{
//     int position_x;
//     int position_y;;
// };

Player* newPlayer() {
    Player* this = (Player*)calloc(1, sizeof(Player));
    assert(this != NULL);  //Memory allocation's verification
    return this;
}

void playerInitialisation(Player* this, int localX, int localY) {
    assert(this != NULL);  //Valid object's verification
    if (0 <= localX < LINE && 0 <= localY < COLUMN) {
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
