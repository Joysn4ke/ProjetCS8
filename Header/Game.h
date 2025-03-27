#ifndef GAME_H
#define GAME_H

#include "Map.h"
#include "Player.h"
#include "Treasure.h"

typedef struct Game_s Game;

Game* newGame();
void gameInitialisation(Game* this);
void freeGame(Game* this);

// Getter & Setter
Map* getMapGame(Game* game);
Player* getPlayerGame(Game* game);
Treasure* getTreasureGame(Game* game);
char** getGridGame(Game* game);


#endif //GAME_H
