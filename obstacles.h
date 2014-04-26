#ifndef OBSTACLES_H_INCLUDED
#define OBSTACLES_H_INCLUDED
int generateObstacle(ALLEGRO_BITMAP *obstacles[]);
int drawObstacles(ALLEGRO_BITMAP *obstacles1[], float *bouncer_x, float *bouncer1_x, bool *first, bool *transfert,int obsdata1[], int obsdata2[]);
int obsGenerator(int obsdata1[], int obsdata2[], bool first, float bouncerx1, float bouncerx2, int dec);
int rand_a_b(int a, int b);
bool verif(int obstacles[]);
bool verif(int obstacles[]);

#endif // OBSTACLES_H_INCLUDED
