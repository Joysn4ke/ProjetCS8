//
// Created by matthieu on 28/03/25.
//

#ifndef PIRATE_H
#define PIRATE_H

typedef struct Pirate_s Pirate;

extern Pirate* newPirate();
extern void pirateInitialisation(Pirate* this, int localX, int localY);
extern void freePirate(Pirate* this);

extern int getPosPirateX(Pirate* this);
extern int getPosPirateY(Pirate* this);

extern void setPosPirateX(Pirate* this, int x);
extern void setPosPirateY(Pirate* this, int y);


#endif
