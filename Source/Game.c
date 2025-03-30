#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "assert.h"

#include "Common.h"
#include "Game.h"
#include "Map.h"
#include "Player.h"
#include "Trap.h"
#include "Treasure.h"

struct TransitionAction_s {
    GameAction action;
    GameState destinationState;
};

struct Game_s {
    Map *map;
    Player *player;
    Treasure *treasure;
    Trap *trap[NBTRAP];

    // State machine elements
    GameState currentState;
    int gameFinished;
    TransitionAction transitionMatrix[STATE_NB][EVENT_NB];
};


//Action function declarations
static void actionNop(Game* this);
static void actionInitGame(Game* this);
static void actionMoveUp(Game* this);
static void actionMoveDown(Game* this);
static void actionMoveLeft(Game* this);
static void actionMoveRight(Game* this);
static void actionPrintGame(Game* this);
static void actionCheckStatus(Game* this);
static void actionPrintVictory(Game* this);
static void actionPrintDefeat(Game* this);
static void actionFreeGame(Game* this);

//Function pointer typedef for actions
typedef void (*ActionPtr)(Game*);

//Array of action functions
static const ActionPtr actionsTab[ACTION_NB] = {
    &actionNop,
    &actionInitGame,
    &actionMoveUp,
    &actionMoveDown,
    &actionMoveLeft,
    &actionMoveRight,
    &actionPrintGame,
    &actionCheckStatus,
    &actionPrintVictory,
    &actionPrintDefeat,
    &actionFreeGame
};


const TransitionAction transitionMatrixConst[STATE_NB][EVENT_NB] = {
    //S_INIT
    [S_INIT][E_START] = {A_INIT_GAME, S_ACQUISITION_CLAVIER},

    //S_ACQUISITION_CLAVIER
    [S_ACQUISITION_CLAVIER][E_KEY_UP] = {A_MOVE_UP, S_DEPLACEMENT},
    [S_ACQUISITION_CLAVIER][E_KEY_DOWN] = {A_MOVE_DOWN, S_DEPLACEMENT},
    [S_ACQUISITION_CLAVIER][E_KEY_LEFT] = {A_MOVE_LEFT, S_DEPLACEMENT},
    [S_ACQUISITION_CLAVIER][E_KEY_RIGHT] = {A_MOVE_RIGHT, S_DEPLACEMENT},
    [S_ACQUISITION_CLAVIER][E_KEY_QUIT] = {A_FREE_GAME, S_GAME_OVER},
    [S_ACQUISITION_CLAVIER][E_OTHER_KEY] = {A_NOP, S_ACQUISITION_CLAVIER},

    //S_DEPLACEMENT
    [S_DEPLACEMENT][E_MOVE_DONE] = {A_PRINT_GAME, S_VERIFICATION_VICTOIRE},

    //S_VERIFICATION_VICTOIRE
    [S_VERIFICATION_VICTOIRE][E_VICTORY] = {A_PRINT_VICTORY, S_GAME_OVER},
    [S_VERIFICATION_VICTOIRE][E_DEFEAT] = {A_PRINT_DEFEAT, S_GAME_OVER},
    [S_VERIFICATION_VICTOIRE][E_CONTINUE] = {A_NOP, S_ACQUISITION_CLAVIER},

    //S_GAME_OVER (toutes les transitions mènent à S_FORGET ou sont NOP par défaut)
};

TransitionAction getTransition(GameState state, GameEvent event) {
    if (state >= STATE_NB || event >= EVENT_NB) {
        return (TransitionAction){A_NOP, S_FORGET}; //Valeur par défaut pour toute transition invalide
    }
    return transitionMatrixConst[state][event];
}


extern Game* newGame() {
    Game* this = (Game*)calloc(1, sizeof(Game));
    assert(this != NULL);  //Memory allocation's verification

    this->map = newMap();
    this->player = newPlayer();
    this->treasure = newTreasure();
    for (int i = 0; i < NBTRAP ; i++) {
        this->trap[i] = newTrap();
    }

    return this;
}

