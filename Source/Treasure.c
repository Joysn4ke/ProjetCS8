//
// Created by matthieu on 26/03/25.
//

#include <stdlib.h>
#include <stdio.h>
#include "assert.h"
#include "Treasure.h"

struct treasure_s{
    int position_x;
    int position_y;
};

extern Treasure* Treasure_new(int position_x, int position_y) {
    Treasure* this = (Treasure*)calloc(1, sizeof(Treasure));
    assert(this != NULL);  // verif que l'allocation mémoire a réussi
    this->position_x = position_x;
    this->position_y = position_y;
    return this;
}


extern void Initialisation(Treasure* this, int position_x, int position_y) {
    assert(this != NULL);  // verif que l'objet est valide
    assert(position_x >= 0 && position_y >= 0);  // verif que les coordonnées sont valides

    this->position_x = position_x;
    this->position_y = position_y;
}


extern void get_pos(Treasure* this)
{
    assert(this != NULL);  // On vérifie que l'objet est valide
    printf("Position du trésor : (%d, %d)\n", this->position_x, this->position_y);
}

extern void Treasure_free(Treasure* this) {
    if (this != NULL) {  // verif que l'objet n'est pas NULL avant de libérer la mémoire
        free(this);
    }
}




//c'est multi instance
//singleton (c'est intéressant si on a un seul trésor)

