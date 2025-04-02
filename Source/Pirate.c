#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "assert.h"

#include "Common.h"
#include "Pirate.h"


/**
 * @brief Represents the pirate enemy
 * 
 * Contains position information for the pirate that chases the player.
 */
struct Pirate_s {
    int position_x;
    int position_y;
};


/**
 * @brief Creates a new Pirate object
 * 
 * Allocates memory for a new Pirate.
 * 
 * @return Pointer to the newly created Pirate
 */
extern Pirate* newPirate() {
    Pirate* this = (Pirate*)calloc(1, sizeof(Pirate));
    assert(this != NULL);
    srand(time(NULL));
    return this;
}


/**
 * @brief Initializes a Pirate object
 * 
 * Sets the pirate's initial position on the map.
 * 
 * @param this Pointer to the Pirate to initialize
 * @param localX Initial X position
 * @param localY Initial Y position
 */
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


/**
 * @brief Frees memory used by a Pirate object
 * 
 * @param this Pointer to the Pirate to free
 */
extern void freePirate(Pirate* this) {
    if (this != NULL) {
        free(this);
    }
}

// Getters
/**
 * @brief Gets the pirate's X position
 * 
 * @param this Pointer to the Pirate
 * @return X coordinate of the pirate
 */
extern int getPosPirateX(Pirate* this) {
    assert(this != NULL);
    return this->position_x;
}

/**
 * @brief Gets the pirate's Y position
 * 
 * @param this Pointer to the Pirate
 * @return Y coordinate of the pirate
 */
extern int getPosPirateY(Pirate* this) {
    assert(this != NULL);
    return this->position_y;
}

// Setters

/**
 * @brief Sets the pirate's X position
 * 
 * @param this Pointer to the Pirate
 * @param x New X coordinate
 */
extern void setPosPirateX(Pirate* this, int x) {
    assert(this != NULL);
    assert(x >= 0 && x < LINE);
    this->position_x = x;
}

/**
 * @brief Sets the pirate's Y position
 * 
 * @param this Pointer to the Pirate
 * @param y New Y coordinate
 */
extern void setPosPirateY(Pirate* this, int y) {
    assert(this != NULL);
    assert(y >= 0 && y < COLUMN);
    this->position_y = y;
}

