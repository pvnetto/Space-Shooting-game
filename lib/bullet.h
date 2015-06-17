#ifndef SPACY_BULLET
#define SPACY_BULLET

#include "engine.h"
#include "enemy.h"

using namespace std;

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
    ALLEGRO_SAMPLE *sound;
    Character *player;

    Bullets(Character *player);
    void fire_bullet(int, int, float, float);
    bool bullet_trajectory(vector <Enemy> &);
    void draw_bullet();
};

#endif
