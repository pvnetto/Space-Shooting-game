#ifndef SPACY_ENGINE
#define SPACY_ENGINE

#define PI 3.14159
#define WIDTH 800
#define HEIGHT 600
#define DEBUG false

#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <math.h>
#include <vector>
#include <cstdlib>
#include <cmath>

class Engine{
  public:
    static void initialize();
    static float get_angle(int, int, float, float);
};

#endif
