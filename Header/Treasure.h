//
// Created by matthieu on 26/03/25.
//

#ifndef _TREASURE_H
#define _TREASURE_H

typedef struct Treasure_s Treasure;


Treasure* Treasure_new(int position_x, int position_y);
void Treasure_Initialisation(Treasure* this, int position_x, int position_y);
void Treasure_free(Treasure* this);

// ---------------
// Getter & Setter
// ---------------
void get_pos(Treasure* this);

#endif