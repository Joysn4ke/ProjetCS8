#include <stdlib.h>
#include <stdio.h>
#include <stdint.h> //uint8_t
#include "assert.h"


#include "Common.h"
#include "Map.h"
#include "Grille.h"

struct Map_s{
    char **grid;
};


extern Map* newMap() {
    Map* this = (Map*)calloc(1, sizeof(Map));
    assert(this != NULL);  //Memory allocation's verification

    this->grid = (char **)malloc(LINE * sizeof(char *));
    for (int i = 0; i < LINE; i++) {
        this->grid[i] = (char *)malloc(COLUMN * sizeof(char));
    }

    return this;
}


extern void mapInitialisation(Map* this) {
    assert(this != NULL);  //Valid object's verification

    for(int i=0; i < LINE; i++)
    {
        for(int j=0; j < COLUMN; j++)
        {
            this->grid[i][j] = ' ';
        }
    }
}


extern void freeMap(Map* this) {
    if (this != NULL) {  //Check that the object is not NULL before freeing the memory
        for (int i = 0; i < LINE; i++) {
            free(this->grid[i]);
        }
        free(this->grid);

        free(this);
    }
}


extern void grille_print (char **tab_grille, uint8_t nb_colonne, uint8_t nb_ligne) {
    for(int j= 0; j<nb_ligne; j++)
    {
        //ligne de delimitation
        for(int i=0; i<nb_colonne; i++)
        {
            printf("+---");
        }
        printf("+\n");
        //ligne de contenu
        for(int i=0; i<nb_colonne; i++)
        {
            printf("| ");
            printf("%c",tab_grille[j][i]); //contenu
            printf(" ");
        }
        printf("|\n");
    }
    //ligne de delimitation
    for(int i=0; i<nb_colonne; i++)
    {
        printf("+---");
    }
    printf("+\n");
}



// Getter & Setter
extern char** getGridMap(Map* map) {
    assert(map != NULL);
    return map->grid;
}

extern void setGridCellMap(Map* map, int x, int y, char value) {
    // Debug
    // printf("X : %d\n", x);
    // printf("Y : %d\n", y);
    // printf("X : %c\n", value);

    assert(map != NULL);
    assert(x >= 0 && x < LINE);
    assert(y >= 0 && y < COLUMN);
    map->grid[x][y] = value;
}

extern char getGridCellMap(Map* map, int x, int y) {
    assert(map != NULL);
    assert(x >= 0 && x < LINE);
    assert(y >= 0 && y < COLUMN);
    return map->grid[x][y];
}
