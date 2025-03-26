#ifndef PLAYER_H
#define PLAYER_H

//typedef struct Player_s Player;

typedef struct Player_s {
    int position_x;
    int position_y;;
} Player;

Player* newPlayer();
void playerInitialisation(Player* this, int localX, int localY);
void freePlayer(Player* this);

#endif //PLAYER_H
