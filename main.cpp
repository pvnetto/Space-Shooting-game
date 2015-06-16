#include "lib/game.h"
using namespace std;

const int maximum_enemies = 3;
int enemy_count = 0;

int main(int argc, char *argv[]) {
  float fps = 60;
  float tempo = 1.0f/fps;
  bool jogo_finalizou = false;

  int contador = 1;
  int random_enemy = 0;

  Engine::initialize();

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
      Bullets *aux = new Bullets;
      aux->fire_bullet(event.mouse.x, event.mouse.y, player->pos_x, player->pos_y);
      MyBullets.push_back(*aux);
    }

    //Detecta angulo da nave
    if (event.type == ALLEGRO_EVENT_MOUSE_AXES){
      player->angle = Engine::get_angle(event.mouse.x, event.mouse.y, player->pos_x, player->pos_y);
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
      if(DEBUG){
        cout << "frame " << contador  << endl;
      }

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
