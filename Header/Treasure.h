//
// Created by matthieu on 26/03/25.
//

#ifndef _TREASURE_H
#define _TREASURE_H

typedef struct treasure_s Treasure;

extern Treasure* Treasure_new();
extern void Treasure_increment(Treasure* this, int a);
extern int Treasure_query(Treasure* this);
extern void Treasure_free(Treasure* this);

#endif