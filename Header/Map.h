#ifndef MAP_H
#define MAP_H

typedef struct Map_s Map;

extern Map* newMap();
extern void mapInitialisation(Map* this);
extern void freeMap(Map* this);

// Getter & Setter
extern char** getGridMap(Map* map);
extern void setGridCellMap(Map* map, int x, int y, char value);
extern char getGridCellMap(Map* map, int x, int y);

#endif //MAP_H
