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
#include "Pirate.h"

struct TransitionAction_s {
    GameAction action;
    GameState destinationState;
};

struct Game_s {
    Map *map;
    Player *player;
    Treasure *treasure;
    Pirate *pirate;
    Trap *trap[NBTRAP];

    //State machine elements
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
    this->pirate = newPirate();
    for (int i = 0; i < NBTRAP ; i++) {
        this->trap[i] = newTrap();
    }

    return this;
}


extern void gameInitialisation(Game* this) {
    assert(this != NULL);  //Valid object's verification
    assert(HEALTHPLAYER > 0);  //Verif health's player
    assert(NBPLAYER > 0);  //Verif nb player
    assert(LINE > 3 && COLUMN > 3);  //Verif grid size
    assert(NBTRAP < (LINE - 1) * (COLUMN - 1)); //Make sure that there is not too much trap

    //Initialize state machine related fields
    gameInitStateMachine(this);

    //Initialize new seed
    srand(time(NULL));

    //Arrays to track used coordinates
    int usedX[TOTAL_ENTITY + 1];
    int usedY[TOTAL_ENTITY + 1];
    int usedCount = 0;
    
    //Initialize player coordinates
    int playerX, playerY;
    generateUniqueCoordinates(&playerX, &playerY, usedX, usedY, usedCount++);
    
    //Initialize treasure coordinates
    int treasureX, treasureY;
    generateUniqueCoordinates(&treasureX, &treasureY, usedX, usedY, usedCount++);
    
    //Initialize pirate coordinates
    int pirateX, pirateY;
    generateUniqueCoordinates(&pirateX, &pirateY, usedX, usedY, usedCount++);
    
    // printf("playerX : %d\n", playerX);
    // printf("playerY : %d\n", playerY);
    // printf("treasureX : %d\n", treasureX);
    // printf("treasureY : %d\n", treasureY);
    // printf("pirateX : %d\n", pirateX);
    // printf("pirateY : %d\n", pirateY);

    mapInitialisation(this->map);
    playerInitialisation(this->player, playerX, playerY);
    treasureInitialisation(this->treasure, treasureX, treasureY);
    pirateInitialisation(this->pirate, pirateX, pirateY);

    if (CHEAT) setGridCellMap(this->map, treasureX, treasureY, 'T');    //Set treasure on the grid
    setGridCellMap(this->map, pirateX, pirateY, 'P');    //Set pirate on the grid
    setGridCellMap(this->map, playerX, playerY, 'j');    //Set pirate on the grid

    //Trap coordinates generation
    int X, Y;
    for (int i = 0; i < NBTRAP; i++) {
        generateUniqueCoordinates(&X, &Y, usedX, usedY, usedCount++);
        TrapInitialisation(this->trap[i], X, Y);            //Set trap coordinates correctly
        if (CHEAT) setGridCellMap(this->map, X, Y, 't');    //Set trap on the grid
    }
    
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
        freePirate(this->pirate);

        for (int i = 0; i < NBTRAP ; i++) {
            free(this->trap[i]);
        }

        free(this);
    }
}


extern void gamePrint(Game* this) {
    system("clear");

    if (CHEAT) {
        setGridCellMap(this->map, getPosTreasureX(this->treasure), getPosTreasureY(this->treasure), 'T');
        for (int i = 0; i < NBTRAP; i++) {
            if (getPosTrapX(this->trap[i]) != -1 && getPosTrapY(this->trap[i]) != -1) {
                setGridCellMap(this->map, getPosTrapX(this->trap[i]), getPosTrapY(this->trap[i]), 't');    //Set trap on the grid
            }
        }
    }

    setGridCellMap(this->map, getPosPlayerX(this->player), getPosPlayerY(this->player), 'j');
    setGridCellMap(this->map, getPosPirateX(this->pirate), getPosPirateY(this->pirate), 'P');

    grille_print(getGridMap(this->map), COLUMN, LINE);
    printf("\nIl te reste %d vies.\n", getHealthPlayer(this->player));

    // printf("playerX : %d\n", getPosPlayerX(this->player));
    // printf("playerY : %d\n", getPosPlayerY(this->player));
    // printf("treasureX : %d\n", getPosTreasureX(this->treasure));
    // printf("treasureY : %d\n", getPosTreasureY(this->treasure));
    // printf("pirateX : %d\n", getPosPirateX(this->pirate));
    // printf("pirateY : %d\n", getPosPirateY(this->pirate));
}


