#ifndef GAME_H
#define GAME_H

#include "Map.h"
#include "Player.h"
#include "Treasure.h"
#include "Pirate.h"
#include "Trap.h"

// Define state machine elements
/**
 * @brief Game state machine states
 * 
 * Defines all possible states for the game state machine.
 */
typedef enum {
    S_INIT,
    S_ACQUISITION_CLAVIER,
    S_DEPLACEMENT,
    S_VERIFICATION_VICTOIRE,
    S_GAME_OVER,
    S_DEATH,    //État de mort (non utilisé, pour la gestion d'erreur)
    S_FORGET,   //État spécial pour ne pas changer d'état
    STATE_NB    //Nombre total d'états
} GameState;


/**
 * @brief Game events
 * 
 * Defines all possible events that can trigger state transitions.
 */
typedef enum {
    E_START,
    E_KEY_UP,
    E_KEY_DOWN,
    E_KEY_LEFT,
    E_KEY_RIGHT,
    E_KEY_QUIT,
    E_OTHER_KEY,
    E_MOVE_DONE,
    E_VICTORY,
    E_DEFEAT,
    E_CONTINUE,
    EVENT_NB    //Nombre total d'événements
} GameEvent;


/**
 * @brief Game actions
 * 
 * Defines all possible actions that can be triggered during state transitions.
 */
typedef enum {
    A_NOP,              //Aucune action
    A_INIT_GAME,        //Initialiser le jeu
    A_MOVE_UP,          //Déplacer vers le haut
    A_MOVE_DOWN,        //Déplacer vers le bas
    A_MOVE_LEFT,        //Déplacer vers la gauche
    A_MOVE_RIGHT,       //Déplacer vers la droite
    A_PRINT_GAME,       //Afficher le jeu
    A_CHECK_STATUS,     //Vérifier le statut du jeu
    A_PRINT_VICTORY,    //Afficher le message de victoire
    A_PRINT_DEFEAT,     //Afficher le message de défaite
    A_FREE_GAME,        //Libérer les ressources du jeu
    ACTION_NB           // Nombre total d'actions
} GameAction;


typedef struct TransitionAction_s TransitionAction;

typedef struct Game_s Game;

extern Game* newGame();
extern void gameInitialisation(Game* this);
extern void freeGame(Game* this);

extern void gamePrint(Game* this);
extern int checkGameStatus(Game* this);
extern void movePirate(Game* this, int bool);

//Incorporated StateMachine functions
extern void gameInitStateMachine(Game* this);
extern void gameHandleEvent(Game* this, GameEvent event);
extern int gameIsFinished(Game* this);
extern GameEvent gameGetEventFromKey(char key);
extern GameState gameGetCurrentState(Game* this);

//Getter & Setter
extern Map* getMapGame(Game* game);
extern Player* getPlayerGame(Game* game);
extern Treasure* getTreasureGame(Game* game);
extern Pirate* getPirateGame(Game* game);
extern char** getGridGame(Game* game);
extern Trap** getTrapGame(Game* game);


#endif //GAME_H
