#ifndef TREASURE_H
#define TREASURE_H

typedef struct Treasure_s Treasure;

// typedef struct Treasure_s{
//     int position_x;
//     int position_y;;
// } Treasure;

Treasure* newTreasure();
void treasureInitialisation(Treasure* this, int localX, int localY);
void freeTreasure(Treasure* this);

#endif //TREASURE_H
