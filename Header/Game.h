#ifndef GAME_H
#define GAME_H

#include "Map.h"
#include "Player.h"
#include "Treasure.h"
#include "Trap.h"

typedef struct Game_s Game;

extern Game* newGame();
extern void gameInitialisation(Game* this);
extern void freeGame(Game* this);

extern void gamePrint(Game* this);
extern int checkGameStatus(Game* this);

// Getter & Setter
extern Map* getMapGame(Game* game);
extern Player* getPlayerGame(Game* game);
extern Treasure* getTreasureGame(Game* game);
extern char** getGridGame(Game* game);
extern Trap** getTrapGame(Game* game);

typedef enum {
    INIT_A,
    ACQUISITION_CLAVIER,
    DEPLACEMENT_GAUCHE,
    DEPLACEMENT_DROITE,
    DEPLACEMENT_HAUT,
    DEPLACEMENT_BAS,
    VERIFICATION_VICTOIRE
} Etat;

typedef enum {
    E_CLAVIER,
    E_DEPLACER_GAUCHE,
    E_DEPLACER_DROITE,
    E_DEPLACER_HAUT,
    E_DEPLACER_BAS,
    E_VICTOIRE,
    E_PERDU,
    E_FIN
} Evenement;

typedef enum {
    A_NOP,
    A_DEPLACER,
    A_VERIFIER_VICTOIRE,
    A_TERMINE
} Action;

typedef struct {
    Etat etat_destination;
    Action action;
} Transition;

extern void run(Etat* etat, Evenement evenement, Game* game);

#endif //GAME_H
