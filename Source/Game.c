#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "assert.h"

#include "Common.h"
#include "Game.h"
#include "Grille.h"
#include "Map.h"
#include "Player.h"
#include "Trap.h"
#include "Treasure.h"


struct Game_s{
    Map *map;
    Player *player;
    Treasure *treasure;
    Trap *trap[NBTRAP];
};

extern Game* newGame() {
    Game* this = (Game*)calloc(1, sizeof(Game));
    assert(this != NULL);  //Memory allocation's verification

    this->map = newMap();
    this->player = newPlayer();
    this->treasure = newTreasure();
    for (int i = 0; i < NBTRAP ; i++) {
        this->trap[i] = newTrap();
    }

    return this;
}

extern void gameInitialisation(Game* this) {
    assert(this != NULL);  //Valid object's verification

    srand(time(NULL));
    //rand() % (MAX - MIN + 1) + MIN;
    int playerX = rand() % (LINE - 0 + 1) + 0;
    int playerY = rand() % (COLUMN - 0 + 1) + 0;

    int treasureX = LINE - 1;
    int treasureY = COLUMN - 1;

    do {
        treasureX = rand() % (LINE - 0 + 1) + 0;
        treasureY = rand() % (COLUMN - 0 + 1) + 0;
    } while (treasureX == playerX || treasureY == playerY);


    // printf("playerX : %d\n", playerX);
    // printf("playerY : %d\n", playerY);

    // printf("treasureX : %d\n", treasureX);
    // printf("treasureY : %d\n", treasureY);

    mapInitialisation(this->map);
    playerInitialisation(this->player, playerX, playerY);
    treasureInitialisation(this->treasure, treasureX, treasureY);

    for (int i = 0; i < NBTRAP; i++) {
        int X, Y;
        int usedX[NBTRAP];
        int usedY[NBTRAP];
    
        //Initialize used arrays
        for (int j = 0; j < i; j++) {
            usedX[j] = getPosTrapX(this->trap[j]);
            usedY[j] = getPosTrapY(this->trap[j]);
        }
    
        //Generate unique coordinates
        generateUniqueCoordinates(&X, &Y, 
            getPosPlayerX(this->player), 
            getPosPlayerY(this->player), 
            usedX, usedY, i, 
            LINE - 1, COLUMN - 1);
    
        //Set trap coordinates correctly
        //setPosTrapX(this->trap[i], X);
        //setPosTrapY(this->trap[i], Y);
        TrapInitialisation(this->trap[i], X, Y);
    
        //Set trap on the grid
        setGridCellMap(this->map, X, Y, 't');
    }

    
    setGridCellMap(getMapGame(this), 
               getPosPlayerX(this->player),
               getPosPlayerY(this->player),
               'j');
}

extern void freeGame(Game* this) {
    if (this != NULL) {  //Check that the object is not NULL before freeing the memory
        freeMap(this->map);
        freePlayer(this->player);
        freeTreasure(this->treasure);

        for (int i = 0; i < NBTRAP ; i++) {
            free(this->trap[i]);
        }

        free(this);
    }
}


extern void gamePrint(Game* this) {
    setGridCellMap(this->map, 
        getPosPlayerX(this->player),
        getPosPlayerY(this->player),
        'j');
    
    grille_print(getGridMap(this->map), COLUMN, LINE);
}


// Getter & Setter
extern Map* getMapGame(Game* game) {
    assert(game != NULL);
    return game->map;
}

extern Player* getPlayerGame(Game* game) {
    assert(game != NULL);
    return game->player;
}

extern Treasure* getTreasureGame(Game* game) {
    assert(game != NULL);
    return game->treasure;
}

extern char** getGridGame(Game* game) {
    assert(game != NULL);
    return getGridMap(game->map);
}
