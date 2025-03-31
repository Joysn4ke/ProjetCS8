#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "assert.h"

#include "Common.h"

//void generateUniqueCoordinates(int* x, int* y, int* usedX, int* usedY, int nbUsed) {
// void generateUniqueCoordinates(int* x, int* y, int* usedX, int* usedY) {
    
//     int newX, newY;
//     int isUnique;

//     do {
//         //Generate new random coordinates
//         newX = rand() % (LINE);
//         newY = rand() % (COLUMN);

//         //Verify the unicity of the generates coordinates
//         isUnique = 1;
//         for (int i = 0; i < TOTAL_ENTITY ; i++) {
//             //Debug
//             //printf("usedX[i] %d\n", usedX[i]);
//             //printf("usedY[i] %d\n", usedY[i]);
//             if (newX == usedX[i] && newY == usedY[i]) {
//                 isUnique = 0;
//                 break;
//             }
//         }
//     } while (!isUnique);

//     //Change the value of the new coordinates
//     *x = newX;
//     *y = newY;
// }

void generateUniqueCoordinates(int* x, int* y, int* usedX, int* usedY, int usedCount) {
    int newX, newY;
    int isUnique;

    do {
        // Generate new random coordinates
        newX = rand() % (LINE);
        newY = rand() % (COLUMN);

        // Verify the uniqueness of the generated coordinates
        isUnique = 1;
        for (int i = 0; i < usedCount; i++) {
            if (newX == usedX[i] && newY == usedY[i]) {
                isUnique = 0;
                break;
            }
        }
    } while (!isUnique);

    // Change the value of the new coordinates
    *x = newX;
    *y = newY;
    
    // Store the new coordinates in the used arrays
    usedX[usedCount] = newX;
    usedY[usedCount] = newY;
}