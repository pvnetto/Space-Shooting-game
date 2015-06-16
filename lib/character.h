#ifndef SPACY_CHARACTER
#define SPACY_CHARACTER

#include "engine.h"

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
    int lives;
    bool alive;
    ALLEGRO_BITMAP *sprite;

    Character();

    void set_char_bitmap();
    void set_character_speed(float, float);
    void set_character_position();
    void set_accel();
    void draw_character();
    void remove_life();
};

#endif
