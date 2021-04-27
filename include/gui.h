#ifndef __GUI__H__
#define __GUI__H__

#include "management.h"

#include <MLV/MLV_all.h>

typedef enum {
    CHARACTER_SOUTH,
    CHARACTER_NORTH,
    CHARACTER_EAST,
    CHARACTER_WEST,
    PROJECTILE_SOUTH,
    PROJECTILE_NORTH,
    PROJECTILE_EAST,
    PROJECTILE_WEST,
    WALL,
    LAUNCHER
}typeImage;



void init_array_img(MLV_Image *array_img[]);

void free_array_img(MLV_Image *array[]);

void load_image();

void free_image();

void init_plateau(Plateau niveau, int height);

void update_plateau(Plateau niveau);

void draw_Object(Objet objet);



#endif