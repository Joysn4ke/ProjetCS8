#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "assert.h"

#include "Common.h"

void generateUniqueCoordinates(int* x, int* y, int* usedX, int* usedY, int nbUsed) {
    
    int newX, newY;
    int isUnique;
    do {
        // Générer de nouvelles coordonnées
        newX = rand() % (LINE);
        newY = rand() % (COLUMN);
        
        // Vérifier l'unicité par rapport aux coordonnées déjà utilisées
        isUnique = 0;
        for (int i = 0; i < nbUsed; i++) {
            if (newX == usedX[i] && newY == usedY[i]) {
                isUnique = 1;
                break;
            }
        }
    } while (isUnique);

    // Retourner les coordonnées uniques
    *x = newX;
    *y = newY;
}

// void generateUniqueCoordinates(int* x, int* y, int playerX, int playerY, int* usedX, int* usedY, int nbUsed, int maxLine, int maxColumn) {
    
//     int newX, newY;
//     int isUnique;
//     do {
//         // Générer de nouvelles coordonnées
//         newX = rand() % (maxLine - 0 + 1) + 0;
//         newY = rand() % (maxColumn - 0 + 1) + 0;

//         // Vérifier l'unicité par rapport au joueur
//         if (newX == playerX && newY == playerY) {
//             continue;
//         } 
        
//         // Vérifier l'unicité par rapport aux coordonnées déjà utilisées
//         isUnique = 1;
//         for (int i = 0; i < nbUsed; i++) {
//             if (newX == usedX[i] && newY == usedY[i]) {
//                 isUnique = 0;
//                 break;
//             }
//         }
//     } while (!isUnique);

//     // Retourner les coordonnées uniques
//     *x = newX;
//     *y = newY;
// }
