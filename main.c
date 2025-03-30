// #include <stdlib.h>
// #include <stdio.h>

// #include "Game.h"
// #include "Grille.h"
// #include "Getch.h"
// #include "Treasure.h"
// #include "Map.h"
// #include "Player.h"
// #include "Common.h"
// #include "Trap.h"


// typedef enum {
//     INIT_A,
//     ACQUISITION_CLAVIER,
//     DEPLACEMENT_GAUCHE,
//     DEPLACEMENT_DROITE,
//     DEPLACEMENT_HAUT,
//     DEPLACEMENT_BAS,
//     VERIFICATION_VICTOIRE
// } Etat;



// int main()
// {
//     char car;
//     int fin = 0;
//     Etat etat = INIT_A;

//     Game *game = newGame();
//     gameInitialisation(game);
//     gamePrint(game);

//     while(!fin)
//     {
//         switch(etat)
//         {
//             case INIT_A:
//                 etat = ACQUISITION_CLAVIER;
//                 break;

//             case ACQUISITION_CLAVIER:
//                 car = getch();
//                 setGridCellMap(getMapGame(game), getPosPlayerX(getPlayerGame(game)), getPosPlayerY(getPlayerGame(game)), ' ');
//                 switch(car)
//                 {
//                     case 'l':  //leave
//                         fin = 1;
//                         break;
//                     case 65: 
//                     case 'z':     //on se déplace vers le haut
//                         etat = DEPLACEMENT_HAUT;
//                         break;
//                     case 66: 
//                     case 's':
//                         etat = DEPLACEMENT_BAS;   //on se déplace vers le bas
//                         break;
//                     case 67: 
//                     case 'd':
//                         etat = DEPLACEMENT_DROITE;    //on se déplace vers la droite
//                         break;
//                     case 68: 
//                     case 'q':
//                         etat = DEPLACEMENT_GAUCHE;  //on se déplacde vers la gauche
//                         break;
//                     default:
//                         etat = ACQUISITION_CLAVIER;  //reprise du clavier avec les touches
//                         break;
//                 }
//                 break;

//             case DEPLACEMENT_GAUCHE:
//                 if (getPosPlayerY(getPlayerGame(game)) > 0) setPosPlayerY(getPlayerGame(game), getPosPlayerY(getPlayerGame(game)) - 1);
//                 etat = VERIFICATION_VICTOIRE;
//                 break;

//             case DEPLACEMENT_DROITE:
//                 if (getPosPlayerY(getPlayerGame(game)) < COLUMN - 1) setPosPlayerY(getPlayerGame(game), getPosPlayerY(getPlayerGame(game)) + 1);
//                 etat = VERIFICATION_VICTOIRE;
//                 break;

//             case DEPLACEMENT_HAUT:
//                 if (getPosPlayerX(getPlayerGame(game)) > 0) setPosPlayerX(getPlayerGame(game), getPosPlayerX(getPlayerGame(game)) - 1);
//                 etat = VERIFICATION_VICTOIRE;
//                 break;

//             case DEPLACEMENT_BAS:
//                 if (getPosPlayerX(getPlayerGame(game)) < LINE - 1) setPosPlayerX(getPlayerGame(game), getPosPlayerX(getPlayerGame(game)) + 1);
//                 etat = VERIFICATION_VICTOIRE;
//                 break;

//             case VERIFICATION_VICTOIRE:
//                 gamePrint(game);

//                 int status = checkGameStatus(game);
//                 if (status == 1) { //Win
//                     printf("Tu as gagné, wp tu es tombé sur le trésor \n");
//                     fin = 1;
//                     etat = INIT_A;
//                 } else if (status == 2) { //Lose
//                     printf("Tu as perdu\n");
//                     fin = 1;
//                     etat = INIT_A;
//                 } else { //Game continue
//                     etat = ACQUISITION_CLAVIER;
//                 }
//                 break;
//             break;
//         }
//     }

//     freeGame(game);
//     return 0;
// }


// #include <stdlib.h>
// #include <stdio.h>

// #include "Getch.h"
// #include "Game.h"
// #include "Common.h"
// #include "StateMachine.h"

// int main() {
//     char key;
//     int status;
//     Event currentEvent;
    
//     Game *game = newGame(); //Création du jeu
//     StateMachine_init(game); // Initialisation de la machine à états
//     StateMachine_handleEvent(E_START); //Démarrer le jeu
    
//     // Boucle principale
//     while (!StateMachine_isGameFinished()) {
//         switch (StateMachine_getCurrentState()) {
//             case S_ACQUISITION_CLAVIER:
//                 key = getch();
//                 currentEvent = StateMachine_getEventFromKey(key);
//                 StateMachine_handleEvent(currentEvent);
//                 break;
                
//             case S_DEPLACEMENT:
//                 StateMachine_handleEvent(E_MOVE_DONE);
//                 break;
                
//             case S_VERIFICATION_VICTOIRE:
//                 status = checkGameStatus(game);
//                 if (status == 1) { // Win
//                     StateMachine_handleEvent(E_VICTORY);
//                 } else if (status == 2) { // Lose
//                     StateMachine_handleEvent(E_DEFEAT);
//                 } else { // Game continue
//                     StateMachine_handleEvent(E_CONTINUE);
//                 }
//                 break;
                
//             case S_GAME_OVER:
//                 // La machine à états devrait avoir marqué le jeu comme terminé
//                 break;
                
//             default:
//                 fprintf(stderr, "État non géré: %d\n", StateMachine_getCurrentState());
//                 return 1;
//         }
//     }
    
//     freeGame(game);
//     return 0;
// }


#include <stdlib.h>
#include <stdio.h>

#include "Getch.h"
#include "Game.h"
#include "Common.h"

int main() {
    char key;
    int status;
    GameEvent currentEvent;
    
    Game *game = newGame(); //Create the game includes state machine initialization
    gameInitialisation(game);
    gamePrint(game);
    gameHandleEvent(game, E_START); //Start the game
    
    // Main loop
    while (!gameIsFinished(game)) {
        switch (gameGetCurrentState(game)) {
            case S_ACQUISITION_CLAVIER:
                key = getch();
                currentEvent = gameGetEventFromKey(key);
                gameHandleEvent(game, currentEvent);
                break;
                
            case S_DEPLACEMENT:
                gameHandleEvent(game, E_MOVE_DONE);
                break;
                
            case S_VERIFICATION_VICTOIRE:
                status = checkGameStatus(game);
                if (status == 1) { // Win
                    gameHandleEvent(game, E_VICTORY);
                } else if (status == 2) { // Lose
                    gameHandleEvent(game, E_DEFEAT);
                } else { // Game continue
                    gameHandleEvent(game, E_CONTINUE);
                }
                break;
                
            case S_GAME_OVER:
                // The state machine should have marked the game as finished
                break;
                
            default:
                fprintf(stderr, "État non géré: %d\n", gameGetCurrentState(game));
                return 1;
        }
    }
    
    freeGame(game);
    return 0;
}

