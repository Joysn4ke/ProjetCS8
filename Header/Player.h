#ifndef PLAYER_H
#define PLAYER_H

typedef struct Player_s Player;

extern Player* newPlayer();
extern void playerInitialisation(Player* this, int localX, int localY);
extern void freePlayer(Player* this);

// Getter & Setter
extern int getPosPlayerX(Player* player);
extern int getPosPlayerY(Player* player);

extern void setPosPlayerX(Player* player, int x);
extern void setPosPlayerY(Player* player, int y);


extern int getHealthPlayer(Player* player);
extern void setHealthPlayer(Player* player, int localHealth);

#endif //PLAYER_H
