//
// Created by flobe on 04/05/2025.
//

#ifndef DEPLACEMENT_VAISSEAU_H
#define DEPLACEMENT_VAISSEAU_H

#endif //DEPLACEMENT_VAISSEAU_H

#include "vaisseau.h"
#include <allegro.h>

//structure du vaisseau du joueur 
typedef struct vaisseau {
    int x, y;           // Position du vaisseau
    int vitesse;        // Vitesse de déplacement
    int largeur, hauteur; // Dimensions du sprite (ou du rectangle de test)
    int vies;           // Nombre de vies restantes
    int invincible;     // 0 = non, 1 = temporairement invincible (option bonus)
    BITMAP* sprite;  // image du vaisseau qu'on changera selon le niveau)
} t_vaisseau;

//première fonction du bloc vaisseau qui initialise le vaisseau
void initialiserVaisseau(t_vaisseau* vaisseau, int niveau) {
    vaisseau->x = 100;
    vaisseau->y = 240;
    vaisseau->vitesse = 4;
    vaisseau->largeur = 32;
    vaisseau->hauteur = 32;
    vaisseau->vies = 3;
    vaisseau->invincible = 0;


    //on charge un sprite différent selon le niveau
    switch(niveau) {
        case 1:
            vaisseau->sprite = load_bitmap("vaisseau_niveau1.bmp", NULL); //soucoupe
        break;
        case 2:
            vaisseau->sprite = load_bitmap("vaisseau_niveau2.bmp", NULL); //avion
        break;
        case 3:
            vaisseau->sprite = load_bitmap("vaisseau_niveau3.bmp", NULL); //sous-marin
        break;
    }

    if (!vaisseau->sprite) {
        allegro_message("Erreur : impossible de charger l’image du vaisseau !");
        exit(EXIT_FAILURE);
    }
}

//deuxième fonction du bloc vaisseau : afficher le vaisseau à l'écran
void afficherVaisseau(t_vaisseau* vaisseau, BITMAP* buffer) {
    //si le sprite, c'est-à-dire l'image du vaisseau a bien été chargée
    if (vaisseau->sprite != NULL) {
        //alors on dessine l'image du vaisseau à sa position (x, y) sur le buffer
        draw_sprite(buffer, vaisseau->sprite, vaisseau->x, vaisseau->y);
    } else {
        //si jamais l'image n'est pas chargée,
        //on prévoie une solution de secours pour pouvoir quand même jouer
        //et on dessine un rectangle rouge à la place
        rectfill(buffer,
                 vaisseau->x,
                 vaisseau->y,
                 vaisseau->x + vaisseau->largeur,
                 vaisseau->y + vaisseau->hauteur,
                 makecol(255, 0, 0)); //code couleur pour le rouge
    }
}

//troixième fonction du bloc vaisseau : déplacement du vaisseau sur l'écran
//le vaisseau se déplace selon les touches "flèches" du clavier appuyées par le joueur (uniquement haut et bas)
//pour les limites de l'écran, on sait que largeur = 640 et longueur = 480
//on doit faire attention à ce que le vaisseau ne sorte pas de l'écran en vérifiant une condition sur x ou y
void deplacerVaisseau(t_vaisseau* vaisseau) {

    if (key[KEY_UP]) {//si la flèche du haut est appuyée, le vaisseau monte
        vaisseau->y -= vaisseau->vitesse;

        //si la nouvelle position est au-dessus de l'écran (y < 0), on la remet à 0
        //remettre à 0 veut dire que le vaisseau sera collé tout en haut de l'écran sur la bordure de l'écran
        //plus y est grand, plus on descend donc si y<0, le vaisseau est trop haut et sort de l'écran
        if (vaisseau->y < 0) {
            vaisseau->y = 0;
        }
    }

    if (key[KEY_DOWN]) {//si la flèche du bas est appuyée, le vaisseau descend
        vaisseau->y += vaisseau->vitesse; //on augmente la position y pour aller vers le bas

        //on vérifie bien que le vaisseau ne dépasse pas la limite de l'écran en bas (la bordure basse)
        //c'est-à-dire qu'on vérifie si sa position y + sa hauteur ne dépasse pas la hauteur de l'écran
        if (vaisseau->y + vaisseau->hauteur > SCREEN_H) {//si oui donc s'il sort
            vaisseau->y = SCREEN_H - vaisseau->hauteur;//on le repositionne pour qu'il soit collé à la bordure du bas de l'écran
        }
    }
}

//quatrième fonction du bloc vaisseau : vérifier les collisions du vaisseau avec un élément du décor
//pour cela, on utilise une image de collisions fournie par Amine (BITMAP* mapCollision)
//chaque pixel de cette image peut représenter un type de zone de collision (obstacle, vide, bonus...)
//ici on compare certains pixels autour du vaisseau avec la couleur d’un obstacle (qu'on va associer dans le main)
//cette couleur est passée en paramètre donc par exemple makecol(255,255,255) pour une météorité à laquelle on aura associé la couleur blanche

int verifierCollisionDecor(t_vaisseau* vaisseau, BITMAP* mapCollision, int couleurObstacle) {
    //on teste 4 points autour du vaisseau (haut, bas, gauche, droite)
    //pour voir s’il touche un pixel correspondant à la couleur d’un obstacle

    //point au milieu du bord supérieur du vaisseau
    int haut = getpixel(mapCollision, vaisseau->x + vaisseau->largeur / 2, vaisseau->y);

    //point au milieu du bord inférieur
    int bas = getpixel(mapCollision, vaisseau->x + vaisseau->largeur / 2, vaisseau->y + vaisseau->hauteur);

    //point au centre du bord gauche
    int gauche = getpixel(mapCollision, vaisseau->x, vaisseau->y + vaisseau->hauteur / 2);

    //point au centre du bord droit
    int droite = getpixel(mapCollision, vaisseau->x + vaisseau->largeur, vaisseau->y + vaisseau->hauteur / 2);

    //si un de ces points touche un pixel de couleur "obstacle", on va détecter une collision
    if (haut == couleurObstacle || bas == couleurObstacle ||
        gauche == couleurObstacle || droite == couleurObstacle) {
        return 1; //la collision est détectée
        }

    //sinon, tout va bien, il n'y a pas de collision et le vaisseau continue son chemin
    return 0;
}
