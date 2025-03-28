#include <stdlib.h>
#include <stdio.h>

#include "Game.h"
#include "Grille.h"
#include "Getch.h"
#include "Treasure.h"
#include "Map.h"
#include "Player.h"
#include "Common.h"


int main()
{
    char car;
    int fin = 0;

    Game *game = newGame();
    gameInitialisation(game);

    //grille_print(getGridMap(getMapGame(game)), COLUMN, LINE);

    gamePrint(game);
    
    while(!fin)
    {
        car = getch();
        setGridCellMap(getMapGame(game), 
               getPosPlayerX(getPlayerGame(game)),
               getPosPlayerY(getPlayerGame(game)),
               ' ');
        switch(car)
        {
            case 'l':   //l = leave
                fin = 1;
                break;
            case 65:    //flèche du haut
            case 'z':   //haut
                if (getPosPlayerX(getPlayerGame(game)) > 0) setPosPlayerX(getPlayerGame(game), getPosPlayerX(getPlayerGame(game)) - 1);
                break;
            case 66:    //lèche du bas
            case 's':   //bas
                if (getPosPlayerX(getPlayerGame(game)) < LINE - 1) setPosPlayerX(getPlayerGame(game), getPosPlayerX(getPlayerGame(game)) + 1);
                break;
            case 67:    //flèche de droite
            case 'd':   //droite
                if (getPosPlayerY(getPlayerGame(game)) < COLUMN - 1) setPosPlayerY(getPlayerGame(game), getPosPlayerY(getPlayerGame(game)) + 1);
                break;
            case 68:    //flèche de gauche
            case 'q':   //gauche
                if (getPosPlayerY(getPlayerGame(game)) > 0) setPosPlayerY(getPlayerGame(game), getPosPlayerY(getPlayerGame(game)) - 1);
                break;
        }

        system("clear");

        // setGridCellMap(getMapGame(game), 
        // getPosPlayerX(getPlayerGame(game)),
        // getPosPlayerY(getPlayerGame(game)),
        // 'j');

        //grille_print(getGridMap(getMapGame(game)), COLUMN, LINE);
        gamePrint(game);

        // printf("treasure X : %d\n", getPosTreasureX(getTreasureGame(game)));printf("treasure Y : %d\n", getPosTreasureY(getTreasureGame(game)));

        // printf("player X : %d\n", getPosPlayerX(getPlayerGame(game)));printf("player Y : %d\n", getPosPlayerY(getPlayerGame(game)));
    }
  

    freeGame(game);
    return 0;
}
