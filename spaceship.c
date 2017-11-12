#include"spaceship.h"

void draw_ship(Spaceship *s)
{
  //calculate the new coordinates  
  ALLEGRO_TRANSFORM transform;
  al_identity_transform(&transform);
  al_rotate_transform(&transform, s->heading * 3.14/180);
  al_translate_transform(&transform, s->sx, s->sy);
  al_use_transform(&transform);
  al_draw_line(-8, 9, 0, -11, s->color, 3.0f);
  al_draw_line(0, -11, 8, 9, s->color, 3.0f);
  al_draw_line(-6, 4, -1, 4, s->color, 3.0f);
  al_draw_line(6, 4, 1, 4, s->color, 3.0f);
}

void move_ship_forward(Spaceship *s){
  //calculate new coordinates
  s->sy += -((s->speed)*cos(s->heading * 3.14/180));
  s->sx += (s->speed)*sin(s->heading * 3.14/180);
}

void rotate_ship_right(Spaceship *s){
  s->heading = s->heading + 5;
}

void rotate_ship_left(Spaceship *s){
  s->heading = s->heading - 5;
}

void init_ships(Spaceship *s[], int num){
  int x = 30, y = 30;
  for(int i = 0; i < num; i++){
    s[i] = (Spaceship*) malloc(sizeof(Spaceship));
    if(s[i]){
      s[i]->sx = x;
      s[i]->sy = y;
      s[i]->heading = 0;
      s[i]->speed = 10;
      s[i]->gone = 0;
      s[i]->color = al_map_rgb(0,255,0);
    }
    else puts("Malloc did not succeed.");
    draw_ship(s[i]);
    x += 40;
  }
}
