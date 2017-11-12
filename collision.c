#include "collision.h"

//check hit which means check if blast hit the asteroid
void check_hit(Blast *b, Asteroid *a[], int ast_num, int *points){
  for(int k = 0; k < ast_num; k++){
    if(a[k]){
      //if scale is one, make the asteroid smaller
      if(a[k]->scale < 2){
        if(b->sx > a[k]->sx-20 
            && b->sx < a[k]->sx+20
            && b->sy < a[k]->sy+20
            && b->sy > a[k]->sy-20
          ){
          *points += 50;
          a[k]->scale += 1;
          b->gone = 1;
          break;
        }
      }
      //if asteroid is alredy smaller and gets hit, make set the gone field which makes it dissaper and free the memory
      else{ 
        if(b->sx > a[k]->sx-10 
            && b->sx < a[k]->sx+10
            && b->sy < a[k]->sy+10
            && b->sy > a[k]->sy-10
          ){
          *points += 100;
          a[k]->gone = 1;
          b->gone = 1;
          break;
        }
      }
    }
  }
}

//check collision between the spaceship and the asteroid
void check_collision(Spaceship *s, Asteroid *a){
  if(s){
    if(a->scale < 2){
      if(s->sx > a->sx-20 
          && s->sx < a->sx+20
          && s->sy < a->sy+20
          && s->sy > a->sy-20
        ){
        s->gone = 1;
      }
    }
    else{ 
      if(s->sx > a->sx-10
          && s->sx < a->sx+10
          && s->sy < a->sy+10
          && s->sy > a->sy-10
        ){
        s->gone = 1;
      }
    }
  }
}
