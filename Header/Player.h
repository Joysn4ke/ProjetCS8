#ifndef PLAYER_H
#define PLAYER_H

typedef struct Player_s Player;

Player* newPlayer();
void playerInitialisation(Player* this, int localX, int localY);
void freePlayer(Player* this);

// Getter & Setter
int getPlayerX(Player* player);
int getPlayerY(Player* player);
void setPlayerX(Player* player, int x);
void setPlayerY(Player* player, int y);

#endif //PLAYER_H
