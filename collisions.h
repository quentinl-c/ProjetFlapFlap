#ifndef COLLISIONS_H_INCLUDED
#define COLLISIONS_H_INCLUDED

#include "bonus.h"
bool collisionsObstacles(float tramx1, float tramex2, float *coordy, int BUGGLE_SIZE, int obsdata1[], int obsdata2[], bool colEnable);
bool collisionBonus(float tramx1, float coordy, int bData,bool getBonus, int BUGGLE_SIZE);
bool collisionBaggle(float tramx1, float coordy, int bData,bool getBaggle, int BUGGLE_SIZE);
#endif // COLLISIONS_H_INCLUDED
