#include <stdio.h>
#include<stdlib.h>
#include <allegro5/allegro.h>
#include<allegro5/allegro_image.h>
#include<allegro5/allegro_native_dialog.h>
#include<allegro5/allegro_font.h>
#include<allegro5/allegro_ttf.h>
#include<stdlib.h>
#include "obstacles.h"
int generateObstacle(ALLEGRO_BITMAP *obstacles[])
{

    obstacles[0] = al_create_bitmap(40,480);
    if(!obstacles[0])
    {
        return -1;
    }
    obstacles[1] = al_create_bitmap(40,480);
    if(!obstacles[1])
    {
        return -1;
    }



    al_set_target_bitmap(obstacles[0]);
    obstacles[0]=al_load_bitmap("pipeTop.jpg");

    /*al_clear_to_color(al_map_rgb(0, 255,0));*/

    al_set_target_bitmap(obstacles[1]);
    obstacles[1]=al_load_bitmap("pipeBottom.jpg");

    /*al_clear_to_color(al_map_rgb(0, 255,0));*/


}

int drawObstacles(ALLEGRO_BITMAP *obstacles1[], float *bouncer_x, float *bouncer1_x, bool *first, bool *transfert,int obsdata1[], int obsdata2[])
{

    if(*first)
    {
        al_draw_bitmap(obstacles1[0], *bouncer_x, obsdata1[0], NULL);
        al_draw_bitmap(obstacles1[1], *bouncer_x, obsdata1[0]+600, NULL);
        al_draw_bitmap(obstacles1[0], *bouncer_x+200, obsdata1[1], NULL);
        al_draw_bitmap(obstacles1[1], *bouncer_x+200, obsdata1[1]+600, NULL);
        al_draw_bitmap(obstacles1[0], *bouncer_x+400, obsdata1[2], NULL);
        al_draw_bitmap(obstacles1[1], *bouncer_x+400, obsdata1[2]+600, NULL);
    }




    if( *bouncer1_x<40)
    {
        if(!(*transfert))
        {
            *bouncer_x=640;
            *(transfert)=true;
        }

        al_draw_bitmap(obstacles1[0], *bouncer_x, obsdata1[0], NULL);
        al_draw_bitmap(obstacles1[1], *bouncer_x, obsdata1[0]+600, NULL);
        al_draw_bitmap(obstacles1[0], *bouncer_x+200, obsdata1[1], NULL);
        al_draw_bitmap(obstacles1[1], *bouncer_x+200, obsdata1[1]+600, NULL);
        al_draw_bitmap(obstacles1[0], *bouncer_x+400, obsdata1[2], NULL);
        al_draw_bitmap(obstacles1[1], *bouncer_x+400, obsdata1[2]+600, NULL);
        al_draw_bitmap(obstacles1[0], *bouncer1_x, obsdata2[0], NULL);
        al_draw_bitmap(obstacles1[1], *bouncer1_x,obsdata2[0]+600, NULL);
        al_draw_bitmap(obstacles1[0], *bouncer1_x+200, obsdata2[1], NULL);
        al_draw_bitmap(obstacles1[1], *bouncer1_x+200, obsdata2[1]+600, NULL);
        al_draw_bitmap(obstacles1[0], *bouncer1_x+400,obsdata2[2], NULL);
        al_draw_bitmap(obstacles1[1], *bouncer1_x+400, obsdata2[2]+600, NULL);
    }
    if( *bouncer_x<40)
    {
        if((*transfert))
        {
            *bouncer1_x=640;
            *(transfert)=false;
        }
        *first=false;
        al_draw_bitmap(obstacles1[0], *bouncer1_x, obsdata2[0], NULL);
        al_draw_bitmap(obstacles1[1], *bouncer1_x, obsdata2[0]+600, NULL);
        al_draw_bitmap(obstacles1[0], *bouncer1_x+200, obsdata2[1], NULL);
        al_draw_bitmap(obstacles1[1], *bouncer1_x+200, obsdata2[1]+600, NULL);
        al_draw_bitmap(obstacles1[0], *bouncer1_x+400, obsdata2[2], NULL);
        al_draw_bitmap(obstacles1[1], *bouncer1_x+400, obsdata2[2]+600, NULL);
        al_draw_bitmap(obstacles1[0], *bouncer_x, obsdata1[0], NULL);
        al_draw_bitmap(obstacles1[1], *bouncer_x, obsdata1[0]+600, NULL);
        al_draw_bitmap(obstacles1[0], *bouncer_x+200, obsdata1[1], NULL);
        al_draw_bitmap(obstacles1[1], *bouncer_x+200, obsdata1[1]+600, NULL);
        al_draw_bitmap(obstacles1[0], *bouncer_x+400, obsdata1[2], NULL);
        al_draw_bitmap(obstacles1[1], *bouncer_x+400, obsdata1[2]+600, NULL);
    }

    return 0;

}
int obsGenerator(int obsdata1[], int obsdata2[], bool first, float bouncerx1, float bouncerx2, int dec)
{
    if(first && bouncerx1>-520 && bouncerx2>-520)
    {
        int borne[3];
        int i=0;
        for(i=0; i<3; i++)
        {
            borne[i]=rand_a_b(-480, -72);
        }
        for(i=0; i<3; i++)
        {
            obsdata1[i]=borne[i];
        }
        do
        {
            obsdata2[0]=rand_a_b(obsdata1[2]-dec,obsdata1[2]+dec);
            obsdata2[1]=rand_a_b(obsdata2[0]-dec, obsdata2[0]+dec);
            obsdata2[2]=rand_a_b(obsdata2[1]-dec, obsdata2[1]+dec);
        }
        while(!verif(obsdata2));

    }
        else
{
    if(bouncerx1<=-520)
        {
            do
            {
                obsdata1[0]=rand_a_b(obsdata2[2]-dec, obsdata2[2]+dec);
                obsdata1[1]=rand_a_b(obsdata1[0]-dec, obsdata1[1]+dec);
                obsdata1[2]=rand_a_b(obsdata1[1]-dec, obsdata1[1]+dec);
            }
            while(!verif(obsdata1));

        }
        if(bouncerx2<=-520)
        {
            do
            {
                obsdata2[0]=rand_a_b(obsdata1[2]-dec, obsdata1[2]+dec);
                obsdata2[1]=rand_a_b(obsdata1[0]-dec, obsdata1[0]+dec);
                obsdata2[2]=rand_a_b(obsdata1[1]-dec, obsdata1[1]+dec);
            }
            while(!verif(obsdata2));

            }
    }


}
/*Cette fonction permet de générer une valeur entière alèatoire comprise entre deux bornes
Je n'ai pas fait moi même cette fonction....
*/
int rand_a_b(int a, int b)
{
    return rand()%(b-a) + a;
}

bool verif(int obstacles[])
{
    bool result = true;
    int i=0;
    for(i=0; i<3; i++)
    {
        if(obstacles[i]<-400 || obstacles[i]>-250)
        {
            result = false;
        }
    }
    return result;
}
