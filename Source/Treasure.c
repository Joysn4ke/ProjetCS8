//
// Created by matthieu on 26/03/25.
//

#include <stdlib.h>
#include <stdio.h>
#include "assert.h"
#include "treasure.h"

struct treasure_s{
    int position_x;
    int position_y
};

extern Treasure* Treasure_new(int number)
{
    Ampoule* this;
    this = (Ampoule*)calloc(1, sizeof(Ampoule) );
    this->number = number;
    return this;
}

extern void Ampoule_allumer(Ampoule* this)
{
    printf("allumage ampoule %d\n",this->number);
}

extern void Ampoule_eteindre(Ampoule* this)
{
    printf("extinction ampoule %d\n",this->number);
}

extern void Ampoule_free(Ampoule* this)
{
    free(this);
}