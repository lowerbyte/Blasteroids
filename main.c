#include <stdio.h>
#include <allegro5/allegro.h>
#include "collision.h"
#include <stdio.h>
#include <pthread.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <stdlib.h>

#define WIN_WIDTH 1024      //Window width
#define WIN_HEIGHT 768      //Window height
#define BULLETS_NUM 1000    //Number of bullets
#define ASTEROIDS_NUM 20    //Number of asteroids
#define SPACESHIP_NUM 3     //Number of ships

int main(int argc, char **argv){

  ALLEGRO_DISPLAY *display = NULL;

  //if initialization of allegro failed
  if(!al_init()) {
    fprintf(stderr, "failed to initialize allegro!\n");
    return -1;
  }

  display = al_create_display(WIN_WIDTH, WIN_HEIGHT);
  //is display created?
  if(!display) {
    fprintf(stderr, "failed to create display!\n");
    return -1;
  }

  al_clear_to_color(al_map_rgb(0,0,0)); //set black color on window

  al_init_primitives_addon(); //initialize primitives (lines, circles, etc)
  al_init_font_addon();       //initialize the font addon
  al_init_ttf_addon();        //initialize the ttf (True Type Font) addon
  char result[20];            //buffer for sprintf
  int points = 0;             //earned pointes

  Spaceship *s[SPACESHIP_NUM] = {NULL}; //table of pointers on Spaceship   
  Asteroid *a[ASTEROIDS_NUM] = {NULL};  //table of pointers on Asteroids
  Blast *b[BULLETS_NUM] = {NULL};       //table of pointers on Bullets
  int blast_num = 0;                    //auxiliary variable for blast counting
  int ship_num = 0;                     //auxiliary variable for spaceship counting

  init_ships(s, SPACESHIP_NUM);         //initialize Spaceships (spacechip.h)
  init_asteroids(a, ASTEROIDS_NUM);     //initialize Asteroids (asteroid.h)
  s[ship_num]->sx = 400;                //start coordinates of ship number 0
  s[ship_num]->sy = 400;                //start coordinates of ship number 0

  //load font GardenGnome-Regular.otf
  //feel free to use other one and place it in the working directory
  ALLEGRO_FONT *font = al_load_ttf_font("GardenGnome-Regular.otf",72,0);
  //was loading ok?
  if (!font){
    fprintf(stderr, "Could not load 'GardenGnome-Regular.otf'.\n");
    return -1;
  }    

  if(!al_install_keyboard()) exit(0);   //initialization of keyboard
  ALLEGRO_KEYBOARD_STATE keyState;
  ALLEGRO_TIMER *timer = al_create_timer(1.0/30);  //timer

  ALLEGRO_EVENT_QUEUE *queue;
  queue = al_create_event_queue();
  al_register_event_source(queue, al_get_keyboard_event_source());
  al_register_event_source(queue, al_get_timer_event_source(timer));

  al_start_timer(timer);
  bool end = false;  //auxiliary variable for ending the game earlier by pressing ESC
  while(true){

    //set temporary origin of the coordinates system in 0,0
    ALLEGRO_TRANSFORM transform;
    al_identity_transform(&transform);
    al_translate_transform(&transform, 0, 0);
    al_use_transform(&transform);
    sprintf(result, "%d", points); //changing int into string
    al_draw_text(font, al_map_rgb(255,255,255), 800, 30, ALLEGRO_ALIGN_CENTRE, result);
    
    if(end == true) break;
    ALLEGRO_EVENT event;
    al_wait_for_event(queue, &event);

    if(event.type == ALLEGRO_EVENT_KEY_DOWN){
      switch(event.keyboard.keycode){
        case ALLEGRO_KEY_SPACE:     
          //if SPACE is pressed make an instance of Blast
          //each time you press the SPACE another instance is created 
          //and memory is alocated. 
          b[blast_num] = (Blast*) malloc(sizeof(Blast));

          if(b[blast_num]){
            b[blast_num]->sx = s[ship_num]->sx;
            b[blast_num]->sy = s[ship_num]->sy;
            b[blast_num]->heading = s[ship_num]->heading;
            b[blast_num]->speed = 11;
            b[blast_num]->gone = 0;
            b[blast_num]->color = al_map_rgb(255,0,0);
          }
          else puts("Malloc did not succeed.");
          draw_blast(b[blast_num]);
          blast_num++; //blast_num is increase to get to another index in pointers table
          //as after every time when blast is out of the screen bounds it's
          //pointer in pointers table is change to NULL, so when we hit the
          //maximum size of bullets (1000) we're changing the blast_num to 0 (0
          //index in pointers table) and starting from the begging.
          //This simple mechanism gives us infinity amount of bullets with only
          //4000 bytes allocated.
          if(blast_num == BULLETS_NUM-1) blast_num = 0;

          break;
        case ALLEGRO_KEY_ESCAPE:
          end = true;
          break;
      }
    }
    else if(event.type == ALLEGRO_EVENT_TIMER){
      for(int i = 0 ;i < SPACESHIP_NUM; i++){
        //if pointer is not NULL
        if(s[i]){
          //if gone field is set free the allocated memory and set the pointer
          //to NULL
          if(s[i]->gone == 1){
            //if it is the last ship (life)
            if(ship_num == 2){
              ALLEGRO_TRANSFORM transform;
              al_identity_transform(&transform);
              al_translate_transform(&transform, 0, 0);
              al_use_transform(&transform);
              al_draw_text(font, al_map_rgb(255,255,255), WIN_WIDTH/2, WIN_HEIGHT/2, ALLEGRO_ALIGN_CENTRE, "GAME OVER");
              al_flip_display();
              sleep(5);
              free(s[i]);
              exit(0);
            }
            free(s[i]);
            s[i] = NULL;
            ship_num += 1;
            s[ship_num]->sx = 400;
            s[ship_num]->sy = 400;
          }
        }
      }
      for( int i =0 ;i < BULLETS_NUM; i++){
        //if pointer is not NULL
        if(b[i]){
          //check collidsion (collision.h)
          check_hit(b[i], a, ASTEROIDS_NUM, &points);
          //if gone is not set, update the position
          if(b[i]->gone != 1) update_blast(b[i], WIN_WIDTH, WIN_HEIGHT);
          else{ 
            free(b[i]);
            b[i] = NULL;
          }
        }
      }
      for( int i =0 ;i < ASTEROIDS_NUM; i++){
        //if pointer is not NULL        
        if(a[i]){
          //check collidsion (collision.h)          
          check_collision(s[ship_num], a[i]);
          //if gone is not set, update the position          
          if(a[i]->gone != 1) update_asteroid(a[i], WIN_WIDTH, WIN_HEIGHT);
          else{ 
            free(a[i]);
            a[i] = NULL;
          }
        }
      }
      //simple movings implemented in (spaceship.c)
      al_get_keyboard_state(&keyState);
      if(al_key_down(&keyState, ALLEGRO_KEY_UP)){
        move_ship_forward(s[ship_num]);
      }
      else if(al_key_down(&keyState, ALLEGRO_KEY_RIGHT)){
        rotate_ship_right(s[ship_num]);
      }
      else if(al_key_down(&keyState, ALLEGRO_KEY_LEFT)){
        rotate_ship_left(s[ship_num]);
      }
      else if(al_key_down(&keyState, ALLEGRO_KEY_LEFT)){
        rotate_ship_left(s[ship_num]);
      }
    }

    for(int i = 0; i< SPACESHIP_NUM; i++){
      if(s[i]) draw_ship(s[i]);
    }
    al_flip_display();
    al_clear_to_color(al_map_rgb(0,0,0));
  }

  //let's do some cleanup
  al_destroy_display(display);
  al_destroy_event_queue(queue);
  al_destroy_timer(timer);
  al_destroy_font(font);

  return 0;
}

