#ifndef GAME_H
#define GAME_H

typedef struct Game_s Game;

Game* newGame();
void gameInitialisation(Game* this);
void gameFree(Game* this);

#endif //GAME_H
