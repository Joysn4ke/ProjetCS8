#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "assert.h"

#include "Common.h"
#include "Game.h"
#include "Grille.h"
#include "Map.h"
#include "Player.h"
#include "Trap.h"
#include "Treasure.h"

typedef struct {
    GameAction action;
    GameState destinationState;
} TransitionAction;


struct Game_s{
    Map *map;
    Player *player;
    Treasure *treasure;
    Trap *trap[NBTRAP];

    // State machine elements
    GameState currentState;
    int gameFinished;
    TransitionAction transitionMatrix[STATE_NB][EVENT_NB];
};


// Action function declarations
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

// Function pointer typedef for actions
typedef void (*ActionPtr)(Game*);

// Array of action functions
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


// Initialize the transition matrix for the game
static void initTransitionMatrix(Game* this) {
    // Default initialization
    for (int i = 0; i < STATE_NB; i++) {
        for (int j = 0; j < EVENT_NB; j++) {
            this->transitionMatrix[i][j].action = A_NOP;
            this->transitionMatrix[i][j].destinationState = S_FORGET;
        }
    }
    
    // Define specific transitions
    
    // From S_INIT
    this->transitionMatrix[S_INIT][E_START].action = A_INIT_GAME;
    this->transitionMatrix[S_INIT][E_START].destinationState = S_ACQUISITION_CLAVIER;
    
    // From S_ACQUISITION_CLAVIER
    this->transitionMatrix[S_ACQUISITION_CLAVIER][E_KEY_UP].action = A_MOVE_UP;
    this->transitionMatrix[S_ACQUISITION_CLAVIER][E_KEY_UP].destinationState = S_DEPLACEMENT;
    
    this->transitionMatrix[S_ACQUISITION_CLAVIER][E_KEY_DOWN].action = A_MOVE_DOWN;
    this->transitionMatrix[S_ACQUISITION_CLAVIER][E_KEY_DOWN].destinationState = S_DEPLACEMENT;
    
    this->transitionMatrix[S_ACQUISITION_CLAVIER][E_KEY_LEFT].action = A_MOVE_LEFT;
    this->transitionMatrix[S_ACQUISITION_CLAVIER][E_KEY_LEFT].destinationState = S_DEPLACEMENT;
    
    this->transitionMatrix[S_ACQUISITION_CLAVIER][E_KEY_RIGHT].action = A_MOVE_RIGHT;
    this->transitionMatrix[S_ACQUISITION_CLAVIER][E_KEY_RIGHT].destinationState = S_DEPLACEMENT;
    
    this->transitionMatrix[S_ACQUISITION_CLAVIER][E_KEY_QUIT].action = A_FREE_GAME;
    this->transitionMatrix[S_ACQUISITION_CLAVIER][E_KEY_QUIT].destinationState = S_GAME_OVER;
    
    this->transitionMatrix[S_ACQUISITION_CLAVIER][E_OTHER_KEY].action = A_NOP;
    this->transitionMatrix[S_ACQUISITION_CLAVIER][E_OTHER_KEY].destinationState = S_ACQUISITION_CLAVIER;
    
    // From S_DEPLACEMENT
    this->transitionMatrix[S_DEPLACEMENT][E_MOVE_DONE].action = A_PRINT_GAME;
    this->transitionMatrix[S_DEPLACEMENT][E_MOVE_DONE].destinationState = S_VERIFICATION_VICTOIRE;
    
    // From S_VERIFICATION_VICTOIRE
    this->transitionMatrix[S_VERIFICATION_VICTOIRE][E_VICTORY].action = A_PRINT_VICTORY;
    this->transitionMatrix[S_VERIFICATION_VICTOIRE][E_VICTORY].destinationState = S_GAME_OVER;
    
    this->transitionMatrix[S_VERIFICATION_VICTOIRE][E_DEFEAT].action = A_PRINT_DEFEAT;
    this->transitionMatrix[S_VERIFICATION_VICTOIRE][E_DEFEAT].destinationState = S_GAME_OVER;
    
    this->transitionMatrix[S_VERIFICATION_VICTOIRE][E_CONTINUE].action = A_NOP;
    this->transitionMatrix[S_VERIFICATION_VICTOIRE][E_CONTINUE].destinationState = S_ACQUISITION_CLAVIER;
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

    // Initialize state machine related fields
    this->currentState = S_INIT;
    this->gameFinished = 0;
    initTransitionMatrix(this);

    return this;
}

