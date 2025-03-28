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


void generateUniqueCoordinates(int* x, int* y, int playerX, int playerY, int* usedX, int* usedY, int nbUsed, int maxLine, int maxColumn);


#endif //COMMON_H
