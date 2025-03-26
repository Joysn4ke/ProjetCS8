#include <stdlib.h>
#include <stdio.h>
#include "assert.h"
#include "Map.h"
#include "Grille.h"

struct Map_s{
    char **grid;
};


Map* newMap() {
    Map* this = (Map*)calloc(1, sizeof(Map));
    assert(this != NULL);  //Memory allocation's verification

    this->grid = (char **)malloc(LINE * sizeof(char *));
    for (int i = 0; i < LINE; i++) {
        this->grid[i] = (char *)malloc(COLUMN * sizeof(char));
    }

    return this;
}


void mapInitialisation(Map* this) {
    assert(this != NULL);  //Valid object's verification

    for(int i=0; i < LINE; i++)
    {
        for(int j=0; j < COLUMN; j++)
        {
            this->grid[i][j] = ' ';
        }
    }
}


void freeMap(Map* this) {
    if (this != NULL) {  //Check that the object is not NULL before freeing the memory
        for (int i = 0; i < LINE; i++) {
            free(this->grid[i]);
        }
        free(this->grid);

        free(this);
    }
}
