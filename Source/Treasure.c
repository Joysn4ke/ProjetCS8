#include <stdlib.h>
#include <stdio.h>
#include "assert.h"

#include "Common.h"
#include "Treasure.h"

struct Treasure_s{
    int position_x;
    int position_y;;
};

extern Treasure* newTreasure() {
    Treasure* this = (Treasure*)calloc(1, sizeof(Treasure));
    assert(this != NULL);  //Memory allocation's verification
    return this;
}

extern void treasureInitialisation(Treasure* this, int localX, int localY) {
    assert(this != NULL);  //Valid object's verification
    if (0 <= localX && localX < LINE && 0 <= localY && localY < COLUMN) {
        this->position_x = localX;
        this->position_y = localY;
    } else {
        this->position_x = LINE - 1;
        this->position_y = COLUMN - 1;
    }
}

extern void freeTreasure(Treasure* this) {
    if (this != NULL) {  //Check that the object is not NULL before freeing the memory
        free(this);
    }
}


// Getter & Setter
extern int getPosTreasureX(Treasure* Treasure) {
    assert(Treasure != NULL);
    return Treasure->position_x;
}

extern int getPosTreasureY(Treasure* Treasure) {
    assert(Treasure != NULL);
    return Treasure->position_y;
}

extern void setPosTreasureX(Treasure* Treasure, int x) {
    assert(Treasure != NULL);
    assert(x >= 0 && x < LINE);
    Treasure->position_x = x;
}

extern void setPosTreasureY(Treasure* Treasure, int y) {
    assert(Treasure != NULL);
    assert(y >= 0 && y < COLUMN);
    Treasure->position_y = y;
}
