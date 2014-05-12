#include <stdio.h>
#include <allegro5/allegro.h>
#include<allegro5/allegro_image.h>
#include<allegro5/allegro_native_dialog.h>
#include<allegro5/allegro_font.h>
#include<allegro5/allegro_ttf.h>
#include "obstacles.h"
#include "bonus.h"


/** This function enables the collision between the Buggle and the pipes
**/

bool collisionsObstacles(float tramex1, float tramex2, float *coordy, int BUGGLE_SIZE, int obsdata1[], int obsdata2[], bool colEnable)
{

/* if the parameter colEnable equals true,the collision is allowed  */
    if(colEnable)
    {

		/* if the buggle touches the ground ou the sky the function equals true and the player loses */
        if(*coordy<0 || *coordy> 440 - BUGGLE_SIZE)    /* the size of the ground is 40 pixels*/
        {
            return true;
        }


        else
        {
            int i=0;

            /* there are 6 different obstacles represented by obsdata1[i] andobsdata2(i]
				if the buggle touches one of the obstacles of tramex1 or tramex2, the function equals true and the player loses
            */
            for(i=0; i<3; i++)
            {
                float trame_temp=tramex1+i*200;
                if(trame_temp<=150 + BUGGLE_SIZE && trame_temp+40>=150 && ((*coordy<(480 + obsdata1[i])) || (*coordy+BUGGLE_SIZE>(480 + obsdata1[i] + 120))))
                {
                    return true;
                }


                trame_temp = tramex2+i*200;
                if((tramex1 <= 0 || tramex2 <= 0) && trame_temp<=150 + BUGGLE_SIZE && trame_temp+40>=150 &&(*coordy<(480 + obsdata2[i]) || *coordy+BUGGLE_SIZE>(480 + obsdata2[i] + 120)))
                {
                    return true;
                }

            }


        }
    }

    /* even if there are no pipes, the player loses if he touches the ground or the sky */
    else
    {
       if(*coordy<0 || *coordy> 440 - BUGGLE_SIZE)    /* le sol fait 40 pixels*/
        {
            return true;
        }


    }
    return false;
}


/** This function enables the collision between the buggle and the mystery bonus
* Parameters :
*		float trame1x
*		float coordy
*		int bData
*		bool getBonus
*		int BUGGLE_SIZE
**/
bool collisionBonus(float tramex1, float coordy, int bData,bool getBonus, int BUGGLE_SIZE)
{
	/* if getBonus equals true and if the buggle crashes into this bonus, the function equals true and the player loses */
    if(getBonus)
    {
        if(tramex1-100<=150 +BUGGLE_SIZE && tramex1-100+40>=150 &&((coordy>bData && coordy<bData+40)||(coordy+BUGGLE_SIZE<bData && coordy+BUGGLE_SIZE>bData+40)))
        {
            return true;
        }
    }
    return false;

}

/** This function enables the collision between the buggle and the bagel
* Parameters :
*		float trame1x
*		float coordy
*		int bData
*		bool getBaggle
*		int BUGGLE_SIZE
**/
bool collisionBaggle(float tramex1, float coordy, int bData,bool getBaggle, int BUGGLE_SIZE)
{
	/* if getBaggle equals true and if the buggle crashes into this bonus, the function equals true and the player loses */
    if(getBaggle)
    {
        if(tramex1-100<=150 +BUGGLE_SIZE && tramex1-100+40>=150 &&(coordy>bData && coordy<bData+40))
        {
            fprintf(stderr,"collisions baggle\n");
            return true;
        }
    }
    return false;

}
