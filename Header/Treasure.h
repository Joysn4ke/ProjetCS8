//
// Created by matthieu on 26/03/25.
//

#ifndef _TREASURE_H
#define _TREASURE_H

typedef struct treasure_s Treasure;

extern Treasure* Treasure_new();
extern void Initialisation(Treasure* this, int position_x, int position_y);
extern void get_pos(Treasure* this);
extern void Treasure_free(Treasure* this);

#endif