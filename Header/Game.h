#ifndef GAME_H
#define GAME_H

//typedef struct Game_s Game;

typedef struct Game_s {
    Map *map;
    Player *player;
    Treasure *treasure;
}  Game;

Game* newGame();
void gameInitialisation(Game* this);
void freeGame(Game* this);

#endif //GAME_H
