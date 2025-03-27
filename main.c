#include <stdlib.h>
#include <stdio.h>

#include "Game.h"
#include "Grille.h"
#include "Getch.h"
#include "Treasure.h"
#include "Map.h"
#include "Player.h"
#include "Common.h"

// #define COLONNE 10
// #define LIGNE 10

// const int LINE = 10;
// const int COLUMN = 10;

int main()
{
    char car;
    int fin = 0;

    // Map *mapTest = newMap();  //Test Leak Memmory
    // freeMap(mapTest);

    // Player *PlayerTest = newPlayer();  //Test Leak Memmory
    // freePlayer(PlayerTest);

    // Treasure *TreasureTest = newTreasure();  //Test Leak Memmory
    // freeTreasure(TreasureTest);

    // Game *GameTest = newGame();  //Test Leak Memmory
    // freeGame(GameTest);


    Game *game = newGame();
    gameInitialisation(game);

    grille_print(game->map->grid, COLUMN, LINE);

    while(!fin)
    {
        car = getch();
        game->map->grid[game->player->position_x][game->player->position_y] = ' ';
        switch(car)
        {
            case 'l':   //l = leave
                fin = 1;
                break;
            case 65:    //flèche du haut
            case 'z':   //haut
                if (game->player->position_x > 0) game->player->position_x--; 
                break;
            case 66:    //lèche du bas
            case 's':   //bas
                if (game->player->position_x < LINE - 1) game->player->position_x++; 
                break;
            case 67:    //flèche de droite
            case 'd':   //droite
                if (game->player->position_y < COLUMN - 1) game->player->position_y++; 
                break;
            case 68:    //flèche de gauche
            case 'q':   //gauche
                if (game->player->position_y > 0) game->player->position_y--; 
                break;
        }

        game->map->grid[game->player->position_x][game->player->position_y] = 'j';
        system("clear");
        grille_print(game->map->grid, COLUMN, LINE);

    }
  
    
    freeGame(game);

    return 0;
}
