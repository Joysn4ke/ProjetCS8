#include <stdlib.h>
#include <stdio.h>
#include "assert.h"

#include "Common.h"
#include "Treasure.h"


/**
 * @brief Represents the treasure
 * 
 * Contains position information for the treasure the player must find.
 */
struct Treasure_s{
    int position_x;
    int position_y;
};


/**
 * @brief Creates a new Treasure object
 * 
 * Allocates memory for a new Treasure.
 * 
 * @return Pointer to the newly created Treasure
 */
extern Treasure* newTreasure() {
    Treasure* this = (Treasure*)calloc(1, sizeof(Treasure));
    assert(this != NULL);  //Memory allocation's verification
    return this;
}


/**
 * @brief Initializes a Treasure object
 * 
 * Sets the treasure's position on the map.
 * 
 * @param this Pointer to the Treasure to initialize
 * @param localX Initial X position
 * @param localY Initial Y position
 */
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


/**
 * @brief Frees memory used by a Treasure object
 * 
 * @param this Pointer to the Treasure to free
 */	
extern void freeTreasure(Treasure* this) {
    if (this != NULL) {  //Check that the object is not NULL before freeing the memory
        free(this);
    }
}

// Getter & Setter

/**
 * @brief Gets the treasure's X position
 * 
 * @param Treasure Pointer to the Treasure
 * @return X coordinate of the treasure
 */
extern int getPosTreasureX(Treasure* Treasure) {
    assert(Treasure != NULL);
    return Treasure->position_x;
}


/**
 * @brief Gets the treasure's Y position
 * 
 * @param Treasure Pointer to the Treasure
 * @return Y coordinate of the treasure
 */
extern int getPosTreasureY(Treasure* Treasure) {
    assert(Treasure != NULL);
    return Treasure->position_y;
}


/**
 * @brief Sets the treasure's X position
 * 
 * @param Treasure Pointer to the Treasure
 * @param x New X coordinate
 */
extern void setPosTreasureX(Treasure* Treasure, int x) {
    assert(Treasure != NULL);
    assert(x >= 0 && x < LINE);
    Treasure->position_x = x;
}


/**
 * @brief Sets the treasure's Y position
 * 
 * @param Treasure Pointer to the Treasure
 * @param y New Y coordinate
 */
extern void setPosTreasureY(Treasure* Treasure, int y) {
    assert(Treasure != NULL);
    assert(y >= 0 && y < COLUMN);
    Treasure->position_y = y;
}
