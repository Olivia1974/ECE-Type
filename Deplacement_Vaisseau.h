//
// Created by flobe on 04/05/2025.
//

#ifndef DEPLACEMENT_VAISSEAU_H
#define DEPLACEMENT_VAISSEAU_H

#endif //DEPLACEMENT_VAISSEAU_H

//structure du vaisseau du joueur 
typedef struct vaisseau {
    int x;              // Position horizontale
    int y;              // Position verticale
    int nb_vies;        // Nombre de vies restantes
    int vitesse;        // Vitesse de déplacement
    int niveau_actuel;  // Niveau atteint
} t_vaisseau;

// Déclaration du vaisseau joueur
t_vaisseau joueur;

//fonction pour initialiser le vaisseau du joueur
void initialiserVaisseau() {
    joueur.x = 100;             //position de départ en x
    joueur.y = 300;             //position de départ en y
    joueur.nb_vies = 3;         //le joueur commence avec 3 vies
    joueur.vitesse = 5;         //vitesse standard de déplacement
    joueur.niveau_actuel = 1;   //niveau 1 au début du jeu
}
