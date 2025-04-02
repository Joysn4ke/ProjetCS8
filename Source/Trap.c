#include <stdlib.h>
#include <stdio.h>
#include "assert.h"

#include "Common.h"
#include "Trap.h"

/**
 * @brief Represents a trap
 * 
 * Contains position information for a trap that can damage the player.
 */
struct Trap_s{
    int position_x;
    int position_y;
};


/**
 * @brief Creates a new Trap object
 * 
 * Allocates memory for a new Trap.
 * 
 * @return Pointer to the newly created Trap
 */
extern Trap* newTrap() {
    Trap* this = (Trap*)calloc(1, sizeof(Trap));
    assert(this != NULL);  //Memory allocation's verification
    return this;
}



/**
 * @brief Initializes a Trap object
 * 
 * Sets the trap's position on the map.
 * 
 * @param this Pointer to the Trap to initialize
 * @param localX Initial X position
 * @param localY Initial Y position
 */
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


/**
 * @brief Frees memory used by a Trap object
 * 
 * @param this Pointer to the Trap to free
 */
extern void freeTrap(Trap* this) {
    if (this != NULL) {  //Check that the object is not NULL before freeing the memory
        free(this);
    }
}


// Getter & Setter
/**
 * @brief Gets the trap's X position
 * 
 * @param Trap Pointer to the Trap
 * @return X coordinate of the trap
 */
extern int getPosTrapX(Trap* Trap) {
    assert(Trap != NULL);
    return Trap->position_x;
}


/**
 * @brief Gets the trap's Y position
 * 
 * @param Trap Pointer to the Trap
 * @return Y coordinate of the trap
 */
extern int getPosTrapY(Trap* Trap) {
    assert(Trap != NULL);
    return Trap->position_y;
}


/**
 * @brief Sets the trap's X position
 * 
 * @param Trap Pointer to the Trap
 * @param x New X coordinate
 */
extern void setPosTrapX(Trap* Trap, int x) {
    assert(Trap != NULL);
    assert(x >= 0 && x < LINE);
    Trap->position_x = x;
}


/**
 * @brief Sets the trap's Y position
 * 
 * @param Trap Pointer to the Trap
 * @param y New Y coordinate
 */
extern void setPosTrapY(Trap* Trap, int y) {
    assert(Trap != NULL);
    assert(y >= 0 && y < COLUMN);
    Trap->position_y = y;
}



/**
 * @brief Sets the trap's X position to an invalid value (-1)
 * 
 * Used to mark a trap as triggered/disabled.
 * 
 * @param Trap Pointer to the Trap
 */
extern void setNullPosTrapX(Trap* Trap) {
    assert(Trap != NULL);
    Trap->position_x = -1;
}



/**
 * @brief Sets the trap's Y position to an invalid value (-1)
 * 
 * Used to mark a trap as triggered/disabled.
 * 
 * @param Trap Pointer to the Trap
 */
extern void setNullPosTrapY(Trap* Trap) {
    assert(Trap != NULL);
    Trap->position_y = -1;
}
