#include <stdlib.h>
#include <stdio.h>
#include <stdint.h> //uint8_t
#include "assert.h"


#include "Common.h"
#include "Map.h"

/**
 * @brief Represents the game map
 * 
 * The Map structure contains the grid representation of the game world
 * where all entities are positioned.
 */
struct Map_s{
    char **grid;
};


/**
 * @brief Creates a new Map object
 * 
 * Allocates memory for a new Map and its internal grid based on
 * LINE and COLUMN dimensions.
 * 
 * @return Pointer to the newly created Map
 */
extern Map* newMap() {
    Map* this = (Map*)calloc(1, sizeof(Map));
    assert(this != NULL);  //Memory allocation's verification

    this->grid = (char **)malloc(LINE * sizeof(char *));
    for (int i = 0; i < LINE; i++) {
        this->grid[i] = (char *)malloc(COLUMN * sizeof(char));
    }

    return this;
}


/**
 * @brief Initializes a Map object
 * 
 * Sets all cells in the map grid to empty spaces.
 * 
 * @param this Pointer to the Map to initialize
 */
extern void mapInitialisation(Map* this) {
    assert(this != NULL);  //Valid object's verification

    for(int i=0; i < LINE; i++)
    {
        for(int j=0; j < COLUMN; j++)
        {
            this->grid[i][j] = ' ';
        }
    }
}


/**
 * @brief Frees memory used by a Map object
 * 
 * Releases all resources associated with the given Map.
 * 
 * @param this Pointer to the Map to free
 */
extern void freeMap(Map* this) {
    if (this != NULL) {  //Check that the object is not NULL before freeing the memory
        for (int i = 0; i < LINE; i++) {
            free(this->grid[i]);
        }
        free(this->grid);

        free(this);
    }
}


/**
 * @brief Prints the game grid to the console
 * 
 * Displays the game map with cell borders and contents.
 * 
 * @param tab_grille The 2D grid to display
 * @param nb_colonne Number of columns in the grid
 * @param nb_ligne Number of rows in the grid
 */
extern void grille_print(char **tab_grille, uint8_t nb_colonne, uint8_t nb_ligne) {
    //Code ANSI minimal pour les couleurs
    const char *COULEUR_BORDURE = "\033[36m";  //Cyan pour les bordures
    const char *COULEUR_CONTENU = "\033[33m";  //Jaune pour le contenu
    const char *RESET_COULEUR = "\033[0m";     //Réinitialisation
    
    //Utilisation de caractères ASCII standard
    for(int j = 0; j < nb_ligne; j++) {
        //Ligne de délimitation supérieure
        printf("%s", COULEUR_BORDURE);
        for(int i = 0; i < nb_colonne; i++) {
            printf("+---");
        }
        printf("+%s\n", RESET_COULEUR);
        
        //Ligne de contenu
        printf("%s|%s ", COULEUR_BORDURE, RESET_COULEUR);
        for(int i = 0; i < nb_colonne; i++) {
            printf("%s%c%s ", COULEUR_CONTENU, tab_grille[j][i], RESET_COULEUR);
            printf("%s|%s ", COULEUR_BORDURE, RESET_COULEUR);
        }
        printf("\n");
    }
    
    //Ligne de délimitation inférieure
    printf("%s", COULEUR_BORDURE);
    for(int i = 0; i < nb_colonne; i++) {
        printf("+---");
    }
    printf("+%s\n", RESET_COULEUR);
}


//Getter & Setter
/**
 * @brief Gets the grid of a Map
 * 
 * @param map Pointer to the Map
 * @return 2D char array representing the grid
 */
extern char** getGridMap(Map* map) {
    assert(map != NULL);
    return map->grid;
}

/**
 * @brief Sets the value of a cell in the map grid
 * 
 * @param map Pointer to the Map
 * @param x X coordinate of the cell
 * @param y Y coordinate of the cell
 * @param value Character value to set
 */
extern void setGridCellMap(Map* map, int x, int y, char value) {
    // Debug
    // printf("X : %d\n", x);
    // printf("Y : %d\n", y);
    // printf("X : %c\n", value);

    assert(map != NULL);
    assert(x >= 0 && x < LINE);
    assert(y >= 0 && y < COLUMN);
    map->grid[x][y] = value;
}

/**
 * @brief Gets the value of a cell in the map grid
 * 
 * @param map Pointer to the Map
 * @param x X coordinate of the cell
 * @param y Y coordinate of the cell
 * @return Character at the specified position
 */
extern char getGridCellMap(Map* map, int x, int y) {
    assert(map != NULL);
    assert(x >= 0 && x < LINE);
    assert(y >= 0 && y < COLUMN);
    return map->grid[x][y];
}
