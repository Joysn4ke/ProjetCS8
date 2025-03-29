#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "assert.h"

#include "Common.h"

void generateUniqueCoordinates(int* x, int* y, int* usedX, int* usedY, int nbUsed) {
    
    int newX, newY;
    int isUnique;
    do {
        //Generate new random coordinates
        newX = rand() % (LINE);
        newY = rand() % (COLUMN);

        //Verify the unicity of the generates coordinates
        isUnique = 0;
        for (int i = 0; i < nbUsed; i++) {
            if (newX == usedX[i] && newY == usedY[i]) {
                isUnique = 1;
                break;
            }
        }
    } while (isUnique);

    //Change the value of the new coordinates
    *x = newX;
    *y = newY;
}
