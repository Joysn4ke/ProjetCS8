#ifndef GAME_H
#define GAME_H

#include "Map.h"
#include "Player.h"
#include "Treasure.h"
#include "Trap.h"

typedef struct Game_s Game;

extern Game* newGame();
extern void gameInitialisation(Game* this);
extern void freeGame(Game* this);

extern void gamePrint(Game* this);
extern int checkGameStatus(Game* this);

// Getter & Setter
extern Map* getMapGame(Game* game);
extern Player* getPlayerGame(Game* game);
extern Treasure* getTreasureGame(Game* game);
extern char** getGridGame(Game* game);
extern Trap** getTrapGame(Game* game);

#endif //GAME_H
