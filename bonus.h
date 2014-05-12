#ifndef BONUS_H_INCLUDED
#define BONUS_H_INCLUDED
#include "collisions.h"
typedef struct data_bonus
{
    int *bdata;
    /*Gestion des collisions pour les bonus*/
    bool colEnable;
    bool getBonus;
    bool getBaggle;
    bool bonusTouched;
    bool baggleTouched;
    ALLEGRO_BITMAP **bonusBitmap;
} bonusData;

int initBonusBitmap(ALLEGRO_BITMAP * bitmap[]);
int getBonusData(bonusData gameBonus,int i);
void setBonusData(bonusData *gameBonus, int i, int val);
ALLEGRO_BITMAP *getBonusBitmap(bonusData gameBonus, int i);
void setBonusBitmap(bonusData *gameBonus, int i, ALLEGRO_BITMAP *bitmap);
void setBonusTouched(bonusData *gameBonus, bool val);
void setGetBonus(bonusData *gameBonus, bool val);
void setBaggleTouched(bonusData *gameBonus, bool val);
void setGetBaggle(bonusData *gameBonus, bool val);
void drawBonus(int bouncer_x, bonusData gameBonus);
void initBonusData(bonusData *gameBonus, ALLEGRO_BITMAP *bitmap[]);
bool bonusGeneraor(int score, bonusData gameBonus);
bool baggleGenerator(int score, bonusData gameBonus);
void baggleEffect(int *score, bonusData gameBonus);
void drawBaggle(int boucer_x, bonusData gameBonus);
void bonusEffect(int score, int *lastBonusTouched, bonusData *gameBonus);
void drawBonus(int bouncer_x, bonusData gameBonus);
void destroyBonus(bonusData *gameBonus);
int randBonus(int a, int b);
#endif // BONUS_H_INCLUDED
