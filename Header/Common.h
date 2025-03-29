#ifndef COMMON_H
#define COMMON_H

#ifndef LINE
#define LINE 10
#endif

#ifndef COLUMN
#define COLUMN 10
#endif

#ifndef NBTRAP
#define NBTRAP 2
#endif

#ifndef HEALTHPLAYER
#define HEALTHPLAYER 2
#endif

#ifndef NBPLAYER
#define NBPLAYER 1
#endif

#ifndef NBPIRATE
#define NBPIRATE 1
#endif

#ifndef CHEAT
#define CHEAT 1
#endif

void generateUniqueCoordinates(int* x, int* y, int* usedX, int* usedY, int nbUsed);

#endif //COMMON_H
