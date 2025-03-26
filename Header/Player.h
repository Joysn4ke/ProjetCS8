#ifndef PLAYER_H
#define PLAYER_H

typedef struct Player_s Player;

Player* newPlayer();
void playerInitialisation(Player* this);
void freePlayer(Player* this);

#endif //PLAYER_H
