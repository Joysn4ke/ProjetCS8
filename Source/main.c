#include <stdlib.h>

// #include "Header/grille.h"
// #include "Header/getch.h"

#include "../Header/Grille.h"
#include "../Header/Getch.h"

#define COLONNE 5
#define LIGNE 4

int main()
{
    char car ;
    int fin = 0;
    char **test_grille;
    int pos_joueur_x = 0;
    int pos_joueur_y = 0;

    //Allouer memoire pour le tableau
    test_grille = (char **)malloc(LIGNE * sizeof(char *));
    for (int i = 0; i < LIGNE; i++) {
        test_grille[i] = (char *)malloc(COLONNE * sizeof(char));
    }

    //Remplissage du tableau
    for(int i=0; i< LIGNE; i++)
    {
        for(int j=0; j<COLONNE; j++)
        {
            test_grille[i][j] = ' ';
        }
    }
    test_grille[pos_joueur_x][pos_joueur_y] = 'j';

    //Affichage du tableau
    grille_print(test_grille, COLONNE, LIGNE);

    while(!fin)
    {
        car = getch();
        test_grille[pos_joueur_x][pos_joueur_y] = ' ';
        switch(car)
        {
            case 'l': //l = leave
                fin = 1;
                break;
            case 'z': //haut
                pos_joueur_x--; 
                break;
            case 's': //bas
                pos_joueur_x++; 
                break;
            case 'q': //gauche
                pos_joueur_y--; 
                break;
            case 'd': //droite
                pos_joueur_y++; 
                break;
        }

        test_grille[pos_joueur_x][pos_joueur_y] = 'j';
        system("clear");
        grille_print(test_grille, COLONNE, LIGNE);

    }

  
    //Liberation de la memoire pour le tableau
    for (int i = 0; i < LIGNE; i++) {
        free(test_grille[i]);
    }
    free(test_grille);


    return 0;
}
