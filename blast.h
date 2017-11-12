#include <allegro5/allegro_color.h>
#include "spaceship.h"

typedef struct{
  float sx;      //x position
  float sy;      //y position
  float heading; //move direction
  float speed;   //speed
  int gone;      //is it still valid? 0-yes, 1-no
  ALLEGRO_COLOR color;
} Blast;

void draw_blast(Blast *blast);
void update_blast(Blast *blast, int winWidth, int winHeight);
