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

/** This function allows the Game Loop to run
 *
 * none parameters
 *
 * return 0 when it runs correctly
 * return 1 when error occurs
 */

int run ()
{
    /*main variables declaration*/
    const float FPS = 60;
    const int SCREEN_W = 640;
    const int SCREEN_H = 480;
    const int BUGGLE_SIZE = 32;
    bool key_space = false;

    /*Allegro addons initialisation*/
    if(!al_init())
    {
        fprintf(stderr, "failed to initialize allegro!\n");
        return -1;
    }
    if(!al_init_image_addon())
    {
        fprintf(stderr, "failed to initialize allegro image addon!\n");
        return -1;
    }
    if(!al_install_keyboard())
    {
        fprintf(stderr, "failed to initialize the keyboard!\n");
        return -1;
    }
    al_init_font_addon();
    if(!al_init_ttf_addon())
    {
        fprintf(stderr, "failed to initialize the fonts!\n");
        return -1;
    }
    /** Allegro components declaration
     * Fonts
     * Bitmaps
     * Samples
     * Timer
     * Display
     */
    ALLEGRO_FONT *size_32 =al_load_font("font/Super_Mario_Bros.ttf", 32, 2);
    ALLEGRO_FONT *size_15 =al_load_font("font/Super_Mario_Bros.ttf", 15, 2);
    ALLEGRO_FONT *size_23 =al_load_font("font/Super_Mario_Bros.ttf", 23, 2);
    ALLEGRO_BITMAP *obstacle11 = NULL;
    ALLEGRO_BITMAP *obstacle12 = NULL;
    ALLEGRO_BITMAP *bonus = NULL;
    ALLEGRO_BITMAP *baggle = NULL;
    ALLEGRO_BITMAP *ground = NULL;
    ALLEGRO_BITMAP *mountains = NULL;
    ALLEGRO_SAMPLE *flapSample=NULL;
    ALLEGRO_SAMPLE *collisionSample=NULL;
    ALLEGRO_TIMER *timer = NULL;
    ALLEGRO_BITMAP *buggle = NULL;
    ALLEGRO_DISPLAY *display = NULL;
    /*Allegro components initialisation*/


    /*Audio components initialisation*/
    /*#############################################################*/
    if(!al_install_audio())
    {
        fprintf(stderr, "failed to initialize audio!\n");
        al_destroy_font(size_32);
        al_destroy_font(size_15);
        al_destroy_font(size_23);
        return -1;
    }

    if(!al_init_acodec_addon())
    {
        fprintf(stderr, "failed to initialize audio codecs!\n");
        al_destroy_font(size_32);
        al_destroy_font(size_15);
        al_destroy_font(size_23);
        return -1;
    }

    if (!al_reserve_samples(1))
    {
        fprintf(stderr, "failed to reserve samples!\n");
        al_destroy_font(size_32);
        al_destroy_font(size_15);
        al_destroy_font(size_23);
        return -1;
    }

    /*Samples loading*/
    collisionSample = al_load_sample("audio/birds001.wav");
    flapSample = al_load_sample("audio/suction.wav");

    /*Samples initialisation*/
    if (!collisionSample)
    {
        printf( "Audio clip sample not loaded!\n" );
        al_destroy_font(size_32);
        al_destroy_font(size_15);
        al_destroy_font(size_23);
        return -1;
    }

    if (!flapSample)
    {
        printf( "Audio clip sample not loaded!\n" );
        al_destroy_sample(collisionSample);
        al_destroy_font(size_32);
        al_destroy_font(size_15);
        al_destroy_font(size_23);
        return -1;
    }


    /*Display / Bitmaps / timer initialisation */
    /*#############################################################*/

    /*timer initialisation*/
    timer = al_create_timer(1.0 / FPS);
    if(!timer)
    {
        fprintf(stderr, "failed to create timer!\n");
        al_destroy_sample(collisionSample);
        al_destroy_sample(flapSample);
        al_destroy_font(size_32);
        al_destroy_font(size_15);
        al_destroy_font(size_23);
        return -1;
    }

    /*Display Initialisation*/
    display = al_create_display(SCREEN_W, SCREEN_H);
    if(!display)
    {
        fprintf(stderr, "failed to create display!\n");
        al_destroy_timer(timer);
        al_destroy_sample(collisionSample);
        al_destroy_sample(flapSample);
        al_destroy_font(size_32);
        al_destroy_font(size_15);
        al_destroy_font(size_23);
        return -1;
    }
    /** Main Bitmaps initialisation
     *Background bitmap:
     *                  *main background
     *                  *ground background
     *                  *Mountains background
     */

    /*ground bitmap loading*/
    ground = al_create_bitmap(640, 20);
    if(!ground)
    {
        fprintf(stderr,"failed to create ground bitmap!\n");
        al_destroy_timer(timer);
        al_destroy_display(display);
        al_destroy_sample(collisionSample);
        al_destroy_sample(flapSample);
        al_destroy_font(size_32);
        al_destroy_font(size_15);
        al_destroy_font(size_23);
        return -1;
    }
    al_set_target_bitmap(ground);
    ground = al_load_bitmap("img/ground.jpg");

    /*Mountains bitmap loading*/
    mountains = al_create_bitmap(640,255);
    if(!mountains)
    {
        fprintf(stderr,"failed to create mountains bitmap!\n");
        al_destroy_bitmap(ground);
        al_destroy_timer(timer);
        al_destroy_display(display);
        al_destroy_sample(collisionSample);
        al_destroy_sample(flapSample);
        al_destroy_font(size_32);
        al_destroy_font(size_15);
        al_destroy_font(size_23);
    }
    al_set_target_bitmap(mountains);
    mountains = al_load_bitmap("img/mountains.png");

    /*buggle bitmap loading*/
    buggle = al_create_bitmap(BUGGLE_SIZE, BUGGLE_SIZE);
    if(!buggle)
    {
        fprintf(stderr, "failed to create buggle bitmap!\n");
        al_destroy_bitmap(ground);
        al_destroy_timer(timer);
        al_destroy_display(display);
        al_destroy_sample(collisionSample);
        al_destroy_sample(flapSample);
        al_destroy_font(size_32);
        al_destroy_font(size_15);
        al_destroy_font(size_23);
        return -1;
    }
    al_set_target_bitmap(buggle);
    buggle=al_load_bitmap("img/bird.png");

    /*event queue initialisation*/
    ALLEGRO_EVENT_QUEUE *event_queue = NULL;
    event_queue = al_create_event_queue();
    if(!event_queue)
    {
        fprintf(stderr, "failed to create event_queue!\n");
        al_destroy_bitmap(buggle);
        al_destroy_bitmap(ground);
        al_destroy_timer(timer);
        al_destroy_display(display);
        al_destroy_sample(collisionSample);
        al_destroy_sample(flapSample);
        al_destroy_font(size_32);
        al_destroy_font(size_15);
        al_destroy_font(size_23);
        return -1;
    }
    al_set_target_bitmap(al_get_backbuffer(display));

    /*Main game loop*/
    /*#############################################################*/
    bool restart = false;
    do
    {
        char scoreMaxTxt[20] ="0";/*ScoreMax string displayed on the top right corner*/
        char scoreTxt[20] = "0";/*Score string displayed en the top left corner*/
        int scoreMax = getScoreMax();/*score max loaded from txt file*/
        float tramex1 = 640;/*first trame abscisse initialization*/
        float coordy = SCREEN_H / 2.0 - BUGGLE_SIZE / 2.0;/*buggle ordonate initialization*/
        float tramex2 = 640;/*second trame abscisse initialisation*/
        bool redraw = true;/*authorisation to redraw on display*/
        bool up= false;
        bool exit = false;/*authorization to shut down the programme*/
        bool gameOver = false;/*authorization to run "game over" mode*/
        double buggle_dy = 2.0;/*buggle moving distance*/
        bool pause = false;/*authorization to run the break mode*/
        bool gameOverShown = false;/*authorization to display "game over" message*/
        ALLEGRO_BITMAP *bonusBitmap[]= {bonus, baggle};/*bonus bitmap declaration*/
        ALLEGRO_BITMAP *obstaclesBtmp[]= {obstacle11, obstacle12};/*obstacles bitmap declaration*/
        bonusData gameBonus;/*bonus data structure declaration*/
        gameObstacles obstacles;/*obstacles data structure declaration*/
        int obsdata1[]= {0,0,0};/*obstacles abscisses initialization*/
        int obsdata2[]= {0,0,0};
        bool firstpass=true;/*first passing tram*/
        bool start = true;/*start the game authorization*/
        int bonusDuration=0;/*bonus effect counter*/


       /*obstacles bitmap loading*/
        if(generateBtmpObstacle(obstaclesBtmp)==-1)
        {
            fprintf(stderr, "failed to create obstacles bitmap!\n");
            al_destroy_display(display);
            al_destroy_timer(timer);
            return -1;
        }
        /*obstacles data structure initialization*/
        initObstacles(&obstacles, obstaclesBtmp);


        /*Bonus bitmap loading*/
        if(initBonusBitmap(bonusBitmap)==-1)
        {
            fprintf(stderr, "failed to create bonus bitmpa!\n");
            al_destroy_display(display);
            al_destroy_timer(timer);
        }
        /*Bonus data structure initialization*/
        initBonusData(&gameBonus, bonusBitmap);


        restart = false;

        /*display printing*/
        al_set_target_bitmap(al_get_backbuffer(display));


        /** event queue sources recording
         *  Allegro display
         *  Allegro timer (one tick per 1/60 sec)
         *  Allegor keyboard
         */
        al_register_event_source(event_queue, al_get_display_event_source(display));
        al_register_event_source(event_queue, al_get_timer_event_source(timer));
        al_register_event_source(event_queue, al_get_keyboard_event_source());

        /*Backgrounds bitmap loading*/
        ALLEGRO_BITMAP *image = al_load_bitmap("img/backgroung.jpg");
        ALLEGRO_BITMAP *startImage = al_load_bitmap("img/backgroundStart.jpg");

        /*start backround bitmap printing*/
        al_draw_bitmap(startImage, 0, 0, NULL);

        al_flip_display();

        al_start_timer(timer);/*start the timer*/


        /*first obstacles generation*/
        if(!gameOver)
        {
            obsGenerator(obstacles,tramex1, tramex2,100);
        }
        setFirst(&obstacles, false);
        /*Score initialisation*/
        int score=0;
        int nbTimerEvents = 0;

        /*Game loop beginning*/
        while(!exit)
        {


            ALLEGRO_EVENT ev;/*event declaration*/
            al_wait_for_event(event_queue, &ev);/*waiting new event*/


            if(ev.type == ALLEGRO_EVENT_TIMER)/*if the event is allegro timer (tick)*/
            {
                if(!start && !pause)
                {
                    if(!gameOver)
                    {
                        if(!start)
                        {
                            /*score upgrading*/
                            nbTimerEvents++;
                            if(nbTimerEvents>= 150)
                            {
                                score++;
                                bonusDuration--;
                                nbTimerEvents = 0;
                            }
                        }

                        if(key_space)/*if key space is pressed*/
                        {
                            coordy =coordy-2*buggle_dy;/*jump*/
                        }


                        coordy += buggle_dy;/*gravity generation*/

                        tramex1 -=  1.0;/*obstacles scrolling*/
                        tramex2 -=1.0;

                        redraw = true;/*allowed to print the new pattern*/

                    }
                }
            }
            else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            {
                break;
            }
            /*check wether a key is pressed*/
            /*#############################################################*/
            else if(ev.type == ALLEGRO_EVENT_KEY_DOWN)
            {
                if(ev.keyboard.keycode == ALLEGRO_KEY_SPACE)
                {
                    key_space = true;
                    al_play_sample(flapSample, 1.0, 0.0,2.0,ALLEGRO_PLAYMODE_ONCE,0);
                }
            }
            else if(ev.type == ALLEGRO_EVENT_KEY_UP)
            {
                if(!pause && !start)
                {
                    switch(ev.keyboard.keycode)
                    {
                    case ALLEGRO_KEY_SPACE:
                        key_space = false;
                        break;

                    case ALLEGRO_KEY_ESCAPE:
                        exit = true;
                        restart = false;
                        break;

                    case ALLEGRO_KEY_Y:
                        if(gameOverShown)/*accept to replay*/
                        {
                            exit = true;
                            restart = true;
                        }
                        break;

                    case ALLEGRO_KEY_N:
                        if(gameOverShown)/*quit the game*/
                        {
                            exit = true;
                            restart = false;
                        }
                        break;

                    case ALLEGRO_KEY_P:/*set break*/
                        pause = true;
                        break;

                    }
                }

                else if(pause)
                {
                    if(ev.keyboard.keycode == ALLEGRO_KEY_P)/*quit break*/
                    {
                        pause = false;
                    }
                }
                else if(start)/*start the game*/
                {
                    if(ev.keyboard.keycode == ALLEGRO_KEY_ENTER)
                    {
                        start= false;
                    }
                }
            }

            /*game actions*/
            if(!pause && ! start)
            {
                /*Print the new pattern*/
                /*#############################################################*/
                if(redraw && al_is_event_queue_empty(event_queue))
                {
                    redraw = false;
                    /*display the background fixed*/
                    al_draw_bitmap(image, 0, 0, 0);
                    /*display the moving background*/
                    al_draw_bitmap(mountains,tramex1-100,210, 0);

                    if(!gameOver)
                    {
                        /*generate new obstacles*/
                        obsGenerator(obstacles,tramex1,tramex2,100);
                        /*check the collision between the buggle and the obstacles*/
                        gameOver=collisionsObstacles(tramex1,tramex2,&coordy, BUGGLE_SIZE, obstacles.obsdata1,obstacles.obsdata2,gameBonus.colEnable);
                        /*check wether a bonus can be displayed*/
                        setGetBonus(&gameBonus, bonusGeneraor(score, gameBonus));
                        /*check the collision between the buggle and the bonus*/
                        setBonusTouched(&gameBonus, collisionBonus(tramex1, coordy, getBonusData(gameBonus,0),gameBonus.getBonus, BUGGLE_SIZE));
                        /*check wether a baggle can be displayed*/
                        setGetBaggle(&gameBonus, baggleGenerator(score, gameBonus));
                        /*check the collision between the buggle and the bagel*/
                        setBaggleTouched(&gameBonus, collisionBaggle(tramex2,coordy,getBonusData(gameBonus,1), gameBonus.getBaggle, BUGGLE_SIZE));
                        /*generate bonus effect*/
                        bonusEffect(score, &bonusDuration, &gameBonus);
                        /*generate bagel effect*/
                        baggleEffect(&score, gameBonus);
                        /*print obstacles*/
                        drawObstacles(&obstacles, &firstpass, &tramex1, &tramex2,gameBonus.colEnable);
                        /*print bonus*/
                        drawBonus(tramex1-100, gameBonus);
                        /*print bagel*/
                        drawBaggle(tramex2-100, gameBonus);

                        /*manage the speed obstacles scrolling*/
                        double k=0.0;
                        for(k=0.0; k<100.0; k++)
                        {
                            if(30*k <= score && score <= 30*(k+1))
                            {
                                tramex1 -= k;
                                tramex2 -= k;
                            }
                        }

                    }
                    /*print the ground bitmap*/
                    al_draw_bitmap(ground,0,460,0);
                }

                /*record the new best score*/
                if(score>scoreMax)
                {
                    scoreMax = score;
                }
                /*cat scores*/
                sprintf(scoreMaxTxt, "%d", scoreMax);
                sprintf(scoreTxt, "%d", score);
                /*display scores*/
                al_draw_text(size_15, al_map_rgb(128, 50, 30), 20,20,0, scoreTxt);
                al_draw_text(size_15, al_map_rgb(128, 50, 30), 600,20,0, scoreMaxTxt);

                /*print the buggle*/
                if(!gameOver)
                {
                    al_draw_bitmap(buggle, 150, coordy, 0);
                }
                else
                {
                    if(!gameOverShown)/*play the sample collision*/
                    {
                        al_play_sample(collisionSample, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);

                    }
                    /*print "game over" messages*/
                    al_draw_text(size_32, al_map_rgb(128, 50, 30), 200,100,0, "Game Over!");
                    al_draw_text(size_23, al_map_rgb(100, 4, 4), 30,200,0, "To exit the game press key N or Escap");
                    al_draw_text(size_23, al_map_rgb(100, 4, 4), 30,240,0, "To Restart the game press key Y");
                    gameOverShown = true;
                    /*record the maxscore*/
                    scoreMaxRecording(scoreMax);


                }
            }

            else if(pause&&!start)/*break mode*/
            {
                al_draw_text(size_32, al_map_rgb(128, 50, 30), 270,200,0, "Pause");
            }
            else if(start && !pause)/*start mode*/
            {
                al_draw_text(size_15, al_map_rgb(128, 50, 30), 170,150,0, "Appuyez sur la touche \"entree\"");
                al_draw_text(size_15, al_map_rgb(128, 50, 30), 150,200,0, "pour commencer une nouvelle partie");
            }
            al_flip_display();

        }
        /*end game*/
        destroyBonus(&gameBonus);
        destroyObstacles(&obstacles);
    }
    while(restart);
    /*end programme*/
    al_destroy_bitmap(buggle);
    al_destroy_timer(timer);
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
    al_destroy_sample(collisionSample);
    al_destroy_sample(flapSample);
    al_destroy_font(size_32);
    al_destroy_font(size_15);
    al_destroy_font(size_23);
    return 0;
}
