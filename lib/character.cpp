#include "character.h"

Character::Character(){
  pos_x = 10;
  pos_y = 10;
  vel_x = 0;
  vel_y = 0;
  angle = 0;
  accel = 0;
  max_speed = 0.4;
  max_speed_neg = -0.4;
  radius = 16;
  sprite = al_load_bitmap("img/player.png");
  lives = 10;
  alive = true;
  score = 0;
}

void Character::set_character_speed(float x, float y){
  vel_x = x;
  vel_y = y;
  accel = 0;
}

void Character::set_character_position(){
  if (vel_x > 0 && accel < max_speed){
    vel_x += accel;
    accel += 0.01;
  }

  else if (vel_x < 0 && accel > max_speed_neg){
    vel_x += accel;
    accel -= 0.01;
  }

  if (vel_y > 0 && accel < max_speed){
    vel_y += accel;
    accel += 0.01;
  }

  else if (vel_y < 0 && accel > max_speed_neg){
    vel_y += accel;
    accel -= 0.01;
  }
  pos_x += vel_x;
  pos_y += vel_y;
}

void Character::draw_character(){
  al_draw_rotated_bitmap(sprite, radius, radius, pos_x, pos_y, angle, 0);
}

void Character::remove_life(){
  this->lives--;
  if(this->lives <= 0){
    this->alive = false;
  }
}
