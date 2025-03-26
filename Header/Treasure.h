//
// Created by matthieu on 26/03/25.
//

#ifndef _TREASURE_H
#define _TREASURE_H

typedef struct treasure_s Treasure;

extern Treasure* Counter_new();
extern void Counter_increment(Treasure* this, int a);
extern int Counter_query(Treasure* this);
extern void Counter_free(Treasure* this);

#endif