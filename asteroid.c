#include "asteroid.h"

void draw_asteroid(Asteroid *a){
  //calculate new coordinates  
  ALLEGRO_TRANSFORM transform;
  al_identity_transform(&transform);
  al_rotate_transform(&transform, a->heading * 3.14/180);
  al_translate_transform(&transform, a->sx, a->sy);
  al_use_transform(&transform);
  //draw asteroid
  al_draw_line(-20/a->scale, 20/a->scale, -25/a->scale, 5/a->scale, a->color, 2.0f);
  al_draw_line(-25/a->scale, 5/a->scale, -25/a->scale, -10/a->scale, a->color, 2.0f);
  al_draw_line(-25/a->scale, -10/a->scale, -5/a->scale, -10/a->scale, a->color, 2.0f);
  al_draw_line(-5/a->scale, -10/a->scale, -10/a->scale, -20/a->scale, a->color, 2.0f);
  al_draw_line(-10/a->scale, -20/a->scale, 5/a->scale, -20/a->scale, a->color, 2.0f);
  al_draw_line(5/a->scale, -20/a->scale, 20/a->scale, -10/a->scale, a->color, 2.0f);
  al_draw_line(20/a->scale, -10/a->scale, 20/a->scale, -5/a->scale, a->color, 2.0f);
  al_draw_line(20/a->scale, -5/a->scale, 0/a->scale, 0/a->scale, a->color, 2.0f);
  al_draw_line(0/a->scale, 0/a->scale, 20/a->scale, 10/a->scale, a->color, 2.0f);
  al_draw_line(20/a->scale, 10/a->scale, 10/a->scale, 20/a->scale, a->color, 2.0f);
  al_draw_line(10/a->scale, 20/a->scale, 0/a->scale, 15/a->scale, a->color, 2.0f);
  al_draw_line(0/a->scale, 15/a->scale, -20/a->scale, 20/a->scale, a->color, 2.0f);
}

void update_asteroid(Asteroid *a, int winWidth, int winHeight){
  if(a->gone == 0){
    a->sx += (a->speed*sin(a->heading * 3.14/180));
    a->sy -= a->speed*cos(a->heading * 3.14/180);
    draw_asteroid(a);
    if(a->sx > winWidth) a->sx = 0;
    else if(a->sx < 0) a->sx = winWidth;
    if(a->sy > winHeight) a->sy = 0;
    else if(a->sy < 0) a->sy = winHeight;
  }
}

void init_asteroids(Asteroid *a[], int m){
  srand(time(NULL));
  //wach asteroid has different random values
  for(int k = 0; k < m; k++){
    float sx = rand()%1024;
    float sy = rand()%768;
    float heading = rand()%360;
    float speed = rand()%6;
    float scale = rand()%2+1;
    a[k] = (Asteroid*) malloc(sizeof(Asteroid));
    if(a[k]){
      a[k]->sx = sy;
      a[k]->sy = sx;
      a[k]->heading = heading;
      //twist
      a[k]->speed = speed;
      //rot_velocity
      a[k]->scale = scale;
      a[k]->gone = 0;
      a[k]->color = al_map_rgb(0,0,255);
    }
    else puts("Malloc did not succeed.");
    draw_asteroid(a[k]);
  }
}
