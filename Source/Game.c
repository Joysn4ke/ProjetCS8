#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "assert.h"

#include "Getch.h"

#include "Common.h"
#include "Game.h"
#include "Map.h"
#include "Player.h"
#include "Trap.h"
#include "Treasure.h"
#include "Pirate.h"


/**
 * @brief Transition action pair
 * 
 * Associates an action with a destination state for state transitions.
 */
struct TransitionAction_s {
    GameAction action;
    GameState destinationState;
};


/**
 * @brief Main game structure
 * 
 * Contains all game entities and state machine elements.
 */
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
    [S_ACQUISITION_CLAVIER][E_START] = {A_NOP, S_ACQUISITION_CLAVIER},
    [S_ACQUISITION_CLAVIER][E_KEY_UP] = {A_MOVE_UP, S_DEPLACEMENT},
    [S_ACQUISITION_CLAVIER][E_KEY_DOWN] = {A_MOVE_DOWN, S_DEPLACEMENT},
    [S_ACQUISITION_CLAVIER][E_KEY_LEFT] = {A_MOVE_LEFT, S_DEPLACEMENT},
    [S_ACQUISITION_CLAVIER][E_KEY_RIGHT] = {A_MOVE_RIGHT, S_DEPLACEMENT},
    [S_ACQUISITION_CLAVIER][E_KEY_QUIT] = {A_FREE_GAME, S_GAME_OVER},
    [S_ACQUISITION_CLAVIER][E_OTHER_KEY] = {A_NOP, S_ACQUISITION_CLAVIER},
    [S_ACQUISITION_CLAVIER][E_MOVE_DONE] = {A_NOP, S_ACQUISITION_CLAVIER},
    [S_ACQUISITION_CLAVIER][E_VICTORY] = {A_NOP, S_ACQUISITION_CLAVIER},
    [S_ACQUISITION_CLAVIER][E_DEFEAT] = {A_NOP, S_ACQUISITION_CLAVIER},
    [S_ACQUISITION_CLAVIER][E_CONTINUE] = {A_NOP, S_ACQUISITION_CLAVIER},

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
        return (TransitionAction){A_NOP, S_ACQUISITION_CLAVIER}; //Valeur par défaut pour toute transition invalide
    }
    return transitionMatrixConst[state][event];
}



/**
 * @brief Creates a new Game object
 * 
 * Allocates memory for a new Game and all its components.
 * 
 * @return Pointer to the newly created Game
 */
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


/**
 * @brief Initializes a Game object
 * 
 * Sets up the game state, map, and all entities.
 * 
 * @param this Pointer to the Game to initialize
 */
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
    int usedX[TOTAL_ENTITY];
    int usedY[TOTAL_ENTITY];
    int usedCount = 0;
    
    //Initialize player coordinates
    int playerX, playerY;
    generateUniqueCoordinates(&playerX, &playerY, usedX, usedY, usedCount);
    
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


/**
 * @brief Frees memory used by a Game object
 * 
 * Releases all resources associated with the given Game.
 * 
 * @param this Pointer to the Game to free
 */
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


/**
 * @brief Prints the current game state
 * 
 * Displays the game map and player health.
 * 
 * @param this Pointer to the Game
 */
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

    //Debug
    // printf("playerX : %d\n", getPosPlayerX(this->player));
    // printf("playerY : %d\n", getPosPlayerY(this->player));
    // printf("treasureX : %d\n", getPosTreasureX(this->treasure));
    // printf("treasureY : %d\n", getPosTreasureY(this->treasure));
    // printf("pirateX : %d\n", getPosPirateX(this->pirate));
    // printf("pirateY : %d\n", getPosPirateY(this->pirate));
}


/**
 * @brief Checks the game status
 * 
 * Determines if the player has won, lost, or if the game continues.
 * 
 * @param this Pointer to the Game
 * @return 0 if game continues, 1 if player wins, 2 if player loses
 */
