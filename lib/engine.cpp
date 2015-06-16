#include "engine.h"


void Engine::initialize(){
  srand(time(NULL));
  al_init();
  al_install_keyboard();
  al_init_primitives_addon();
  al_install_mouse();
  al_init_image_addon();
}

float Engine::get_angle(int mouse_x, int mouse_y, float character_x, float character_y){
  float x, y;
  if (mouse_x > character_x && mouse_y < character_y){
    x = abs(mouse_x - character_x);
    y = abs(mouse_y - character_y);
    return atanf(x/y);
  }

  else if (mouse_x > character_x && mouse_y > character_y){
    x = abs(mouse_x - character_x);
    y = abs(mouse_y - character_y);
    return atanf(y/x) + (90*PI/180);
  }

  else if (mouse_x < character_x && mouse_y > character_y){
    x = abs(mouse_x - character_x);
    y = abs(mouse_y - character_y);
    return atanf(x/y) + (180*PI/180);
  }

  else if (mouse_x < character_x && mouse_y < character_y){
    x = abs(mouse_x - character_x);
    y = abs(mouse_y - character_y);
    return atanf(y/x) + (270*PI/180);
  }

  else if (mouse_x == character_x && mouse_y < character_y){
    return 0;
  }

  else if (mouse_y == character_y && mouse_x > character_x){
    return 90*3.14/180;
  }

  else if (mouse_x == character_x && mouse_y > character_y){
    return 180*3.14/180;
  }

  else if (mouse_y == character_y && mouse_x < character_x){
    return 270*3.14/180;
  }

}
