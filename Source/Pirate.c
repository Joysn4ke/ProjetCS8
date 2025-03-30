#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "assert.h"

#include "Common.h"
#include "Pirate.h"

struct Pirate_s {
    int position_x;
    int position_y;
};

extern Pirate* newPirate() {
    Pirate* this = (Pirate*)calloc(1, sizeof(Pirate));
    assert(this != NULL);
    srand(time(NULL));
    return this;
}

extern void pirateInitialisation(Pirate* this, int localX, int localY) {
    assert(this != NULL);
    if (0 <= localX && localX < LINE && 0 <= localY && localY < COLUMN) {
        this->position_x = localX;
        this->position_y = localY;
    } else {
        this->position_x = rand() % LINE;
        this->position_y = rand() % COLUMN;
    }
}

extern void freePirate(Pirate* this) {
    if (this != NULL) {
        free(this);
    }
}

// Getters
extern int getPosPirateX(Pirate* this) {
    assert(this != NULL);
    return this->position_x;
}

extern int getPosPirateY(Pirate* this) {
    assert(this != NULL);
    return this->position_y;
}

// Setters
extern void setPosPirateX(Pirate* this, int x) {
    assert(this != NULL);
    assert(x >= 0 && x < LINE);
    this->position_x = x;
}

extern void setPosPirateY(Pirate* this, int y) {
    assert(this != NULL);
    assert(y >= 0 && y < COLUMN);
    this->position_y = y;
}

