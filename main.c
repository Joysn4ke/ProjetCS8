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
    Game *game = newGame();
    gameInitialisation(game);
    gamePrint(game);
    startGame(game);
    
    //Main loop
    while (!gameIsFinished(game)) {
        acquisitionClavier(game);
        deplacement(game);
        checkWin(game);
    }
    
    freeGame(game);
    return 0;
}

