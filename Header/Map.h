//
// Created by matthieu on 26/03/25.
//

#ifndef MAP_H
#define MAP_H

typedef struct map_s Map;

extern Map* Map_new();
extern void Map_initialisation(Map* this);
extern void Map_free(Map* this);

#endif //MAP_H