extern int checkGameStatus(Game* this) {
    //Verif if treasure found
    if (getPosPlayerX(getPlayerGame(this)) == getPosTreasureX(getTreasureGame(this)) &&
        getPosPlayerY(getPlayerGame(this)) == getPosTreasureY(getTreasureGame(this))) {
        return 1; //Win
    }

    if (getPosPlayerX(getPlayerGame(this)) == getPosPirateX(getPirateGame(this)) &&
        getPosPlayerY(getPlayerGame(this)) == getPosPirateY(getPirateGame(this))) {

        printf("Le pirate t'as rattrapé, tu perds une vie\n");
        setHealthPlayer(this->player, getHealthPlayer(this->player) - 1);
        movePirate(this, 0);
    }
    
    //Verif player on trap
    for (int i = 0; i < NBTRAP; i++) {
        if (getPosPlayerX(this->player) == getPosTrapX(getTrapGame(this)[i]) && getPosPlayerY(getPlayerGame(this)) == getPosTrapY(getTrapGame(this)[i])) {
            
            printf("Tu es tombé sur un trap, tu perds une vie\n");
            setHealthPlayer(this->player, getHealthPlayer(this->player) - 1);

            setNullPosTrapX(getTrapGame(this)[i]);
            setNullPosTrapY(getTrapGame(this)[i]);
            break;
        }
    }

    if (getHealthPlayer(this->player) <= 0) {
        printf("Tu n'as plus de vie\n");
        return 2; //Lose
    }

    return 0;
}



/**
 * @brief Moves the pirate character
 * 
 * Determines and executes the pirate's movement based on player position.
 * 
 * @param this Pointer to the Game
 * @param bool If true, move pirate intelligently toward player; if false, move randomly
 */
extern void movePirate(Game* this, int bool) {
    assert(this != NULL);
    
    //Get current positions
    int pirateX = getPosPirateX(this->pirate);
    int pirateY = getPosPirateY(this->pirate);
    int playerX = getPosPlayerX(this->player);
    int playerY = getPosPlayerY(this->player);
    
    setGridCellMap(this->map, pirateX, pirateY, ' ');  //Clear pirate's current position on map
    
    int newPirateX = pirateX;
    int newPirateY = pirateY;
    
    if (pirateX == playerX && bool) { //Case 1: Pirate on same row as player
        //Move toward player vertically
        int moveY = (playerY > pirateY) ? 1 : -1;
        newPirateY = pirateY + moveY;
    } else if (pirateY == playerY && bool) { //Case 2: Pirate on same column as player
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
        movePirate(this, 1);
    }
}

static void actionMoveDown(Game* this) {
    if (getPosPlayerX(this->player) < LINE - 1) {
        setGridCellMap(this->map, getPosPlayerX(this->player), getPosPlayerY(this->player), ' ');
        setPosPlayerX(this->player, getPosPlayerX(this->player) + 1);
    }
    if (!(getPosPlayerX(this->player) == getPosPirateX(this->pirate) && getPosPlayerY(this->player) == getPosPirateY(this->pirate))) {
        movePirate(this, 1);
    }
}

static void actionMoveLeft(Game* this) {
    if (getPosPlayerY(this->player) > 0) {
        setGridCellMap(this->map, getPosPlayerX(this->player), getPosPlayerY(this->player), ' ');
        setPosPlayerY(this->player, getPosPlayerY(this->player) - 1);
    }
    if (!(getPosPlayerX(this->player) == getPosPirateX(this->pirate) && getPosPlayerY(this->player) == getPosPirateY(this->pirate))) {
        movePirate(this, 1);
    }
}

