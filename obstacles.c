#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <math.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include "collisions.h"
#include "bonus.h"

/* We set a gameObstacles structure, it contains 2 bars downward and the other upward
represented here with pointers to arrays of integers and image of the obstacle and two Boolean first and transfer */

typedef struct game_obstacles
{
    int *obsdata1, *obsdata2;
    ALLEGRO_BITMAP **bitmapObs;
    bool first, tranfert;
} gameObstacles;

/*these two functions satisfy the ith component of obsdata1 and obsdata2 by a given obstacle with a value val given */
void setObsdata1(gameObstacles *obstacles, int i, int val)
{
    obstacles->obsdata1[i]=val;
}
void setObsdata2(gameObstacles *obstacles, int i, int val)
{
    obstacles->obsdata2[i]=val;
}
/*sets the ith bitmap */
void setObsBitmap(gameObstacles *obstacles, int i, ALLEGRO_BITMAP *val)
{
    *(obstacles->bitmapObs+i)=val;
}
/*sets first to val*/
void setFirst(gameObstacles *obstacles, bool val)
{
    obstacles->first=val;
}
/*gives the ith bitmap */
ALLEGRO_BITMAP *getObsBtmp(gameObstacles obstacles, int i)
{
    return *(obstacles.bitmapObs+i);
}
/*gives the ith obstacle*/
int getObsData1(gameObstacles obstacles, int i)
{
    return *(obstacles.obsdata1+i);
}
int getObsData2(gameObstacles obstacles, int i)
{
    return *(obstacles.obsdata2+i);
}

/** This function creates an obstacle
**/
void initObstacles(gameObstacles *obstacles, ALLEGRO_BITMAP *obsBtm[])
{
    obstacles->first=true;
    obstacles->tranfert=true;
    obstacles->bitmapObs=malloc(2*sizeof(ALLEGRO_BITMAP*));
    setObsBitmap(obstacles, 0, obsBtm[0]);
    setObsBitmap(obstacles, 1, obsBtm[1]);
    obstacles->obsdata1=malloc(3*sizeof(int));
    obstacles->obsdata2=malloc(3*sizeof(int));


}

/** This function checks that the obstacles created do not affect neither sky nor ground
**/
bool verif(int obstacles[])
{
    bool result = true;
    int i=0;
    for( i=0; i<3; i++)
    {
        if(obstacles[i]<-400 || obstacles[i]>-150)
        {
            result = false;
        }
    }
    return result;
}

