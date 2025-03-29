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


typedef enum {
    INIT_A,
    ACQUISITION_CLAVIER,
    DEPLACEMENT_GAUCHE,
    DEPLACEMENT_DROITE,
    DEPLACEMENT_HAUT,
    DEPLACEMENT_BAS,
    VERIFICATION_VICTOIRE
} Etat;



int main()
{
    char car;
    int fin = 0;
    //int vie = 3;
    Etat etat = INIT_A;

    Game *game = newGame();
    gameInitialisation(game);

    //system("clear");
    gamePrint(game);

    while(!fin)
    {
        switch(etat)
        {
            case INIT_A:
                etat = ACQUISITION_CLAVIER;
                break;

            case ACQUISITION_CLAVIER:
                car = getch();
                setGridCellMap(getMapGame(game), getPosPlayerX(getPlayerGame(game)), getPosPlayerY(getPlayerGame(game)), ' ');
                switch(car)
                {
                    case 'l':  //leave
                        fin = 1;
                        break;
                    case 65: 
                    case 'z':     //on se déplace vers le haut
                        etat = DEPLACEMENT_HAUT;
                        break;
                    case 66: 
                    case 's':
                        etat = DEPLACEMENT_BAS;   //on se déplace vers le bas
                        break;
                    case 67: 
                    case 'd':
                        etat = DEPLACEMENT_DROITE;    //on se déplace vers la droite
                        break;
                    case 68: 
                    case 'q':
                        etat = DEPLACEMENT_GAUCHE;  //on se déplacde vers la gauche
                        break;
                    default:
                        etat = ACQUISITION_CLAVIER;  //reprise du clavier avec les touches
                        break;
                }
                break;

            case DEPLACEMENT_GAUCHE:
                if (getPosPlayerY(getPlayerGame(game)) > 0) setPosPlayerY(getPlayerGame(game), getPosPlayerY(getPlayerGame(game)) - 1);
                etat = VERIFICATION_VICTOIRE;
                break;

            case DEPLACEMENT_DROITE:
                if (getPosPlayerY(getPlayerGame(game)) < COLUMN - 1) setPosPlayerY(getPlayerGame(game), getPosPlayerY(getPlayerGame(game)) + 1);
                etat = VERIFICATION_VICTOIRE;
                break;

            case DEPLACEMENT_HAUT:
                if (getPosPlayerX(getPlayerGame(game)) > 0) setPosPlayerX(getPlayerGame(game), getPosPlayerX(getPlayerGame(game)) - 1);
                etat = VERIFICATION_VICTOIRE;
                break;

            case DEPLACEMENT_BAS:
                if (getPosPlayerX(getPlayerGame(game)) < LINE - 1) setPosPlayerX(getPlayerGame(game), getPosPlayerX(getPlayerGame(game)) + 1);
                etat = VERIFICATION_VICTOIRE;
                break;

            case VERIFICATION_VICTOIRE:
                // if (getPosPlayerX(getPlayerGame(game)) == getPosTreasureX(getTreasureGame(game)) &&
                //     getPosPlayerY(getPlayerGame(game)) == getPosTreasureY(getTreasureGame(game))) {
                //     printf("\nTu as gagné, wp tu es tombé sur le trésor \n");
                //     fin = 1;
                //     etat = INIT_A;
                //     }
                // else if (getPosPlayerX(getPlayerGame(game)) == getPosTrapX(getTrapGame(game)) &&
                //     getPosPlayerY(getPlayerGame(game)) == getPosTrapY(getTrapGame(game))) {
                //     printf("\nTu es tombé sur un trap, tu perds une vie\n");
                //     vie  = vie - 1;
                //     if (vie == 0) {
                //         printf("\ntu n'as plus de vie !!! LOOOSER\n");
                //         fin = 1;
                //         etat = INIT_A;
                //     } else {
                //         printf("\nIl te reste %d vies.\n", vie);
                //         system("clear");
                //         setGridCellMap(getMapGame(game),
                //                getPosPlayerX(getPlayerGame(game)),
                //                getPosPlayerY(getPlayerGame(game)),
                //                'j');

                //         grille_print(getGridMap(getMapGame(game)), COLUMN, LINE);
                //         etat = ACQUISITION_CLAVIER;
                //     }
                // } else {
                //     system("clear");
                //     gamePrint(game);
                //     etat = ACQUISITION_CLAVIER;
                // }
                //system("clear");
                gamePrint(game);

                int status = checkGameStatus(game);
                
                if (status == 1) { //Win
                    // system("clear");
                    // gamePrint(game);
                    printf("\nTu as gagné, wp tu es tombé sur le trésor \n");
                    fin = 1;
                    etat = INIT_A;
                } else if (status == 2) { //Lose
                    fin = 1;
                    etat = INIT_A;
                } else { //Game continue
                    //printf("\nIl te reste %d vies.\n", getHealthPlayer(getPlayerGame(game)));
                    //setGridCellMap(getMapGame(game), getPosPlayerX(getPlayerGame(game)), getPosPlayerY(getPlayerGame(game)), 'j');
                    // system("clear");
                    // gamePrint(game);
                    etat = ACQUISITION_CLAVIER;
                }
                break;
            break;
        }
    }

    freeGame(game);
    return 0;
}