static void actionMoveRight(Game* this) {
    if (getPosPlayerY(this->player) < COLUMN - 1) {
        setGridCellMap(this->map, getPosPlayerX(this->player), getPosPlayerY(this->player), ' ');
        setPosPlayerY(this->player, getPosPlayerY(this->player) + 1);
    }
    if (!(getPosPlayerX(this->player) == getPosPirateX(this->pirate) && getPosPlayerY(this->player) == getPosPirateY(this->pirate))) {
        movePirate(this, 1);
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
/**
 * @brief Initializes the game state machine
 * 
 * Sets up the initial state and transition matrix.
 * 
 * @param this Pointer to the Game
 */
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


/**
 * @brief Handles a game event
 * 
 * Processes an event through the state machine, executing appropriate actions
 * and transitioning to the next state.
 * 
 * @param this Pointer to the Game
 * @param event The event to handle
 */
extern void gameHandleEvent(Game* this, GameEvent event) {
    assert(this != NULL);
    TransitionAction transition;
    GameState newState;
    
    assert(this->currentState != S_DEATH);
    
    transition  = getTransition(this->currentState, event);
    newState = transition.destinationState;

    // printf("newState %d\n", newState);
    
    if (newState != S_FORGET) {
        actionsTab[transition.action](this); //Execute the action
        this->currentState = newState;
    }
}


/**
 * @brief Converts a keyboard character to a game event
 * 
 * @param key The keyboard character
 * @return Corresponding GameEvent
 */
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


/**
 * @brief Checks if the game is finished
 * 
 * @param this Pointer to the Game
 * @return Non-zero if game is finished, 0 otherwise
 */
extern int gameIsFinished(Game* this) {
    assert(this != NULL);
    return this->gameFinished;
}


/**
 * @brief Gets the current game state
 * 
 * @param this Pointer to the Game
 * @return Current GameState
 */
extern GameState gameGetCurrentState(Game* this) {
    assert(this != NULL);
    return this->currentState;
}


extern void startGame(Game* game) {
    gameHandleEvent(game, E_START); //Start the game
}

extern void acquisitionClavier(Game* game) {
    char key;
    GameEvent currentEvent;

    key = getch();
    currentEvent = gameGetEventFromKey(key);
    gameHandleEvent(game, currentEvent);
}

extern void deplacement(Game* game) {
    gameHandleEvent(game, E_MOVE_DONE);
}

extern void checkWin(Game* game) {
    int status;
    status = checkGameStatus(game);
    if (status == 1) { // Win
        gameHandleEvent(game, E_VICTORY);
    } else if (status == 2) { // Lose
        gameHandleEvent(game, E_DEFEAT);
    } else { // Game continue
        gameHandleEvent(game, E_CONTINUE);
    }
}

// Getter & Setter
/**
 * @brief Gets the map from a Game
 * 
 * @param game Pointer to the Game
 * @return Pointer to the Map
 */
extern Map* getMapGame(Game* game) {
    assert(game != NULL);
    return game->map;
}


/**
 * @brief Gets the player from a Game
 * 
 * @param game Pointer to the Game
 * @return Pointer to the Player
 */
extern Player* getPlayerGame(Game* game) {
    assert(game != NULL);
    return game->player;
}


/**
 * @brief Gets the traps from a Game
 * 
 * @param game Pointer to the Game
 * @return Pointer to the Traps
 */
extern Trap** getTrapGame(Game* game) {
    assert(game != NULL);
    return game->trap;
}


/**
 * @brief Gets the treasure from a Game
 * 
 * @param game Pointer to the Game
 * @return Pointer to the Treasure
 */
extern Treasure* getTreasureGame(Game* game) {
    assert(game != NULL);
    return game->treasure;
}


/**
 * @brief Gets the pirate from a Game
 * 
 * @param game Pointer to the Game
 * @return Pointer to the Pirate
 */
extern Pirate* getPirateGame(Game* game) {
    assert(game != NULL);
    return game->pirate;
}


/**
 * @brief Gets the grid from a Game
 * 
 * @param game Pointer to the Game
 * @return 2D char array representing the grid
 */
extern char** getGridGame(Game* game) {
    assert(game != NULL);
    return getGridMap(game->map);
}