/**This function initializes obstacle bitmaps
**/
int generateBtmpObstacle(ALLEGRO_BITMAP *obstacles[])
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
    obstacles[0]=al_load_bitmap("img/pipeTop.jpg");
    al_set_target_bitmap(obstacles[1]);
    obstacles[1]=al_load_bitmap("img/pipeBottom.jpg");
}
/** This function draws obstacles
**/
void drawObstacles(gameObstacles *obstacles, bool *firstpass, float *tramex1, float *tramex2, bool colEnable)
{
    if(colEnable)
    {
        if(*firstpass)
        {
            al_draw_bitmap(getObsBtmp(*obstacles, 0), *tramex1, getObsData1(*obstacles,0), 0);
            al_draw_bitmap(getObsBtmp(*obstacles, 1), *tramex1, getObsData1(*obstacles,0)+600, 0);
            al_draw_bitmap(getObsBtmp(*obstacles, 0), *tramex1+200, getObsData1(*obstacles,1), 0);
            al_draw_bitmap(getObsBtmp(*obstacles, 1), *tramex1+200, getObsData1(*obstacles,1)+600, 0);
            al_draw_bitmap(getObsBtmp(*obstacles, 0), *tramex1+400, getObsData1(*obstacles,2), 0);
            al_draw_bitmap(getObsBtmp(*obstacles, 1), *tramex1+400, getObsData1(*obstacles,2)+600, 0);
        }

        if( *tramex2<40)
        {
            if(!(obstacles->tranfert))
            {
                *tramex1=640;
                obstacles->tranfert=true;
            }
            al_draw_bitmap(getObsBtmp(*obstacles, 0), *tramex1, getObsData1(*obstacles,0), 0);
            al_draw_bitmap(getObsBtmp(*obstacles, 1), *tramex1, getObsData1(*obstacles,0)+600, 0);
            al_draw_bitmap(getObsBtmp(*obstacles, 0), *tramex1+200, getObsData1(*obstacles,1), 0);
            al_draw_bitmap(getObsBtmp(*obstacles, 1), *tramex1+200, getObsData1(*obstacles,1)+600, 0);
            al_draw_bitmap(getObsBtmp(*obstacles, 0), *tramex1+400, getObsData1(*obstacles,2), 0);
            al_draw_bitmap(getObsBtmp(*obstacles, 1), *tramex1+400, getObsData1(*obstacles,2)+600, 0);
            al_draw_bitmap(getObsBtmp(*obstacles, 0), *tramex2, getObsData2(*obstacles,0), 0);
            al_draw_bitmap(getObsBtmp(*obstacles, 1), *tramex2, getObsData2(*obstacles,0)+600, 0);
            al_draw_bitmap(getObsBtmp(*obstacles, 0), *tramex2+200, getObsData2(*obstacles,1), 0);
            al_draw_bitmap(getObsBtmp(*obstacles, 1), *tramex2+200, getObsData2(*obstacles,1)+600, 0);
            al_draw_bitmap(getObsBtmp(*obstacles, 0), *tramex2+400,getObsData2(*obstacles,2), 0);
            al_draw_bitmap(getObsBtmp(*obstacles, 1), *tramex2+400, getObsData2(*obstacles,2)+600, 0);
        }
        if( *tramex1<40)
        {
            if((obstacles->tranfert))
            {
                *tramex2=640;
                obstacles->tranfert=false;
            }
            *firstpass=false;
            al_draw_bitmap(getObsBtmp(*obstacles, 0), *tramex2, getObsData2(*obstacles,0), 0);
            al_draw_bitmap(getObsBtmp(*obstacles, 1), *tramex2, getObsData2(*obstacles,0)+600, 0);
            al_draw_bitmap(getObsBtmp(*obstacles, 0), *tramex2+200, getObsData2(*obstacles,1), 0);
            al_draw_bitmap(getObsBtmp(*obstacles, 1), *tramex2+200, getObsData2(*obstacles,1)+600, 0);
            al_draw_bitmap(getObsBtmp(*obstacles, 0), *tramex2+400, getObsData2(*obstacles,2), 0);
            al_draw_bitmap(getObsBtmp(*obstacles, 1), *tramex2+400, getObsData2(*obstacles,2)+600, 0);
            al_draw_bitmap(getObsBtmp(*obstacles, 0), *tramex1, getObsData1(*obstacles,0), 0);
            al_draw_bitmap(getObsBtmp(*obstacles, 1), *tramex1, getObsData1(*obstacles,0)+600, 0);
            al_draw_bitmap(getObsBtmp(*obstacles, 0), *tramex1+200, getObsData1(*obstacles,1), 0);
            al_draw_bitmap(getObsBtmp(*obstacles, 1), *tramex1+200, getObsData1(*obstacles,1)+600, 0);
            al_draw_bitmap(getObsBtmp(*obstacles, 0), *tramex1+400, getObsData1(*obstacles,2), 0);
            al_draw_bitmap(getObsBtmp(*obstacles, 1), *tramex1+400, getObsData1(*obstacles,2)+600, 0);
        }
    }

}
/** This function creates pseudo random generation of obstacles
**/
int obsGenerator(gameObstacles obstacles, float bugglex1, float bugglex2, int dec)
{
    if(obstacles.first && bugglex1>-520 && bugglex2>-520)
    {
        int borne[3];
        int i=0;
        for(i=0; i<3; i++)
        {
            borne[i]=randObs(-300, -200);
        }
        for(i=0; i<3; i++)
        {
            setObsdata1(&obstacles, i, borne[i]);
        }
        do
        {
            setObsdata2(&obstacles, 0, randObs(getObsData1(obstacles,2)-dec, getObsData1(obstacles,2)+dec));
            setObsdata2(&obstacles, 1, randObs(getObsData2(obstacles,0)-dec, getObsData2(obstacles,0)+dec));
            setObsdata2(&obstacles, 2, randObs(getObsData2(obstacles,1)-dec, getObsData2(obstacles,1)+dec));
        }
        while(!verif(obstacles.obsdata2));
    }
    else
    {
        if(bugglex1<=-520)
        {
            do
            {
                setObsdata1(&obstacles, 0, randObs(getObsData2(obstacles, 2)-dec, getObsData2(obstacles, 2)+dec));
                setObsdata1(&obstacles, 1, randObs(getObsData1(obstacles,0)-dec, getObsData1(obstacles,0)+dec));
                setObsdata1(&obstacles, 2, randObs(getObsData1(obstacles,1)-dec, getObsData1(obstacles,1)+dec));
            }
            while(!verif(obstacles.obsdata1));

        }
        if(bugglex2<=-520)
        {
            do
            {
                setObsdata2(&obstacles, 0, randObs(getObsData1(obstacles,2)-dec, getObsData1(obstacles,2)+dec));
                setObsdata2(&obstacles, 1, randObs(getObsData2(obstacles,0)-dec, getObsData2(obstacles,0)+dec));
                setObsdata2(&obstacles, 2, randObs(getObsData2(obstacles,1)-dec, getObsData2(obstacles,1)+dec));
            }
            while(!verif(obstacles.obsdata2));
        }
    }
    return 0;
}
/**This function allows us to generate a random integer value between two terminals
**/
int randObs(int a, int b)
{
    /*Normally solves the problems of floating point exception*/
    if(b-a ==0)
    {
        b+=1;
    }
    return rand()%(b-a) + a;
}
/*It frees the space allocated*/
void destroyObstacles(gameObstacles * obstacles){
    free(obstacles->obsdata1);
    free(obstacles->obsdata2);
    free(obstacles->bitmapObs);

}


