/**
 * \file : gui.h
 * \authors : Johan RAMAROSON RAKOTOMIHAMINA - Christine LI
 * \date : 01-04-21
 * \last modification : 21-05-21
 * 
 * DESCRIPTION
 *
 */


#ifndef __GUI__H__
#define __GUI__H__

#include <MLV/MLV_all.h>

#include "image.h"
#include "management.h"

/**
 * Function to initialize a board
 * @param level : Board, a game board
 * @param height : int, the height of the game board
 * @param font : MLV_Image *
 */
void init_Board(Board niveau, int height, MLV_Image *font);


/**
 * Function update a board 
 * @param level : Board, a game board
 * @param array_img[] : MLV_Image *
 * @param font : MLV_Image *
 * @param width : unsigned int, width of the game board
 * @param height : unsigned int, height of the game board
 */
void update_Board(Board niveau, MLV_Image *array_img[], MLV_Image *font, unsigned int width, unsigned int height);


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

void draw_img_by_board(Board niveau, MLV_Image *array_img[], int x_source, int y_source, unsigned int width, unsigned int height);


/**
 * DESCRIPTION
 * @param level : Board, the game board
 * @param is_reached : bool*,
 */
void launch(Board gameboard, bool *is_reached);

/*void gui_launcher(Board gameboard, bool *is_reached);*/

/*-----------------------------------*/



#endif