extern void gameInitialisation(Game* this) {
    assert(this != NULL);  //Valid object's verification
    assert(NBTRAP < (LINE - 1) * (COLUMN - 1)); //Make sure that there is not too much trap

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

        // usedX[NBTRAP] = getPosPlayerX(this->player);
        // usedY[NBTRAP] = getPosPlayerY(this->player);
    
        generateUniqueCoordinates(&X, &Y, usedX, usedY, i);
        TrapInitialisation(this->trap[i], X, Y);        //Set trap coordinates correctly
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
    //printf("\nIl te reste %d vies.\n", getHealthPlayer(this->player));
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


// Implementation of action functions
static void actionNop(Game* this) {
    assert(this != NULL);
    // Does nothing
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
    // This action is used in combination with the code in main.c
    // to check the game status
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
    initTransitionMatrix(this);
}

extern void gameHandleEvent(Game* this, GameEvent event) {
    assert(this != NULL);
    TransitionAction transition;
    GameState newState;
    
    assert(this->currentState != S_DEATH);
    
    transition = this->transitionMatrix[this->currentState][event];
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


// static const Transition transition_table[] = {
//     [INIT_A] = {ACQUISITION_CLAVIER, A_NOP},
//     [ACQUISITION_CLAVIER] = {ACQUISITION_CLAVIER, A_NOP},
//     [DEPLACEMENT_GAUCHE] = {VERIFICATION_VICTOIRE, A_DEPLACER},
//     [DEPLACEMENT_DROITE] = {VERIFICATION_VICTOIRE, A_DEPLACER},
//     [DEPLACEMENT_HAUT] = {VERIFICATION_VICTOIRE, A_DEPLACER},
//     [DEPLACEMENT_BAS] = {VERIFICATION_VICTOIRE, A_DEPLACER},
//     [VERIFICATION_VICTOIRE] = {ACQUISITION_CLAVIER, A_VERIFIER_VICTOIRE},
// };



// extern void run(Etat* etat, Evenement evenement, Game* game) {
//     assert(*etat != INIT_A);

//     Etat destination = transition_table[*etat].etat_destination;
//     Action action = transition_table[*etat].action;

//     switch(action) {
//         case A_NOP:
//             break;
//         case A_DEPLACER:
//             if (evenement == E_DEPLACER_GAUCHE) {
//                 setPosPlayerY(getPlayerGame(game), getPosPlayerY(getPlayerGame(game)) - 1);
//             } else if (evenement == E_DEPLACER_DROITE) {
//                 setPosPlayerY(getPlayerGame(game), getPosPlayerY(getPlayerGame(game)) + 1);
//             } else if (evenement == E_DEPLACER_HAUT) {
//                 setPosPlayerX(getPlayerGame(game), getPosPlayerX(getPlayerGame(game)) - 1);
//             } else if (evenement == E_DEPLACER_BAS) {
//                 setPosPlayerX(getPlayerGame(game), getPosPlayerX(getPlayerGame(game)) + 1);
//             }
//             break;
//         case A_VERIFIER_VICTOIRE:
//             gamePrint(game);
//             int status = checkGameStatus(game);
//             if (status == 1) { // Win
//                 printf("Tu as gagné, wp tu es tombé sur le trésor \n");
//                 *etat = INIT_A;
//             } else if (status == 2) { // Lose
//                 printf("Tu as perdu\n");
//                 *etat = INIT_A;
//             }
//             break;
//         default:
//             assert(0);
//             break;
//     }

//     if(destination != INIT_A) {
//         *etat = destination;
//     }
// }
