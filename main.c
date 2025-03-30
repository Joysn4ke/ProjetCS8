#include <stdlib.h>
#include <stdio.h>

#include "Game.h"
#include "Getch.h"
#include "Common.h"
#include "StateMachine.h"

int main() {
    char key;
    int status;
    Event currentEvent;
    
    Game *game = newGame(); //Création du jeu
    StateMachine_init(game); // Initialisation de la machine à états
    StateMachine_handleEvent(E_START); //Démarrer le jeu
    
    // Boucle principale
    while (!StateMachine_isGameFinished()) {
        switch (StateMachine_getCurrentState()) {
            case S_ACQUISITION_CLAVIER:
                key = getch();
                currentEvent = StateMachine_getEventFromKey(key);
                StateMachine_handleEvent(currentEvent);
                break;
                
            case S_DEPLACEMENT:
                StateMachine_handleEvent(E_MOVE_DONE);
                break;
                
            case S_VERIFICATION_VICTOIRE:
                status = checkGameStatus(game);
                if (status == 1) { // Win
                    StateMachine_handleEvent(E_VICTORY);
                } else if (status == 2) { // Lose
                    StateMachine_handleEvent(E_DEFEAT);
                } else { // Game continue
                    StateMachine_handleEvent(E_CONTINUE);
                }
                break;
                
            case S_GAME_OVER:
                // La machine à états devrait avoir marqué le jeu comme terminé
                break;
                
            default:
                fprintf(stderr, "État non géré: %d\n", StateMachine_getCurrentState());
                return 1;
        }
    }
    
    return 0;
}
