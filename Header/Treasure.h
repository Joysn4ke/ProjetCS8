#ifndef TREASURE_H
#define TREASURE_H

typedef struct Treasure_s Treasure;

extern Treasure* newTreasure();
extern void treasureInitialisation(Treasure* this, int localX, int localY);
extern void freeTreasure(Treasure* this);

// Getter & Setter
extern int getPosTreasureX(Treasure* Treasure);
extern int getPosTreasureY(Treasure* Treasure);
extern void setPosTreasureX(Treasure* Treasure, int x);
extern void setPosTreasureY(Treasure* Treasure, int y);

#endif //TREASURE_H
