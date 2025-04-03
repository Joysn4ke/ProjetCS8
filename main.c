/**
 * @file main.c
 * @brief Main program for the game, handling the game loop and events.
 *
 * This program initializes the game, displays the initial state, and manages user input 
 * as well as game state transitions based on events. It relies on a state machine to 
 * process different phases of the game, including input acquisition, movement, victory 
 * verification, and game over handling.
 *
 * @author [J M]
 * @date [02/04/2024]
 */
#include <stdlib.h>
#include <stdio.h>

#include "Getch.h"
#include "Game.h"
#include "Common.h"


int main() {
    // char key;
    // int status;
    // GameEvent currentEvent;
    
    Game *game = newGame();
    gameInitialisation(game);
    gamePrint(game);
    //gameHandleEvent(game, E_START); //Start the game
    startGame(game);
    
    //Main loop
    while (!gameIsFinished(game)) {
        // switch (gameGetCurrentState(game)) {
        //     case S_ACQUISITION_CLAVIER:
        //         key = getch();
        //         currentEvent = gameGetEventFromKey(key);
        //         gameHandleEvent(game, currentEvent);
        //         break;
                
        //     case S_DEPLACEMENT:
        //         gameHandleEvent(game, E_MOVE_DONE);
        //         break;
                
        //     case S_VERIFICATION_VICTOIRE:
        //         status = checkGameStatus(game);
        //         if (status == 1) { // Win
        //             gameHandleEvent(game, E_VICTORY);
        //         } else if (status == 2) { // Lose
        //             gameHandleEvent(game, E_DEFEAT);
        //         } else { // Game continue
        //             gameHandleEvent(game, E_CONTINUE);
        //         }
        //         break;
                
        //     case S_GAME_OVER:
        //         //The state machine should have marked the game as finished
        //         break;
                
        //     default:
        //         fprintf(stderr, "État non géré: %d\n", gameGetCurrentState(game));
        //         return 1;
        // }
        acquisitionClavier(game);
        deplacement(game);
        checkWin(game);
    }
    
    freeGame(game);
    return 0;
}

