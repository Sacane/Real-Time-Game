#ifndef __GUI__H__
#define __GUI__H__

#include "management.h"

#include <MLV/MLV_all.h>

void load_image();

void free_image();

void init_plateau(Plateau niveau, int height);

void update_plateau(Plateau niveau);

void draw_Object(Objet objet);


#endif