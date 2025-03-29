#ifndef TRAP_H
#define TRAP_H

typedef struct Trap_s Trap;

extern Trap* newTrap();
extern void TrapInitialisation(Trap* this, int localX, int localY);
extern void freeTrap(Trap* this);

// Getter & Setter
extern int getPosTrapX(Trap* Trap);
extern int getPosTrapY(Trap* Trap);
extern void setPosTrapX(Trap* Trap, int x);
extern void setPosTrapY(Trap* Trap, int y);

extern void setNullPosTrapX(Trap* Trap);
extern void setNullPosTrapY(Trap* Trap);

#endif //TRAP_H
