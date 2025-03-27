#ifndef MAP_H
#define MAP_H

// #define LINE 10
// #define COLUMN 10

typedef struct Map_s Map;

// typedef struct Map_s {
//     char **grid;
// } Map;

Map* newMap();
void mapInitialisation(Map* this);
void freeMap(Map* this);

// Getter & Setter
char** getGridMap(Map* map);
void setGridCellMap(Map* map, int x, int y, char value);
char getGridCellMap(Map* map, int x, int y);

#endif //MAP_H
