#ifndef COMMON_H
#define COMMON_H

#ifndef LINE
#define LINE 10
#endif

#ifndef COLUMN
#define COLUMN 10
#endif

#ifndef NBTRAP
#define NBTRAP 3
#endif

#ifndef HEALTHPLAYER
#define HEALTHPLAYER NBTRAP
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
#define CHEAT 1
#endif

void generateUniqueCoordinates(int* x, int* y, int* usedX, int* usedY, int usedCount);

#endif //COMMON_H
