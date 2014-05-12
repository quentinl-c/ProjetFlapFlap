/*
*Projet C: Flap Flap Buggle
*Auteurs: Lamya KEJJI, Lolita SALVESTRINI, Quentin LAPORTE-CHABASSE
*Projet développé dans le cadre du module de C
*Le code source est distribué sous la licence GNU GPL V2
*TELECOM Nancy année 2014
*/
#include <stdio.h>
#include <allegro5/allegro.h>
#include<allegro5/allegro_image.h>
#include<allegro5/allegro_native_dialog.h>
#include<allegro5/allegro_font.h>
#include<allegro5/allegro_ttf.h>
#include<math.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <time.h>
#include "collisions.h"
#include "obstacles.h"
#include "bonus.h"
#include "fichierScore.h"
#include "game.h"
int main(int argc, char **argv)
{
    run();
}