extern void gameInitialisation(Game* this) {
    assert(this != NULL);  //Valid object's verification
    assert(NBTRAP < (LINE - 1) * (COLUMN - 1)); //Make sure that there is not too much trap

    //Initialize state machine related fields
    gameInitStateMachine(this);

    //Init of random coordinates
    srand(time(NULL));
    //rand() % (MAX - MIN + 1) + MIN;
    int playerX = rand() % (LINE);
    int playerY = rand() % (COLUMN);

    int treasureX = LINE - 1;
    int treasureY = COLUMN - 1;
    do {
        treasureX = rand() % (LINE);
        treasureY = rand() % (COLUMN);
    } while (treasureX == playerX || treasureY == playerY);

    // printf("playerX : %d\n", playerX);
    // printf("playerY : %d\n", playerY);
    // printf("treasureX : %d\n", treasureX);
    // printf("treasureY : %d\n", treasureY);

    mapInitialisation(this->map);
    playerInitialisation(this->player, playerX, playerY);
    treasureInitialisation(this->treasure, treasureX, treasureY);

    int X, Y;
    int usedX[NBTRAP + NBPLAYER + NBPIRATE];
    int usedY[NBTRAP + NBPLAYER + NBPIRATE];

    usedX[NBTRAP] = playerX;
    usedY[NBTRAP] = playerY;

    //Trap coordinates generation
    for (int i = 0; i < NBTRAP; i++) {
        //Initialize used arrays
        for (int j = 0; j < i; j++) {
            usedX[j] = getPosTrapX(this->trap[j]);
            usedY[j] = getPosTrapY(this->trap[j]);
        }
    
        generateUniqueCoordinates(&X, &Y, usedX, usedY, i);
        TrapInitialisation(this->trap[i], X, Y);            //Set trap coordinates correctly
        if (CHEAT) setGridCellMap(this->map, X, Y, 't');           //Set trap on the grid
    }

    if (CHEAT) setGridCellMap(this->map, treasureX, treasureY, 'T');    //Set treasure on the grid
    
    setGridCellMap(getMapGame(this), 
               getPosPlayerX(this->player),
               getPosPlayerY(this->player),
               'j');
}

extern void freeGame(Game* this) {
    if (this != NULL) {  //Check that the object is not NULL before freeing the memory
        freeMap(this->map);
        freePlayer(this->player);
        freeTreasure(this->treasure);

        for (int i = 0; i < NBTRAP ; i++) {
            free(this->trap[i]);
        }

        free(this);
    }
}


extern void gamePrint(Game* this) {
    system("clear");
    setGridCellMap(this->map, getPosPlayerX(this->player), getPosPlayerY(this->player), 'j');
    grille_print(getGridMap(this->map), COLUMN, LINE);
    printf("\nIl te reste %d vies.\n", getHealthPlayer(this->player));
}


extern int checkGameStatus(Game* this) {
    //Verif if treasure found
    if (getPosPlayerX(getPlayerGame(this)) == getPosTreasureX(getTreasureGame(this)) &&
        getPosPlayerY(getPlayerGame(this)) == getPosTreasureY(getTreasureGame(this))) {
        return 1;
    }
    
    //Verif player on trap
    for (int i = 0; i < NBTRAP; i++) {
        if (getPosPlayerX(getPlayerGame(this)) == getPosTrapX(getTrapGame(this)[i]) && getPosPlayerY(getPlayerGame(this)) == getPosTrapY(getTrapGame(this)[i])) {
            
            printf("Tu es tombé sur un trap, tu perds une vie\n");
            setHealthPlayer(this->player, getHealthPlayer(this->player) - 1);

            setNullPosTrapX(getTrapGame(this)[i]);
            setNullPosTrapY(getTrapGame(this)[i]);
            
            if (getHealthPlayer(this->player) == 0) {
                printf("Tu n'as plus de vie\n");
                return 2; //Lose
            } else {
                return 0; //Game Continue
            }
            break;
        }
    }

    return 0;
}


//Implementation of action functions
static void actionNop(Game* this) {
    assert(this != NULL);
    //Does nothing
}