extern int checkGameStatus(Game* this) {
    //Verif if treasure found
    if (getPosPlayerX(getPlayerGame(this)) == getPosTreasureX(getTreasureGame(this)) &&
        getPosPlayerY(getPlayerGame(this)) == getPosTreasureY(getTreasureGame(this))) {
        return 1; //Win
    }

    if (getPosPlayerX(getPlayerGame(this)) == getPosPirateX(getPirateGame(this)) &&
        getPosPlayerY(getPlayerGame(this)) == getPosPirateY(getPirateGame(this))) {
        printf("Le pirate t'as rattrapé\n");
        return 2; //Lose
    }
    
    //Verif player on trap
    for (int i = 0; i < NBTRAP; i++) {
        if (getPosPlayerX(this->player) == getPosTrapX(getTrapGame(this)[i]) && getPosPlayerY(getPlayerGame(this)) == getPosTrapY(getTrapGame(this)[i])) {
            
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



extern void movePirate(Game* this) {
    assert(this != NULL);
    
    //Get current positions
    int pirateX = getPosPirateX(this->pirate);
    int pirateY = getPosPirateY(this->pirate);
    int playerX = getPosPlayerX(this->player);
    int playerY = getPosPlayerY(this->player);
    
    setGridCellMap(this->map, pirateX, pirateY, ' ');  //Clear pirate's current position on map
    
    int newPirateX = pirateX;
    int newPirateY = pirateY;
    
    if (pirateX == playerX) { //Case 1: Pirate on same row as player
        //Move toward player vertically
        int moveY = (playerY > pirateY) ? 1 : -1;
        newPirateY = pirateY + moveY;
    } else if (pirateY == playerY) { //Case 2: Pirate on same column as player
        //Move toward player horizontally
        int moveX = (playerX > pirateX) ? 1 : -1;
        newPirateX = pirateX + moveX;
    } else { //Case 3: Random movement
        //Possible directions: {x, y}
        int possibleMoves[4][2] = {
            {1, 0},   // Right
            {-1, 0},  // Left
            {0, 1},   // Down
            {0, -1}   // Up
        };
        
        //Track valid moves
        int validMoves[4] = {0};
        int validMoveCount = 0;
        
        //Check each direction
        for (int i = 0; i < 4; i++) {
            int newX = pirateX + possibleMoves[i][0];
            int newY = pirateY + possibleMoves[i][1];
            
            //Check if within bounds
            if (newX >= 0 && newX < LINE && newY >= 0 && newY < COLUMN) {
                validMoves[i] = 1;
                validMoveCount++;
            }
        }
        
        //No valid moves available
        if (validMoveCount == 0) {
            return;
        }
        
        //Choose random valid move
        int moveIndex;
        do {
            moveIndex = rand() % 4;
        } while (validMoves[moveIndex] == 0);
        
        //Apply chosen move
        newPirateX = pirateX + possibleMoves[moveIndex][0];
        newPirateY = pirateY + possibleMoves[moveIndex][1];
    }
    
    //Final boundary check before applying movement
    if (newPirateX >= 0 && newPirateX < LINE && newPirateY >= 0 && newPirateY < COLUMN) {
        setPosPirateX(this->pirate, newPirateX);
        setPosPirateY(this->pirate, newPirateY);
    }
    
    setGridCellMap(this->map, getPosPirateX(this->pirate), getPosPirateY(this->pirate), ' ');
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
    if (getPosPlayerX(this->player) > 0) {
        setGridCellMap(this->map, getPosPlayerX(this->player), getPosPlayerY(this->player), ' ');
        setPosPlayerX(this->player, getPosPlayerX(this->player) - 1);
    }
    if (!(getPosPlayerX(this->player) == getPosPirateX(this->pirate) && getPosPlayerY(this->player) == getPosPirateY(this->pirate))) {
        movePirate(this);
    }
}

static void actionMoveDown(Game* this) {
    if (getPosPlayerX(this->player) < LINE - 1) {
        setGridCellMap(this->map, getPosPlayerX(this->player), getPosPlayerY(this->player), ' ');
        setPosPlayerX(this->player, getPosPlayerX(this->player) + 1);
    }
    if (!(getPosPlayerX(this->player) == getPosPirateX(this->pirate) && getPosPlayerY(this->player) == getPosPirateY(this->pirate))) {
        movePirate(this);
    }
}

static void actionMoveLeft(Game* this) {
    if (getPosPlayerY(this->player) > 0) {
        setGridCellMap(this->map, getPosPlayerX(this->player), getPosPlayerY(this->player), ' ');
        setPosPlayerY(this->player, getPosPlayerY(this->player) - 1);
    }
    if (!(getPosPlayerX(this->player) == getPosPirateX(this->pirate) && getPosPlayerY(this->player) == getPosPirateY(this->pirate))) {
        movePirate(this);
    }
}

static void actionMoveRight(Game* this) {
    if (getPosPlayerY(this->player) < COLUMN - 1) {
        setGridCellMap(this->map, getPosPlayerX(this->player), getPosPlayerY(this->player), ' ');
        setPosPlayerY(this->player, getPosPlayerY(this->player) + 1);
    }
    if (!(getPosPlayerX(this->player) == getPosPirateX(this->pirate) && getPosPlayerY(this->player) == getPosPirateY(this->pirate))) {
        movePirate(this);
    }
}

static void actionPrintGame(Game* this) {
    gamePrint(this);
}

static void actionCheckStatus(Game* this) {
    assert(this != NULL);
    //This action is used in combination with the code in main.c to check the game status
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

extern Pirate* getPirateGame(Game* game) {
    assert(game != NULL);
    return game->pirate;
}

extern char** getGridGame(Game* game) {
    assert(game != NULL);
    return getGridMap(game->map);
}

