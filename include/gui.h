/**
 * \fichier : gui.h
 * \auteurs : Johan RAMAROSON RAKOTOMIHAMINA - Christine LI
 * \date de création : 01-04-21
 * \dernière modification : 21-05-21
 * 
 * DESCRIPTION
 *
 */


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
    LAUNCHER,
    DEST,
    PLAYER2_NORTH_IMG,
    PLAYER2_SOUTH_IMG,
    PLAYER2_EAST_IMG,
    PLAYER2_WEST_IMG,
}typeImage;

void init_array_img(MLV_Image *array_img[]);

void free_array_img(MLV_Image *array[]);

void load_image();

void free_image();

void init_plateau(Plateau niveau, int height, MLV_Image *font);

void update_plateau(Plateau niveau, MLV_Image *array_img[], MLV_Image *font, unsigned int width, unsigned int height);

void draw_Object(Objet objet);

void resize_all_img(MLV_Image* array_img[],  int width, int height);

int action_listener(MLV_Keyboard_button button, Plateau board);

void launch_gui(Plateau niveau, bool *is_reached);

void launch_gui_bis(Plateau niveau, bool *is_reached);

void launch(Plateau niveau, bool *is_reached);

/*void gui_launcher(Board gameboard, bool *is_reached);*/

/*-----------------------------------*/



#endif