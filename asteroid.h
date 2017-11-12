#include <allegro5/allegro_color.h>
#include <allegro5/allegro_primitives.h>
#include <math.h>
#include <time.h>
#include <stdio.h>

typedef struct{
  //same as in blast.h with one additional field scale, which is responsible for scaling the asteroid
  float sx;
  float sy;
  float heading;
  float twist;
  float speed;
  float rot_velocity;
  float scale;
  int gone;
  ALLEGRO_COLOR color;
} Asteroid;

void draw_asteroid(Asteroid *a);
void update_asteroid(Asteroid *a, int winWidth, int winHeight);
void init_asteroids(Asteroid *a[], int m);
