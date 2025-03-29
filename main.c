#include <stdlib.h>
#include <stdio.h>

#include "Game.h"
#include "Grille.h"
#include "Getch.h"
#include "Treasure.h"
#include "Map.h"
#include "Player.h"
#include "Common.h"
#include "Trap.h"


int main() {
    char car;
    int fin = 0;
    Etat etat = INIT_A;

    Game *game = newGame();
    gameInitialisation(game);
    gamePrint(game);

    while (!fin) {
        switch(etat) {
            case INIT_A:
                etat = ACQUISITION_CLAVIER;
                break;

            case ACQUISITION_CLAVIER:
                car = getch();
                setGridCellMap(getMapGame(game), getPosPlayerX(getPlayerGame(game)), getPosPlayerY(getPlayerGame(game)), ' ');

                switch(car) {
                    case 'l':  // leave
                        fin = 1;
                        etat = INIT_A;
                        break;
                    case 'z':
                    case 65:   // on se déplace vers le haut
                        run(&etat, E_DEPLACER_HAUT, game);
                        break;
                    case 's':
                    case 66:   // on se déplace vers le bas
                        run(&etat, E_DEPLACER_BAS, game);
                        break;
                    case 'd':
                    case 67:   // on se déplace vers la droite
                        run(&etat, E_DEPLACER_DROITE, game);
                        break;
                    case 'q':
                    case 68:   // on se déplace vers la gauche
                        run(&etat, E_DEPLACER_GAUCHE, game);
                        break;
                    default:
                        break;
                }
                break;

            case VERIFICATION_VICTOIRE:
                run(&etat, E_VICTOIRE, game);
                break;

            default:
                break;
        }
    }

    freeGame(game);
    return 0;
}