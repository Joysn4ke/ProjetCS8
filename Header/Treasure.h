#ifndef TREASURE_H
#define TREASURE_H

typedef struct Treasure_s Treasure;

Treasure* newTreasure();
void treasureInitialisation(Treasure* this);
void freeTreasure(Treasure* this);

#endif //TREASURE_H
