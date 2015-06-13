#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <math.h>
#include <vector>
#include <cstdlib>
#include <cmath>
#define WIDTH 800
#define HEIGHT 600
using namespace std;

const float pi = 3.14159;
const int maximum_enemies = 3;
int enemy_count = 0;


class Character{
	public:
		float pos_x;
		float pos_y;
		float vel_x;
		float vel_y;
	    float angle;
	    float accel;
	    float max_speed;
        float max_speed_neg;
	    int radius;
	    ALLEGRO_BITMAP *chrct;

	    Character();
	    
        void set_char_bitmap();
	    void set_character_speed(float, float);
	    void set_character_position();
	    void set_accel();
	    void draw_character();
};


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
    chrct = al_load_bitmap("img/player.png");
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
	al_draw_rotated_bitmap(chrct, radius, radius, pos_x, pos_y, angle, 0);
}


class Enemy{
	public:
		float enemy_pos_x;
		float enemy_pos_y;
		float enemy_vel_x;
		float enemy_vel_y;
		int radius;
		unsigned int id;
	    bool enemy_live;
	    Character *user;
	    ALLEGRO_BITMAP *vilain;

	    Enemy();
	    void set_enemy_bitmap();
	    void dead_enemy();
	    void follow_player(vector <Enemy> &);
	    void draw_enemy();
	    void spawn_enemy(int);

};

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

float get_angle(int mouse_x, int mouse_y, float character_x, float character_y){
      float x, y;
      if (mouse_x > character_x && mouse_y < character_y){
      x = abs(mouse_x - character_x);
      y = abs(mouse_y - character_y);
         return atanf(x/y);
      }
      
      else if (mouse_x > character_x && mouse_y > character_y){
      x = abs(mouse_x - character_x);
      y = abs(mouse_y - character_y);
         return atanf(y/x) + (90*pi/180);
      }
      
      else if (mouse_x < character_x && mouse_y > character_y){
      x = abs(mouse_x - character_x);
      y = abs(mouse_y - character_y);
         return atanf(x/y) + (180*pi/180);
      }
      
      else if (mouse_x < character_x && mouse_y < character_y){
      x = abs(mouse_x - character_x);
      y = abs(mouse_y - character_y);
         return atanf(y/x) + (270*pi/180);
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

class Bullets{
	public:
		float bullet_x;
		float bullet_y;
		float bullet_speed_x;
		float bullet_speed_y;
		float bullet_angle;
		int radius;
		bool bullet_live;
		ALLEGRO_BITMAP *shot;

		Bullets();
		void fire_bullet(int, int, float, float);
		bool bullet_trajectory(vector <Enemy> &);
		void draw_bullet();
};

Bullets::Bullets(){
	bullet_x = 0;
	bullet_y = 0;
	bullet_speed_x = 0;
	bullet_speed_y = 0;
	bullet_angle = 0;
	radius = 10;
	bullet_live = false;
	shot = al_load_bitmap("img/bullet.png");
}

void Bullets::fire_bullet(int mouse_x, int mouse_y, float player_x, float player_y){
		bullet_angle = get_angle(mouse_x, mouse_y, player_x, player_y) - (90 * pi / 180);
		bullet_speed_x = 10*cos(bullet_angle);
		bullet_speed_y = 10*sin(bullet_angle);
		bullet_x = player_x + bullet_speed_x;
		bullet_y = player_y + bullet_speed_y;
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
   
int main(int argc, char *argv[]) {
	float fps = 60;
	float tempo = 1.0f/fps;
	bool jogo_finalizou = false;

	al_init();
	int contador = 1;
	int random_enemy = 0;
	srand(time(NULL));

	//Inits
	
    al_install_keyboard();
    al_init_primitives_addon();
    al_install_mouse();
	al_init_image_addon();
    al_set_new_display_flags(ALLEGRO_FULLSCREEN);
	
    // Allegro variables
    
    ALLEGRO_DISPLAY *display = al_create_display(WIDTH, HEIGHT);
    ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
	ALLEGRO_TIMER *timer = al_create_timer(1 / fps);
	ALLEGRO_BITMAP *background = NULL;

	Character *player = new Character;
	vector <Bullets> MyBullets;
	vector <Enemy> MyEnemies;
    background = al_load_bitmap("img/scenario.png");

	
    //Registrando eventos
    
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_mouse_event_source());
    al_start_timer(timer);
	
	//Inicializando loop do jogo
	
    while(!jogo_finalizou) {
		// RECEBER EVENTOS DA FILA
		ALLEGRO_EVENT event;
		al_wait_for_event(event_queue, &event);


		if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
			cout << "KEYDOWN: " << event.keyboard.keycode << endl;
			switch (event.keyboard.keycode) {
				case ALLEGRO_KEY_ESCAPE:
					jogo_finalizou = true;
					break;
				case ALLEGRO_KEY_D:
					player->set_character_speed(2, 0);
					break;
				case ALLEGRO_KEY_A:
					player->set_character_speed(-2, 0);
					break;
				case ALLEGRO_KEY_W:
					player->set_character_speed(0, -2);
					break;
				case ALLEGRO_KEY_S:
					player->set_character_speed(0, 2);
					break;
			}
		}

		//Atira
		if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
			if (event.mouse.button & 1){
				Bullets *aux = new Bullets;
				aux->fire_bullet(event.mouse.x, event.mouse.y, player->pos_x, player->pos_y);
				MyBullets.push_back(*aux);
			}
		}
		
		//Detecta angulo da nave
		if (event.type == ALLEGRO_EVENT_MOUSE_AXES){
           player->angle = get_angle(event.mouse.x, event.mouse.y, player->pos_x, player->pos_y);
        }
        
        //Gera os inimigos
        if(random_enemy == 50 && enemy_count < maximum_enemies){
        	Enemy *aux = new Enemy;
        	aux->user = player;
        	aux->spawn_enemy(rand()%4);
        	MyEnemies.push_back(*aux);
        }

		if (event.type == ALLEGRO_EVENT_TIMER) {
			contador++;
			cout << "frame " << contador  << endl;

		    random_enemy = rand()% 51;
		    
		    for (unsigned int x = 0; x < MyEnemies.size(); x++){
		    	MyEnemies[x].id = x;
		    }
		    
			player->set_character_position();
			for (unsigned int a = 0; a < MyEnemies.size(); a++){
				MyEnemies[a].follow_player(MyEnemies);
			}
            
			for(unsigned int i = 0; i < MyBullets.size(); i++){
				MyBullets[i].bullet_trajectory(MyEnemies);
				
                if(MyBullets[i].bullet_trajectory(MyEnemies) == false){
                MyBullets.erase(MyBullets.begin() + i);
                }
			}       
			
			//Checa se colidiu com a parede
			if(player->pos_x > WIDTH || player->pos_x < 0){
               player->pos_x -= player->vel_x;
               player->vel_x = 0;     
            }
            
			if(player->pos_y > HEIGHT ||player->pos_y < 0){
               player->pos_y -= player->vel_y;
               player->vel_y = 0;     
            }
            
			
			al_draw_bitmap(background, 0, 0, 0);
            
            player->draw_character();
            
        	for (unsigned int a = 0; a < MyEnemies.size(); a++){
			MyEnemies[a].draw_enemy();
			}

            for (int j = 0; j < MyBullets.size(); j++){
            	MyBullets[j].draw_bullet();
            }

			al_flip_display();
 			al_clear_to_color(al_map_rgb(0,0,0));
		}
		
	}

	
	return 0;
}