static void actionInitGame(Game* this) {
    gameInitialisation(this);
    gamePrint(this);
}

static void actionMoveUp(Game* this) {
    setGridCellMap(this->map, getPosPlayerX(this->player), getPosPlayerY(this->player), ' ');
    if (getPosPlayerX(this->player) > 0) {
        setPosPlayerX(this->player, getPosPlayerX(this->player) - 1);
    }
}

static void actionMoveDown(Game* this) {
    setGridCellMap(this->map, getPosPlayerX(this->player), getPosPlayerY(this->player), ' ');
    if (getPosPlayerX(this->player) < LINE - 1) {
        setPosPlayerX(this->player, getPosPlayerX(this->player) + 1);
    }
}

static void actionMoveLeft(Game* this) {
    setGridCellMap(this->map, getPosPlayerX(this->player), getPosPlayerY(this->player), ' ');
    if (getPosPlayerY(this->player) > 0) {
        setPosPlayerY(this->player, getPosPlayerY(this->player) - 1);
    }
}

static void actionMoveRight(Game* this) {
    setGridCellMap(this->map, getPosPlayerX(this->player), getPosPlayerY(this->player), ' ');
    if (getPosPlayerY(this->player) < COLUMN - 1) {
        setPosPlayerY(this->player, getPosPlayerY(this->player) + 1);
    }
}

static void actionPrintGame(Game* this) {
    gamePrint(this);
}

static void actionCheckStatus(Game* this) {
    assert(this != NULL);
    //This action is used in combination with the code in main.c
    //to check the game status
}

static void actionPrintVictory(Game* this) {
    printf("Tu as gagné, wp tu es tombé sur le trésor \n");
    this->gameFinished = 1;
}

static void actionPrintDefeat(Game* this) {
    printf("Tu as perdu\n");
    this->gameFinished = 1;
}

static void actionFreeGame(Game* this) {
    this->gameFinished = 1;
}


// State Machine Functions (Incorporated into Game)
extern void gameInitStateMachine(Game* this) {
    assert(this != NULL);
    this->currentState = S_INIT;
    this->gameFinished = 0;
    
    //Copy the transition matrix
    for (int i = 0; i < STATE_NB; i++) {
        for (int j = 0; j < EVENT_NB; j++) {
            this->transitionMatrix[i][j] = transitionMatrixConst[i][j];
        }
    }
}

extern void gameHandleEvent(Game* this, GameEvent event) {
    assert(this != NULL);
    TransitionAction transition;
    GameState newState;
    
    assert(this->currentState != S_DEATH);
    
    transition  = getTransition(this->currentState, event);
    newState = transition.destinationState;
    
    if (newState != S_FORGET) {
        actionsTab[transition.action](this); //Execute the action
        this->currentState = newState;
    }
}

extern GameEvent gameGetEventFromKey(char key) {
    switch(key) {
        case 'l':
            return E_KEY_QUIT;
        case 65: 
        case 'z':
            return E_KEY_UP;
        case 66: 
        case 's':
            return E_KEY_DOWN;
        case 67: 
        case 'd':
            return E_KEY_RIGHT;
        case 68: 
        case 'q':
            return E_KEY_LEFT;
        default:
            return E_OTHER_KEY;
    }
}

extern int gameIsFinished(Game* this) {
    assert(this != NULL);
    return this->gameFinished;
}

extern GameState gameGetCurrentState(Game* this) {
    assert(this != NULL);
    return this->currentState;
}


// Getter & Setter
extern Map* getMapGame(Game* game) {
    assert(game != NULL);
    return game->map;
}

extern Player* getPlayerGame(Game* game) {
    assert(game != NULL);
    return game->player;
}

extern Trap** getTrapGame(Game* game) {
    assert(game != NULL);
    return game->trap;
}

extern Treasure* getTreasureGame(Game* game) {
    assert(game != NULL);
    return game->treasure;
}

extern char** getGridGame(Game* game) {
    assert(game != NULL);
    return getGridMap(game->map);
}


