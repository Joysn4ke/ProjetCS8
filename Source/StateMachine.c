// #include <stdlib.h>
// #include <stdio.h>
// #include <assert.h>

// #include "StateMachine.h"
// #include "Player.h"
// #include "Map.h"
// #include "Getch.h"
// #include "Common.h"

// // Structure pour les transitions
// typedef struct {
//     Action action;
//     State destinationState;
// } TransitionAction;

// // Variables globales pour la machine à états
// static Game *myGame = NULL;
// static State myState = S_INIT;
// static int gameFinished = 0;

// // Déclaration de la matrice de transition
// static TransitionAction mySm[STATE_NB][EVENT_NB];

// // Définition des pointeurs de fonction
// typedef void (*ActionPtr)();

// // Implémentation des actions
// static void actionNop() {
//     // Ne fait rien
// }

// static void actionInitGame() {
//     gameInitialisation(myGame);
//     gamePrint(myGame);
// }

// static void actionMoveUp() {
//     setGridCellMap(getMapGame(myGame), getPosPlayerX(getPlayerGame(myGame)), getPosPlayerY(getPlayerGame(myGame)), ' ');
//     if (getPosPlayerX(getPlayerGame(myGame)) > 0) {
//         setPosPlayerX(getPlayerGame(myGame), getPosPlayerX(getPlayerGame(myGame)) - 1);
//     }
// }

// static void actionMoveDown() {
//     setGridCellMap(getMapGame(myGame), getPosPlayerX(getPlayerGame(myGame)), getPosPlayerY(getPlayerGame(myGame)), ' ');
//     if (getPosPlayerX(getPlayerGame(myGame)) < LINE - 1) {
//         setPosPlayerX(getPlayerGame(myGame), getPosPlayerX(getPlayerGame(myGame)) + 1);
//     }
// }

// static void actionMoveLeft() {
//     setGridCellMap(getMapGame(myGame), getPosPlayerX(getPlayerGame(myGame)), getPosPlayerY(getPlayerGame(myGame)), ' ');
//     if (getPosPlayerY(getPlayerGame(myGame)) > 0) {
//         setPosPlayerY(getPlayerGame(myGame), getPosPlayerY(getPlayerGame(myGame)) - 1);
//     }
// }

// static void actionMoveRight() {
//     setGridCellMap(getMapGame(myGame), getPosPlayerX(getPlayerGame(myGame)), getPosPlayerY(getPlayerGame(myGame)), ' ');
//     if (getPosPlayerY(getPlayerGame(myGame)) < COLUMN - 1) {
//         setPosPlayerY(getPlayerGame(myGame), getPosPlayerY(getPlayerGame(myGame)) + 1);
//     }
// }

// static void actionPrintGame() {
//     gamePrint(myGame);
// }

// static void actionCheckStatus() {
//     // Cette action est utilisée en combinaison avec le code dans main.c
//     // pour vérifier le statut du jeu
// }

// static void actionPrintVictory() {
//     printf("Tu as gagné, wp tu es tombé sur le trésor \n");
//     gameFinished = 1;
// }

// static void actionPrintDefeat() {
//     printf("Tu as perdu\n");
//     gameFinished = 1;
// }

// static void actionFreeGame() {
//     freeGame(myGame);
//     myGame = NULL;
// }

// // Tableau des actions à réaliser
// static const ActionPtr actionsTab[ACTION_NB] = {
//     &actionNop,
//     &actionInitGame,
//     &actionMoveUp,
//     &actionMoveDown,
//     &actionMoveLeft,
//     &actionMoveRight,
//     &actionPrintGame,
//     &actionCheckStatus,
//     &actionPrintVictory,
//     &actionPrintDefeat,
//     &actionFreeGame
// };

// // Initialisation de la matrice de transition
// static void initTransitionMatrix() {
//     // Initialisation de tous les états à une valeur par défaut
//     for (int i = 0; i < STATE_NB; i++) {
//         for (int j = 0; j < EVENT_NB; j++) {
//             mySm[i][j].action = A_NOP;
//             mySm[i][j].destinationState = S_FORGET;
//         }
//     }

//     // Définition des transitions spécifiques
    
//     // Depuis S_INIT
//     mySm[S_INIT][E_START].action = A_INIT_GAME;
//     mySm[S_INIT][E_START].destinationState = S_ACQUISITION_CLAVIER;

