#ifndef COMMON_H
#define COMMON_H

#ifndef LINE
#define LINE 10
#endif

#ifndef COLUMN
#define COLUMN LINE
#endif

#ifndef NBTRAP
#define NBTRAP (LINE - 1)
#endif

#ifndef HEALTHPLAYER
#define HEALTHPLAYER NBTRAP + 1
#endif

#ifndef NBPLAYER
#define NBPLAYER 1
#endif

#ifndef NBPIRATE
#define NBPIRATE 1
#endif

#ifndef TOTAL_ENTITY
#define TOTAL_ENTITY (NBTRAP + NBPLAYER + NBPIRATE)
#endif

#ifndef CHEAT
#define CHEAT 0
#endif

/**
 * @brief Generates unique coordinates for entity placement
 * 
 * This function generates random coordinates that haven't been used before
 * for placing entities on the game map.
 * 
 * @param[out] x Pointer to store the generated X coordinate
 * @param[out] y Pointer to store the generated Y coordinate
 * @param[in,out] usedX Array of X coordinates already in use
 * @param[in,out] usedY Array of Y coordinates already in use
 * @param[in] usedCount Number of coordinates already in use
 */
void generateUniqueCoordinates(int* x, int* y, int* usedX, int* usedY, int usedCount);

#endif //COMMON_H
