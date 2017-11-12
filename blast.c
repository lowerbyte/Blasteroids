#include "blast.h"

void draw_blast(Blast *blast){
  //if blast is still visible on the screen
  if(blast->gone != 1){
    //change the origin of the coordinates system
    ALLEGRO_TRANSFORM transform;
    al_identity_transform(&transform);
    al_rotate_transform(&transform, blast->heading * 3.14/180);
    al_translate_transform(&transform, blast->sx, blast->sy);
    al_use_transform(&transform);
    //draw shoot
    al_draw_filled_circle(0, 0, 2, blast->color);
  }
}

void update_blast(Blast *blast, int winWidth, int winHeight){
  //if blast is still visible on the screen
  if(blast->gone == 0){
    //calculate the new coordinates
    blast->sx += (blast->speed*sin(blast->heading * 3.14/180));
    blast->sy -= blast->speed*cos(blast->heading * 3.14/180);
    draw_blast(blast);
    //if blast is out of bounds (size screen), set the gone field
    if(blast->sx > winWidth || blast->sx < 0){
      blast->gone = 1;
    }
    if(blast->sy > winHeight || blast->sy < 0){
      blast->gone = 1;
    }
  }
}

