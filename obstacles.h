#ifndef OBSTACLES_H_INCLUDED
#define OBSTACLES_H_INCLUDED
#include "bonus.h"
typedef struct game_obstacles
{
    int *obsdata1, *obsdata2;
    ALLEGRO_BITMAP **bitmapObs;
    bool first, tranfert;
} gameObstacles;
void setObsdata1(gameObstacles *obstacles, int i, int val);
void setObsdata2(gameObstacles *obstacles, int i, int val);
void setObsBitmap(gameObstacles *obstacles, int i, ALLEGRO_BITMAP *val);
void setFirst(gameObstacles *obstacles, bool val);
ALLEGRO_BITMAP *getObsBtmp(gameObstacles obstacles, int i);
int getObsData1(gameObstacles obstacles, int i);
int getObsData2(gameObstacles obstacles, int i);
void initObstacles(gameObstacles *obstacles, ALLEGRO_BITMAP *obsBtm[]);
int generateBtmpObstacle(ALLEGRO_BITMAP *obstacles[]);
void drawObstacles(gameObstacles *obstacles, bool *firstpass, float *tramx1, float *tramex2, bool colEnable);
int obsGenerator(gameObstacles obstacles, float bugglex1, float bugglex2, int dec);
int randObs(int a, int b);
bool verif(int obstacles[]);
void destroyObstacles(gameObstacles *obstacles);
#endif // OBSTACLES_H_INCLUDED

