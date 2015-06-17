#include "bullet.h"

Bullets::Bullets(Character *player){
  this->player = player;
  bullet_x = 0;
  bullet_y = 0;
  bullet_speed_x = 0;
  bullet_speed_y = 0;
  bullet_angle = 0;
  radius = 10;
  bullet_live = false;
  shot = al_load_bitmap("img/bullet.png");
  sound = al_load_sample("sounds/shoot_sound.wav");
}

void Bullets::fire_bullet(int mouse_x, int mouse_y, float player_x, float player_y){
  bullet_angle = Engine::get_angle(mouse_x, mouse_y, player_x, player_y) - (90 * PI / 180);
  bullet_speed_x = 10*cos(bullet_angle);
  bullet_speed_y = 10*sin(bullet_angle);
  bullet_x = player_x + bullet_speed_x;
  bullet_y = player_y + bullet_speed_y;
  al_play_sample(sound, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
  bullet_live = true;
}

bool Bullets::bullet_trajectory(vector <Enemy> &MyEnemies){
  bullet_x += bullet_speed_x;
  bullet_y += bullet_speed_y;

  if(bullet_x > WIDTH || bullet_x < 0 || bullet_y > HEIGHT || bullet_y < 0){
    bullet_live = false;
    return false;
  }

  for (unsigned int i = 0; i < MyEnemies.size(); i++){  
    float enemy_distance = sqrt(pow(bullet_x - MyEnemies[i].enemy_pos_x, 2)
        + pow(bullet_y - MyEnemies[i].enemy_pos_y, 2));
    if (enemy_distance < radius + MyEnemies[i].radius){
      bullet_live = false;
      MyEnemies[i].enemy_live = false;
      MyEnemies.erase(MyEnemies.begin() + i);
      player->score++;
      return false;
    }
  }
  return true;
}

void Bullets::draw_bullet(){
  if(bullet_live == true){
    al_draw_bitmap(shot, bullet_x, bullet_y, 0);
  }
}

