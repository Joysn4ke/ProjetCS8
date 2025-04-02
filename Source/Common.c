#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "assert.h"

#include "Common.h"

void generateUniqueCoordinates(int* x, int* y, int* usedX, int* usedY, int usedCount) {
    int newX, newY;
    int isUnique;

    do {
        //Generate new random coordinates
        newX = rand() % (LINE);
        newY = rand() % (COLUMN);

        //Verify the uniqueness of the generated coordinates
        isUnique = 1;
        for (int i = 0; i < usedCount; i++) {
            if (newX == usedX[i] && newY == usedY[i]) {
                isUnique = 0;
                break;
            }
        }
    } while (!isUnique); //!1 = 0

    //Change the value of the new coordinates
    *x = newX;
    *y = newY;
    
    //Store the new coordinates in the used arrays
    usedX[usedCount] = newX;
    usedY[usedCount] = newY;
}
