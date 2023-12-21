#include "graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define CYCLE 100000L
#define SEC 1000000L

typedef enum {
    DROITE, GAUCHE, HAUT, BAS
} Direction;

typedef struct {
    int x, y, sprites;
    Direction dir;
} Position;

typedef struct {
    int nbX, nbY, tailleCase;
    Position posLast;
} InfoJeux;

typedef struct {
    Position position[100];
    int longueur;
} Snake;

typedef struct {
    Position position[5];
    int nbPomme;
} Apple;

void genererNourriture(InfoJeux infos, Apple apple) {
    int i;
    for (i = 0; i < apple.nbPomme; i++){
        if (apple.position[i].x!=-1 && apple.position[i].y!=-1){
            apple.position[i].x = (rand() % infos.nbX) * infos.tailleCase;
            apple.position[i].y = (rand() % infos.nbY) * infos.tailleCase;
        }else{i--;}
    }
}

void initWindows(InfoJeux infos){
    ChoisirEcran(0);
    int taillePlateauX = infos.nbX*infos.tailleCase;
    int taillePlateauY = infos.nbY*infos.tailleCase;
    int tailleFenetreX = taillePlateauX+150;
    int tailleFenetreY = taillePlateauY;
    ChoisirCouleurDessin(CouleurParComposante(40, 40, 40));
    RemplirRectangle(0, 0, tailleFenetreX, tailleFenetreY);
    ChoisirCouleurDessin(CouleurParComposante(20, 255, 20));
    RemplirRectangle(0, 0, taillePlateauX, taillePlateauY);
}

void miseAjour(InfoJeux infos, Snake snake, Apple apple, Direction direction){
    
}

int gameStart(InfoJeux infos, Snake snake, Apple apple, Direction direction){
    unsigned long suivant, timer;
    suivant = Microsecondes()+CYCLE;
    timer = Microsecondes()+SEC;
    int score=0;
    int timerGame=0;
    while (1) {
        if (ToucheEnAttente()) {
            KeySym touche = Touche();
            switch (touche) {
                case XK_Right:
                    if (direction != GAUCHE) {
                        direction = DROITE;
                    }
                break;
                case XK_Left:
                    if (direction != DROITE) {
                        direction = GAUCHE;
                    }
                break;
                case XK_Up:
                    if (direction != BAS) {
                        direction = HAUT;
                    }
                break;
                case XK_Down:
                    if (direction != HAUT) {
                        direction = BAS;
                    }
                break;
                case XK_Escape:
                    return score;
                break;
            }
        }

        if (Microsecondes()>suivant){
            suivant= Microsecondes()+CYCLE;
        }

        if (Microsecondes()>timer){
            timer = Microsecondes()+SEC;
            int minute = timerGame/60;
            int seconde = timerGame%60;
            char timeT[10];
            char *numM;
            char *numS;
            asprintf(&numM, "%d", minute);
            asprintf(&numS, "%d", seconde);
            strcat(timeT, numM);
            strcat(timeT, ":");
            strcat(timeT, numS);
            timerGame++;
            printf("%s\n", timeT);
        }
    }

    return score;
}

int main(void) {
    InitialiserGraphique();
    InfoJeux infos;
    infos.nbX=60;
    infos.nbY=40;
    infos.tailleCase=20;
    int taillePlateauX = infos.nbX*infos.tailleCase;
    int taillePlateauY = infos.nbY*infos.tailleCase;
    int tailleFenetreX = taillePlateauX+150;
    int tailleFenetreY = taillePlateauY;
    CreerFenetre(10, 10, tailleFenetreX, tailleFenetreY);
    ChoisirTitreFenetre("Snake By Me");

    Direction direction;
    direction = GAUCHE;

    Snake snake;
    snake.longueur = 10;
    snake.position[0].x = taillePlateauX / 2;
    snake.position[0].y = taillePlateauY / 2;
    int i;
    for (i = 1; i < snake.longueur; i++){
        snake.position[i].x = snake.position[i-1].x + infos.tailleCase;
        snake.position[i].y = snake.position[0].y;
    }

    Apple apple;
    apple.nbPomme=5;
    for (i = 0; i < apple.nbPomme; i++){
        apple.position[i].x = -1;
        apple.position[i].y = -1;
    }
    genererNourriture(infos, apple);

    initWindows(infos);

    gameStart(infos, snake, apple, direction);

    return EXIT_SUCCESS;
}