//     // Depuis S_ACQUISITION_CLAVIER
//     mySm[S_ACQUISITION_CLAVIER][E_KEY_UP].action = A_MOVE_UP;
//     mySm[S_ACQUISITION_CLAVIER][E_KEY_UP].destinationState = S_DEPLACEMENT;
    
//     mySm[S_ACQUISITION_CLAVIER][E_KEY_DOWN].action = A_MOVE_DOWN;
//     mySm[S_ACQUISITION_CLAVIER][E_KEY_DOWN].destinationState = S_DEPLACEMENT;
    
//     mySm[S_ACQUISITION_CLAVIER][E_KEY_LEFT].action = A_MOVE_LEFT;
//     mySm[S_ACQUISITION_CLAVIER][E_KEY_LEFT].destinationState = S_DEPLACEMENT;
    
//     mySm[S_ACQUISITION_CLAVIER][E_KEY_RIGHT].action = A_MOVE_RIGHT;
//     mySm[S_ACQUISITION_CLAVIER][E_KEY_RIGHT].destinationState = S_DEPLACEMENT;
    
//     mySm[S_ACQUISITION_CLAVIER][E_KEY_QUIT].action = A_FREE_GAME;
//     mySm[S_ACQUISITION_CLAVIER][E_KEY_QUIT].destinationState = S_GAME_OVER;
    
//     mySm[S_ACQUISITION_CLAVIER][E_OTHER_KEY].action = A_NOP;
//     mySm[S_ACQUISITION_CLAVIER][E_OTHER_KEY].destinationState = S_ACQUISITION_CLAVIER;

//     // Depuis S_DEPLACEMENT
//     mySm[S_DEPLACEMENT][E_MOVE_DONE].action = A_PRINT_GAME;
//     mySm[S_DEPLACEMENT][E_MOVE_DONE].destinationState = S_VERIFICATION_VICTOIRE;

//     // Depuis S_VERIFICATION_VICTOIRE
//     mySm[S_VERIFICATION_VICTOIRE][E_VICTORY].action = A_PRINT_VICTORY;
//     mySm[S_VERIFICATION_VICTOIRE][E_VICTORY].destinationState = S_GAME_OVER;
    
//     mySm[S_VERIFICATION_VICTOIRE][E_DEFEAT].action = A_PRINT_DEFEAT;
//     mySm[S_VERIFICATION_VICTOIRE][E_DEFEAT].destinationState = S_GAME_OVER;
    
//     mySm[S_VERIFICATION_VICTOIRE][E_CONTINUE].action = A_NOP;
//     mySm[S_VERIFICATION_VICTOIRE][E_CONTINUE].destinationState = S_ACQUISITION_CLAVIER;
// }

// // Initialisation de la machine à états
// extern void StateMachine_init(Game* game) {
//     myGame = game;
//     myState = S_INIT;
//     gameFinished = 0;
//     initTransitionMatrix();
// }

// // Exécution d'une transition en fonction de l'événement
// extern void StateMachine_handleEvent(Event event) {
//     TransitionAction transition;
//     State newState;
    
//     assert(myState != S_DEATH);
    
//     transition = mySm[myState][event];
//     newState = transition.destinationState;
    
//     if (newState != S_FORGET) {
//         actionsTab[transition.action](); // Exécution de l'action
//         myState = newState;
//     }
// }

// // Fonction pour obtenir l'événement correspondant à une touche
// extern Event StateMachine_getEventFromKey(char key) {
//     switch(key) {
//         case 'l':
//             return E_KEY_QUIT;
//         case 65: 
//         case 'z':
//             return E_KEY_UP;
//         case 66: 
//         case 's':
//             return E_KEY_DOWN;
//         case 67: 
//         case 'd':
//             return E_KEY_RIGHT;
//         case 68: 
//         case 'q':
//             return E_KEY_LEFT;
//         default:
//             return E_OTHER_KEY;
//     }
// }

// // Fonction pour vérifier si le jeu est terminé
// extern int StateMachine_isGameFinished() {
//     return gameFinished;
// }

// // Fonction pour récupérer l'état actuel
// extern State StateMachine_getCurrentState() {
//     return myState;
// }