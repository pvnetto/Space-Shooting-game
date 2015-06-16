#include "enemy.h"

Enemy::Enemy(){
  enemy_pos_x = 0;
  enemy_pos_y = 0;
  enemy_vel_x = 0;
  enemy_vel_y = 0;
  radius = 16;
  enemy_live = false;
  user = NULL;
  id = 0;
  vilain = al_load_bitmap("img/enemy.png");
}

void Enemy::spawn_enemy(int random_corner){
  if (random_corner == 0){
    enemy_pos_x = 1;
    enemy_pos_y = rand()%HEIGHT;
    enemy_live = true;
  }

  else if (random_corner == 1){
    enemy_pos_x = WIDTH - 1;
    enemy_pos_y = rand()%HEIGHT;
    enemy_live = true;
  }

  else if (random_corner == 2){
    enemy_pos_x = rand()%WIDTH;
    enemy_pos_y = 1;
    enemy_live = true;
  }

  else if (random_corner == 3){
    enemy_pos_x = rand()%WIDTH;
    enemy_pos_y = HEIGHT - 1;
    enemy_live = true;
  }
}

void Enemy::follow_player(vector <Enemy> &MyEnemies){
  if(enemy_pos_x < user->pos_x){
    enemy_vel_x = 3;
  }
  else if (enemy_pos_x > user->pos_x){
    enemy_vel_x = -3;
  }
  else if (enemy_pos_x == user->pos_x){
    enemy_vel_x = 0;
  }

  if(enemy_pos_y < user->pos_y){
    enemy_vel_y = 3;
  }
  else if (enemy_pos_y > user->pos_y){
    enemy_vel_y = -3;
  }
  else if (enemy_pos_y == user->pos_y){
    enemy_vel_y = 0;
  }


  enemy_pos_x += enemy_vel_x;
  enemy_pos_y += enemy_vel_y;

  float enemy_distance = sqrt(pow(user->pos_x - enemy_pos_x, 2)
      + pow(user->pos_y - enemy_pos_y, 2));

  if (enemy_distance < radius + user->radius){
    enemy_live = false;
    return;
  }

  //Checa se os inimigos colidem entre si, se colidirem, a posição volta a ser a anterior.
  for(int i = 0; i < MyEnemies.size(); i++){
    enemy_distance = sqrt(pow(enemy_pos_x - MyEnemies[i].enemy_pos_x, 2)
        + pow(enemy_pos_y - MyEnemies[i].enemy_pos_y, 2));

    if(enemy_distance < radius + MyEnemies[i].radius && id != MyEnemies[i].id){
      enemy_pos_x -= enemy_vel_x;
      enemy_pos_y -= enemy_vel_y;
      return;
    }
  }
}

void Enemy::draw_enemy(){
  if(enemy_live == true){
    al_draw_bitmap(vilain, enemy_pos_x, enemy_pos_y, 0);
  }
}
