#include <stdlib.h>
#include <stdio.h>
#include <unistd.h> //sleep

#include "Getch.h"
#include "Game.h"
#include "Common.h"

int main() {
    char key;
    int status;
    GameEvent currentEvent;
    
    Game *game = newGame();
    gameInitialisation(game);
    gamePrint(game);
    gameHandleEvent(game, E_START); //Start the game
    
    //Main loop
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
                //The state machine should have marked the game as finished
                break;
                
            default:
                fprintf(stderr, "État non géré: %d\n", gameGetCurrentState(game));
                return 1;
        }
    }
    
    freeGame(game);
    // sleep(2);
    // system("clear");
    return 0;
}

