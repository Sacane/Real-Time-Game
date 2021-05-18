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

#define SIZE_ARR_IMG 20 /* We can store max 20 img in the array of img, */
                        /* If you attend to add more than 20 images, you have to increment this value */

typedef enum {
    CHARACTER_SOUTH,
    CHARACTER_NORTH,
    CHARACTER_EAST,
    CHARACTER_WEST,
    PROJECTILE_SOUTH,
    PROJECTILE_NORTH,
    PROJECTILE_EAST,
    PROJECTILE_WEST,
    WALL_IMG,
    LAUNCHER_IMG,
    DEST,
    PLAYER2_NORTH_IMG,
    PLAYER2_SOUTH_IMG,
    PLAYER2_EAST_IMG,
    PLAYER2_WEST_IMG,
    SWITCH_IMG,
}typeImage;


/**
 * Function to initialize an array of image
 * @param array_img[] : MLV_Image *
 */
void init_array_img(MLV_Image *array_img[]);

/**
 * Function to free the memory space of an image array
 * @param array[] : MLV_Image *
 */
void free_array_img(MLV_Image *array[]);


/**
 * Function to initialize a board
 * @param level : Board, a game board
 * @param height : int, the height of the game board
 * @param font : MLV_Image *
 */
void init_plateau(Plateau niveau, int height, MLV_Image *font);


/**
 * Function update a board 
 * @param level : Board, a game board
 * @param array_img[] : MLV_Image *
 * @param font : MLV_Image *
 * @param width : unsigned int, width of the game board
 * @param height : unsigned int, height of the game board
 */
void update_plateau(Plateau niveau, MLV_Image *array_img[], MLV_Image *font, unsigned int width, unsigned int height);


/**
 * Function to draw a given object
 * @param object : Object, the object to draw
 */
void draw_Object(Objet objet);



/**
 * Function to resize an image
 * @param array_img[] : MLV_Image*
 * @param width : int, the width of the image
 * @param height : int, the height of the image
 */
void resize_all_img(MLV_Image* array_img[],  int width, int height);

/**
 * Function to retrieve the player's keyboard action
 * @param button : MLV_Keyboard_button
 * @param board : Board, the game board
 * @return int, the action given
 */
int action_listener(MLV_Keyboard_button button, Plateau board);

/**
 * DESCRIPTION
 * @param level : Board, the game board
 * @param is_reached : bool*,
 */
void launch(Plateau niveau, bool *is_reached);

/*void gui_launcher(Board gameboard, bool *is_reached);*/

/*-----------------------------------*/



#endif