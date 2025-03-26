#ifndef MAP_H
#define MAP_H

// #define LINE 10
// #define COLUMN 10

//typedef struct Map_s Map;

typedef struct Map_s {
    char **grid;
} Map;

Map* newMap();
void mapInitialisation(Map* this);
void freeMap(Map* this);

#endif //MAP_H
