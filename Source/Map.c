//
// Created by matthieu on 26/03/25.
//

#include <stdlib.h>
#include <stdio.h>
#include "assert.h"
#include "Map.h"
#include "Grille.h"

struct map_s{
    int position_x;
    int position_y;
    char **test_grille;
};

extern Map* Map_new(int position_x, int position_y) {
    Map* this = (Map*)calloc(1, sizeof(Map));
    assert(this != NULL);  // verif que l'allocation mémoire a réussi
    this->position_x = position_x;
    this->position_y = position_y;
    return this;
}


extern void Map_initialisation(Map* this) {
    assert(this != NULL);  // verif que l'objet est valide
}

extern void Map_free(Map* this) {
    if (this != NULL) {  // verif que l'objet n'est pas NULL avant de libérer la mémoire
        free(this);
    }
}




//c'est multi instance
//singleton (c'est intéressant si on a un seul trésor)

