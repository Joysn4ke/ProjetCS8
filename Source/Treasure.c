#include <stdlib.h>
#include <stdio.h>
#include "assert.h"
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

extern void treasureInitialisation(Treasure* this) {
    assert(this != NULL);  //Valid object's verification
}

extern void freeTreasure(Treasure* this) {
    if (this != NULL) {  //Check that the object is not NULL before freeing the memory
        free(this);
    }
}
