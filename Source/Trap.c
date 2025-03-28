#include <stdlib.h>
#include <stdio.h>
#include "assert.h"

#include "Common.h"
#include "Trap.h"

struct Trap_s{
    int position_x;
    int position_y;;
};

extern Trap* newTrap() {
    Trap* this = (Trap*)calloc(1, sizeof(Trap));
    assert(this != NULL);  //Memory allocation's verification
    return this;
}

extern void TrapInitialisation(Trap* this, int localX, int localY) {
    assert(this != NULL);  //Valid object's verification
    if (0 <= localX && localX < LINE && 0 <= localY && localY < COLUMN) {
        this->position_x = localX;
        this->position_y = localY;
    } else {
        this->position_x = LINE - 1;
        this->position_y = COLUMN - 1;
    }
}

extern void freeTrap(Trap* this) {
    if (this != NULL) {  //Check that the object is not NULL before freeing the memory
        free(this);
    }
}


// Getter & Setter
extern int getPosTrapX(Trap* Trap) {
    assert(Trap != NULL);
    return Trap->position_x;
}

extern int getPosTrapY(Trap* Trap) {
    assert(Trap != NULL);
    return Trap->position_y;
}

extern void setPosTrapX(Trap* Trap, int x) {
    assert(Trap != NULL);
    assert(x >= 0 && x < LINE);
    Trap->position_x = x;
}

extern void setPosTrapY(Trap* Trap, int y) {
    assert(Trap != NULL);
    assert(y >= 0 && y < COLUMN);
    Trap->position_y = y;
}
