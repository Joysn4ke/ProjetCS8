#ifndef MAP_H
#define MAP_H

#include <stdint.h> // uint8_t

typedef struct Map_s Map;

extern Map* newMap();
extern void mapInitialisation(Map* this);
extern void freeMap(Map* this);

extern void grille_print (char **tab_grille, uint8_t nb_colonne, uint8_t nb_ligne);

// Getter & Setter
extern char** getGridMap(Map* map);
extern void setGridCellMap(Map* map, int x, int y, char value);
extern char getGridCellMap(Map* map, int x, int y);

#endif //MAP_H