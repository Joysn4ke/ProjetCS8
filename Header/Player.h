#ifndef PLAYER_H
#define PLAYER_H

typedef struct Player_s Player;

Player* newPlayer();
void playerInitialisation(Player* this, int localX, int localY);
void freePlayer(Player* this);

// Getter & Setter
int getPosPlayerX(Player* player);
int getPosPlayerY(Player* player);
void setPosPlayerX(Player* player, int x);
void setPosPlayerY(Player* player, int y);

#endif //PLAYER_H
