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
    assert(NBTRAP < (LINE - 1) * (COLUMN - 1)); //Make sure that there is not too much trap

    srand(time(NULL));
    //rand() % (MAX - MIN + 1) + MIN;
    int playerX = rand() % (LINE);
    int playerY = rand() % (COLUMN);

    int treasureX = LINE - 1;
    int treasureY = COLUMN - 1;
    do {
        treasureX = rand() % (LINE);
        treasureY = rand() % (COLUMN);
    } while (treasureX == playerX || treasureY == playerY);

    // printf("playerX : %d\n", playerX);
    // printf("playerY : %d\n", playerY);
    // printf("treasureX : %d\n", treasureX);
    // printf("treasureY : %d\n", treasureY);

    mapInitialisation(this->map);
    playerInitialisation(this->player, playerX, playerY);
    treasureInitialisation(this->treasure, treasureX, treasureY);

    int X, Y;
    int usedX[NBTRAP + NBPLAYER + NBPIRATE];
    int usedY[NBTRAP + NBPLAYER + NBPIRATE];

    usedX[NBTRAP] = playerX;
    usedY[NBTRAP] = playerY;

    //Trap coordinates generation
    for (int i = 0; i < NBTRAP; i++) {
        //Initialize used arrays
        for (int j = 0; j < i; j++) {
            usedX[j] = getPosTrapX(this->trap[j]);
            usedY[j] = getPosTrapY(this->trap[j]);
        }

        // usedX[NBTRAP] = getPosPlayerX(this->player);
        // usedY[NBTRAP] = getPosPlayerY(this->player);
    
        generateUniqueCoordinates(&X, &Y, usedX, usedY, i);
        TrapInitialisation(this->trap[i], X, Y);        //Set trap coordinates correctly
        if (CHEAT) setGridCellMap(this->map, X, Y, 't');           //Set trap on the grid
    }

    if (CHEAT) setGridCellMap(this->map, treasureX, treasureY, 'T');    //Set treasure on the grid
    
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
    system("clear");
    setGridCellMap(this->map, getPosPlayerX(this->player), getPosPlayerY(this->player), 'j');
    //printf("\nIl te reste %d vies.\n", getHealthPlayer(this->player));
    grille_print(getGridMap(this->map), COLUMN, LINE);
    printf("\nIl te reste %d vies.\n", getHealthPlayer(this->player));
}


extern int checkGameStatus(Game* this) {
    //Verif if treasure found
    if (getPosPlayerX(getPlayerGame(this)) == getPosTreasureX(getTreasureGame(this)) &&
        getPosPlayerY(getPlayerGame(this)) == getPosTreasureY(getTreasureGame(this))) {
        return 1;
    }
    
    //Verif player on trap
    for (int i = 0; i < NBTRAP; i++) {
        if (getPosPlayerX(getPlayerGame(this)) == getPosTrapX(getTrapGame(this)[i]) && getPosPlayerY(getPlayerGame(this)) == getPosTrapY(getTrapGame(this)[i])) {
            
            printf("Tu es tombé sur un trap, tu perds une vie\n");
            setHealthPlayer(this->player, getHealthPlayer(this->player) - 1);

            setNullPosTrapX(getTrapGame(this)[i]);
            setNullPosTrapY(getTrapGame(this)[i]);
            
            if (getHealthPlayer(this->player) == 0) {
                printf("Tu n'as plus de vie\n");
                return 2; //Lose
            } else {
                return 0; //Game Continue
            }
            break;
        }
    }

    return 0;
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

extern Trap** getTrapGame(Game* game) {
    assert(game != NULL);
    return game->trap;
}

extern Treasure* getTreasureGame(Game* game) {
    assert(game != NULL);
    return game->treasure;
}

extern char** getGridGame(Game* game) {
    assert(game != NULL);
    return getGridMap(game->map);
}
