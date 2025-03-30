// #ifndef STATE_MACHINE_H
// #define STATE_MACHINE_H

// #include "Game.h"

// // Définition des états
// typedef enum {
//     S_INIT,
//     S_ACQUISITION_CLAVIER,
//     S_DEPLACEMENT,
//     S_VERIFICATION_VICTOIRE,
//     S_GAME_OVER,
//     S_DEATH,    // État de mort (non utilisé, pour la gestion d'erreur)
//     S_FORGET,   // État spécial pour ne pas changer d'état
//     STATE_NB    // Nombre total d'états
// } State;

// // Définition des événements
// typedef enum {
//     E_START,
//     E_KEY_UP,
//     E_KEY_DOWN,
//     E_KEY_LEFT,
//     E_KEY_RIGHT,
//     E_KEY_QUIT,
//     E_OTHER_KEY,
//     E_MOVE_DONE,
//     E_VICTORY,
//     E_DEFEAT,
//     E_CONTINUE,
//     EVENT_NB    // Nombre total d'événements
// } Event;

// // Définition des actions
// typedef enum {
//     A_NOP,              // Aucune action
//     A_INIT_GAME,        // Initialiser le jeu
//     A_MOVE_UP,          // Déplacer vers le haut
//     A_MOVE_DOWN,        // Déplacer vers le bas
//     A_MOVE_LEFT,        // Déplacer vers la gauche
//     A_MOVE_RIGHT,       // Déplacer vers la droite
//     A_PRINT_GAME,       // Afficher le jeu
//     A_CHECK_STATUS,     // Vérifier le statut du jeu
//     A_PRINT_VICTORY,    // Afficher le message de victoire
//     A_PRINT_DEFEAT,     // Afficher le message de défaite
//     A_FREE_GAME,        // Libérer les ressources du jeu
//     ACTION_NB           // Nombre total d'actions
// } Action;

// extern void StateMachine_init(Game* game);          //Initialisation de la machine à états
// extern void StateMachine_handleEvent(Event event);  //Exécution d'une transition en fonction de l'événement
// extern Event StateMachine_getEventFromKey(char key);// Fonction pour obtenir l'événement correspondant à une touche
// extern int StateMachine_isGameFinished();       //Fonction pour vérifier si le jeu est terminé
// extern State StateMachine_getCurrentState();    // Fonction pour récupérer l'état actuel

// #endif // STATE_MACHINE_H