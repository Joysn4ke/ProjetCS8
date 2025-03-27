#ifndef PLAYER_H
#define PLAYER_H

typedef struct Player_s Player;

// typedef struct Player_s {
//     int position_x;
//     int position_y;;
// } Player;

Player* newPlayer();
void playerInitialisation(Player* this, int localX, int localY);
void freePlayer(Player* this);

// Getter & Setter
int getPlayerX(Player* player);
int getPlayerY(Player* player);
void setPlayerX(Player* player, int x);
void setPlayerY(Player* player, int y);

#endif //PLAYER_H
