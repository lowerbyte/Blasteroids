#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_image.h>
#include <stdio.h>
#include <math.h>

typedef struct{
  //same as in blast.h
  float sx;       
  float sy;
  float heading;
  float speed;
  int gone;
  ALLEGRO_COLOR color;
} Spaceship;

void draw_ship(Spaceship *s);
void move_ship_forward(Spaceship *s);
void rotate_ship_right(Spaceship *s);
void rotate_ship_left(Spaceship *s);
void init_ships(Spaceship *s[], int num);
