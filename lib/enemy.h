#ifndef SPACY_ENEMY
#define SPACY_ENEMY

#include "engine.h"
#include "character.h"
#include <vector>


using namespace std;

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

#endif
