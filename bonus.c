#include <stdio.h>
#include<stdlib.h>
#include <allegro5/allegro.h>
#include<allegro5/allegro_image.h>
#include<allegro5/allegro_native_dialog.h>
#include<allegro5/allegro_font.h>
#include<allegro5/allegro_ttf.h>
#include<stdlib.h>

/**We define a structure bonusData
**/
typedef struct data_bonus
{
    int *bdata;
    /*managing collisions for bonuses*/
    bool colEnable;/*when true we enable the collisions (we actually take off all the obstacles for 10 s)*/
    bool getBonus;
    bool getBaggle;/*true when we get the "baggle" bonus*/
    bool bonusTouched;
    bool baggleTouched;
    ALLEGRO_BITMAP **bonusBitmap;
} bonusData;
/*gives the ith bonus*/
int getBonusData(bonusData gameBonus,int i)
{
    return *(gameBonus.bdata+i);
}
/*sets the ith bonus*/
void setBonusData(bonusData *gameBonus, int i, int val)
{
    *(gameBonus->bdata+i)= val;
}
/*gives the ith bitmap of the bonus*/
ALLEGRO_BITMAP *getBonusBitmap(bonusData gameBonus, int i)
{
    return *(gameBonus.bonusBitmap+i);
}
/*sets the ith bitmap of the bonus*/
void setBonusBitmap(bonusData *gameBonus, int i, ALLEGRO_BITMAP *bitmap)
{
    *(gameBonus->bonusBitmap+i)=bitmap;
}
/*sets the bonusTouched component of bonusData to val*/
void setBonusTouched(bonusData *gameBonus, bool val)
{
    (gameBonus->bonusTouched)=val;
}
/*sets getBonus to val*/
void setGetBonus(bonusData *gameBonus, bool val)
{
    (gameBonus->getBonus)=val;
}
/*sets baggleTouched to val*/
void setBaggleTouched(bonusData *gameBonus, bool val)
{
    (gameBonus->baggleTouched)=val;
}
/*sets getBaggle to val*/
void setGetBaggle(bonusData *gameBonus, bool val)
{
    (gameBonus->getBaggle)=val;
}

/** This function creates the bonusData structure*/
void initBonusData(bonusData *gameBonus, ALLEGRO_BITMAP *bitmap[])
{
    gameBonus->bdata=malloc(2*sizeof(int));
    setBonusData(gameBonus,0, 0);
    setBonusData(gameBonus,1, 0);
    gameBonus->colEnable=true;
    gameBonus->getBonus=false;
    gameBonus->getBaggle=false;
    gameBonus->baggleTouched=false;
    gameBonus->bonusTouched=false;
    gameBonus->bonusBitmap=malloc(2*sizeof(ALLEGRO_BITMAP*));
    setBonusBitmap(gameBonus, 0, bitmap[0]);
    setBonusBitmap(gameBonus, 1, bitmap[1]);
}

/** This function initializes the mystery bonus and the bagel bonus bitmap */
int initBonusBitmap(ALLEGRO_BITMAP * bitmap[])
{
    bitmap[0]= al_create_bitmap(40,40);
    if(!bitmap[0])
    {
        return -1;
    }
    bitmap[1]= al_create_bitmap(40,40);
    if(!bitmap[1])
    {
        return -1;
    }
    al_set_target_bitmap(bitmap[0]);
    bitmap[0] = al_load_bitmap("img/bonus.jpg");
    al_set_target_bitmap(bitmap[1]);
    bitmap[1] = al_load_bitmap("img/baggle.jpg");

    return 0;
}

/** This function generates bonuses
**/
bool bonusGeneraor(int score, bonusData gameBonus)
{
    if((score+1)%20==0 && !gameBonus.getBonus)
    {
        setBonusData(&gameBonus,0,randBonus(0,350));
        return true;
    }
    else if(gameBonus.getBonus && (score-11)%20==0)
    {
        return false;
    }
    else
    {
        return gameBonus.getBonus;
    }
}

/** This function generates bagels
**/
bool baggleGenerator(int score, bonusData gameBonus)
{
    if((score+1)%10 == 0 && ! gameBonus.getBaggle && gameBonus.colEnable && !gameBonus.getBaggle)
    {
        setBonusData(&gameBonus,1,randBonus(0,350));
        return true;
    }
    else if(gameBonus.getBaggle && (score+1)%17==0)
    {
        return false;
    }
    else if(gameBonus.baggleTouched)
    {
        return false;
    }
    else
    {
        return gameBonus.getBaggle;
    }
}

/** This function shows effects when touching the mystery bonus*/
void bonusEffect(int score,int *bonusDuration, bonusData *gameBonus)
{

    if(gameBonus->bonusTouched)
    {
        *bonusDuration = 10;
    }
    if(*bonusDuration>0)
    {
        gameBonus->getBonus=false;
        gameBonus->colEnable=false;
    }
    else
    {

        gameBonus->bonusTouched=false;
        gameBonus->colEnable=true;
    }
}

/** This function increments the score when touching a bagel*/
void baggleEffect(int *score, bonusData gameBonus)
{
    if(gameBonus.baggleTouched)
    {
        *score= *score+20;
    }
}
/** This function draws the mystery bonus
**/
void drawBonus(int bouncer_x, bonusData gameBonus)
{
    if(gameBonus.getBonus)
    {
        al_draw_bitmap(getBonusBitmap(gameBonus, 0), bouncer_x, getBonusData(gameBonus,0), 0);
    }
}
/** This function draws the bagel
**/
void drawBaggle(int bouncer_x, bonusData gameBonus)
{
    if(gameBonus.getBaggle)
    {
        al_draw_bitmap(getBonusBitmap(gameBonus, 1), bouncer_x, getBonusData(gameBonus,1), 0);
    }
}
/** This function solves floating point exception problems
**/
int randBonus(int a, int b)
{
    if(b-a ==0)
    {
        b+=1;
    }
    return rand()%(b-a) + a;
}
/**We free the memory we have allocated
**/
void destroyBonus(bonusData *gameBonus)
{
    free(gameBonus->bdata);
    al_destroy_bitmap(gameBonus->bonusBitmap[0]);
    al_destroy_bitmap(gameBonus->bonusBitmap[1]);
    free(gameBonus->bonusBitmap);

}
