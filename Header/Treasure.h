#ifndef TREASURE_H
#define TREASURE_H

typedef struct Treasure_s Treasure;

extern Treasure* newTreasure();
extern void treasureInitialisation(Treasure* this, int localX, int localY);
extern void freeTreasure(Treasure* this);
<<<<<<< HEAD

=======
>>>>>>> 0798d272cb99d5ae78723bf723c4f33d3f278bbe
// Getter & Setter
extern int getPosTreasureX(Treasure* Treasure);
extern int getPosTreasureY(Treasure* Treasure);
extern void setPosTreasureX(Treasure* Treasure, int x);
extern void setPosTreasureY(Treasure* Treasure, int y);
<<<<<<< HEAD

=======
>>>>>>> 0798d272cb99d5ae78723bf723c4f33d3f278bbe
#endif //TREASURE_H
