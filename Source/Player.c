#include <stdlib.h>
#include <stdio.h>
#include "assert.h"

#include "Common.h"
#include "Player.h"


/**
 * @brief Represents the player character
 * 
 * Contains position and health information for the player.
 */
struct Player_s{
    int position_x;
    int position_y;
    int health;
};


/**
 * @brief Creates a new Player object
 * 
 * Allocates memory for a new Player.
 * 
 * @return Pointer to the newly created Player
 */
extern Player* newPlayer() {
    Player* this = (Player*)calloc(1, sizeof(Player));
    assert(this != NULL);  //Memory allocation's verification
    return this;
}


/**
 * @brief Initializes a Player object
 * 
 * Sets the player's initial position and health.
 * 
 * @param this Pointer to the Player to initialize
 * @param localX Initial X position
 * @param localY Initial Y position
 */
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



/**
 * @brief Frees memory used by a Player object
 * 
 * @param this Pointer to the Player to free
 */
extern void freePlayer(Player* this) {
    if (this != NULL) {  //Check that the object is not NULL before freeing the memory
        free(this);
    }
}


// Getter & Setter
/**
 * @brief Gets the player's X position
 * 
 * @param player Pointer to the Player
 * @return X coordinate of the player
 */
extern int getPosPlayerX(Player* player) {
    assert(player != NULL);
    return player->position_x;
}


/**
 * @brief Gets the player's Y position
 * 
 * @param player Pointer to the Player
 * @return Y coordinate of the player
 */
extern int getPosPlayerY(Player* player) {
    assert(player != NULL);
    return player->position_y;
}


/**
 * @brief Sets the player's X position
 * 
 * @param player Pointer to the Player
 * @param x New X coordinate
 */
extern void setPosPlayerX(Player* player, int x) {
    assert(player != NULL);
    assert(x >= 0 && x < LINE);
    player->position_x = x;
}


/**
 * @brief Sets the player's Y position
 * 
 * @param player Pointer to the Player
 * @param y New Y coordinate
 */
extern void setPosPlayerY(Player* player, int y) {
    assert(player != NULL);
    assert(y >= 0 && y < COLUMN);
    player->position_y = y;
}



/**
 * @brief Gets the player's health
 * 
 * @param player Pointer to the Player
 * @return Current health value
 */
extern int getHealthPlayer(Player* player) {
    assert(player != NULL);
    return player->health;
}


/**
 * @brief Sets the player's health
 * 
 * @param player Pointer to the Player
 * @param localHealth New health value
 */
extern void setHealthPlayer(Player* player, int localHealth) {
    assert(player != NULL);
    assert(localHealth >= 0 && localHealth < HEALTHPLAYER);
    player->health = localHealth;
}
