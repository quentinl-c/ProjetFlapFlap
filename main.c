#include <stdio.h>
#include <allegro5/allegro.h>
#include<allegro5/allegro_image.h>
#include<allegro5/allegro_native_dialog.h>
#include<allegro5/allegro_font.h>
#include<allegro5/allegro_ttf.h>
#include<math.h>
#include "obstacles.h"
const float FPS = 60;
const int SCREEN_W = 640;
const int SCREEN_H = 480;
const int BOUNCER_SIZE = 32;
enum MYKEYS
{
    KEY_SPACE, KEY_ESCAPE
};
int main(int argc, char **argv)
{
    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_EVENT_QUEUE *event_queue = NULL;
    ALLEGRO_TIMER *timer = NULL;
    ALLEGRO_BITMAP *bouncer = NULL;
    ALLEGRO_FONT *size_32 =al_load_font("Outwrite.ttf", 32, 2);
    float bouncer_x = 640;
    float bouncer_y = SCREEN_H / 2.0 - BOUNCER_SIZE / 2.0;
    float bouncer1_x = 640;
    bool first=true;
    bool key[4] = { false, false};
    bool redraw = true;
    bool up= false;
    bool doexit = false;
    bool gameOver = false;
    double bouncer_dy = 4.0;
    bool transfert=true;
    ALLEGRO_BITMAP *obstacle11 = NULL;
    ALLEGRO_BITMAP *obstacle12 = NULL;
    ALLEGRO_BITMAP *ground = NULL;
    ALLEGRO_BITMAP *mountains = NULL;
    ALLEGRO_BITMAP *obstacles[]= {obstacle11, obstacle12};
    int obsdata1[]={0,0,0};
    int obsdata2[]={0,0,0};
    bool firstpass=true;

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

    timer = al_create_timer(1.0 / FPS);
    if(!timer)
    {
        fprintf(stderr, "failed to create timer!\n");
        return -1;
    }

    display = al_create_display(SCREEN_W, SCREEN_H);
    if(!display)
    {
        fprintf(stderr, "failed to create display!\n");
        al_destroy_timer(timer);
        return -1;
    }
    if(generateObstacle(obstacles)==-1)
    {
        fprintf(stderr, "failed to create obstacles bitmap!\n");
        al_destroy_display(display);
        al_destroy_timer(timer);
        return -1;
    }
    ground = al_create_bitmap(640, 20);
    if(!ground){
        fprintf(stderr,"failed to create ground bitmap!\n");
        al_destroy_display;
        al_destroy_timer(timer);
        return -1;
    }
    al_set_target_bitmap(ground);
    ground = al_load_bitmap("ground.jpg");
    mountains = al_create_bitmap(640,255);
    if(!mountains){
        fprintf(stderr,"failed to create mountains bitmap!\n");
        al_destroy_display(display);
        al_destroy_timer(timer);
    }
    al_set_target_bitmap(mountains);
    mountains = al_load_bitmap("mountains.png");
    bouncer = al_create_bitmap(BOUNCER_SIZE, BOUNCER_SIZE);
    if(!bouncer)
    {
        fprintf(stderr, "failed to create bouncer bitmap!\n");
        al_destroy_display(display);
        al_destroy_timer(timer);
        return -1;
    }

    al_set_target_bitmap(bouncer);

    bouncer=al_load_bitmap("bird.png");

    al_set_target_bitmap(al_get_backbuffer(display));

    event_queue = al_create_event_queue();
    if(!event_queue)
    {
        fprintf(stderr, "failed to create event_queue!\n");
        al_destroy_bitmap(bouncer);
        al_destroy_display(display);
        al_destroy_timer(timer);
        return -1;
    }

    al_register_event_source(event_queue, al_get_display_event_source(display));

    al_register_event_source(event_queue, al_get_timer_event_source(timer));

    al_register_event_source(event_queue, al_get_keyboard_event_source());


    /*al_clear_to_color(al_map_rgb(0,0,0));*/
    ALLEGRO_BITMAP *image = al_load_bitmap("backgroung.jpg");
    al_draw_bitmap(image, 50, 100, NULL);

    al_flip_display();

    al_start_timer(timer);
    obsGenerator(obsdata1,obsdata2,firstpass,bouncer_x, bouncer1_x,100);
    firstpass=false;
    while(!doexit)
    {
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);

        if(ev.type == ALLEGRO_EVENT_TIMER)
        {
            obsGenerator(obsdata1,obsdata2,firstpass,bouncer_x,bouncer1_x,100);
            if(key[KEY_SPACE])
            {
                bouncer_y =bouncer_y-2*bouncer_dy;
            }
            if(bouncer_y<0 || bouncer_y>SCREEN_H - BOUNCER_SIZE)
            {
                bouncer_dy=-bouncer_dy;

            }/*if(bouncer_x>150 && bouncer_x<182 &&((bouncer_y>0 && bouncer_y<190)||(bouncer_y>290 && bouncer_y<480))){
                 doexit = true;
             }*/
            bouncer_y += bouncer_dy;
            bouncer_x -=  1.0;
            bouncer1_x -=1.0;

            redraw = true;
        }
        else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        {
            break;
        }
        else if(ev.type == ALLEGRO_EVENT_KEY_DOWN)
        {
            if(ev.keyboard.keycode == ALLEGRO_KEY_SPACE)
            {
                key[KEY_SPACE] = true;
            }
        }
        else if(ev.type == ALLEGRO_EVENT_KEY_UP)
        {
            switch(ev.keyboard.keycode)
            {
            case ALLEGRO_KEY_SPACE:
                key[KEY_SPACE] = false;
                break;

            case ALLEGRO_KEY_ESCAPE:
                doexit = true;
                break;
            }
        }

        if(redraw && al_is_event_queue_empty(event_queue))
        {
            redraw = false;

            al_draw_bitmap(image, 0, 0, NULL);
            al_draw_bitmap(mountains,bouncer_x-100,210, NULL);

            /*
            al_draw_bitmap(obstacles[0], bouncer_x, 0, NULL);
            al_draw_bitmap(obstacles[1], bouncer_x, 290, NULL);
            al_draw_bitmap(obstacles[2], bouncer_x+200, 0, NULL);
            al_draw_bitmap(obstacles[3], bouncer_x+200, 180, NULL);
            al_draw_bitmap(obstacles[4], bouncer_x+400, 0, NULL);
            al_draw_bitmap(obstacles[5], bouncer_x+400, 300, NULL);
            fprintf(stderr, "%f !\n",bouncer_x);
            if((bouncer_x)<40){
                    if(transfert){
                       bouncer1_x=640;
                       transfert=false;
                    }

                al_draw_bitmap(obstacles[0], bouncer1_x, 0, NULL);
            al_draw_bitmap(obstacles[1], bouncer1_x, 290, NULL);
            al_draw_bitmap(obstacles[2], bouncer1_x+200, 0, NULL);
            al_draw_bitmap(obstacles[3], bouncer1_x+200, 180, NULL);
            al_draw_bitmap(obstacles[4], bouncer1_x+400, 0, NULL);
            al_draw_bitmap(obstacles[5], bouncer1_x+400, 300, NULL);
            */

            if(drawObstacles(obstacles, &bouncer_x, &bouncer1_x, &first, &transfert, obsdata1,obsdata2)==-1)
            {
                fprintf(stderr,"Une erreur s'est produite!!\n");

            }
            al_draw_bitmap(ground,0,460,NULL);
        }


        if(!gameOver)
        {
            al_draw_bitmap(bouncer, 150, bouncer_y, 0);
        }
        else
        {
            al_draw_text(size_32, al_map_rgb(128, 50, 30), 150,50,0, "Gamer Over!");
        }

        al_flip_display();
    }



    al_destroy_bitmap(bouncer);
    al_destroy_bitmap(image);
    al_destroy_timer(timer);
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);

    return 0;
}



