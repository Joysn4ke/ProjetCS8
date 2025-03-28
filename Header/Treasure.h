#ifndef TREASURE_H
#define TREASURE_H

typedef struct Treasure_s Treasure;

extern Treasure* newTreasure();
extern void treasureInitialisation(Treasure* this, int localX, int localY);
extern void freeTreasure(Treasure* this);

#endif //TREASURE_H
