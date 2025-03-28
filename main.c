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


    grille_print(getGridMap(getMapGame(game)), COLUMN, LINE);

    
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

        setGridCellMap(getMapGame(game), 
               getPosPlayerX(getPlayerGame(game)),
               getPosPlayerY(getPlayerGame(game)),
               'j');
        system("clear");

        grille_print(getGridMap(getMapGame(game)), COLUMN, LINE);
    }
  
    freeGame(game);

    return 0;
}
