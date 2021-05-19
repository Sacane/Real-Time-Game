/**
 * \file : gui.h
 * \authors : Johan RAMAROSON RAKOTOMIHAMINA - Christine LI
 * \date : 01-04-21
 * \last modification : 21-05-21
 * 
 * File containing the prototypes of the functions of the file gui.c
 *
 */

#ifndef __GUI__H__
#define __GUI__H__

#include <MLV/MLV_all.h>

#include "image.h"
#include "management.h"

/**
 * Function to initialize a board
 * \param level : Board, a game board
 * \param height : int, the height of the game board
 * \param font : MLV_Image *
 */
void init_Board(Board game_board, int height, MLV_Image *font);


/**
 * Function update a board 
 * \param level : Board, a game board
 * \param array_img[] : MLV_Image *
 * \param font : MLV_Image *
 * \param width : unsigned int, width of the game board
 * \param height : unsigned int, height of the game board
 */
void update_Board(Board game_board, MLV_Image *array_img[], MLV_Image *font, unsigned int width, unsigned int height);


/**
 * Function to draw a given object
 * \param object : Object, the object to draw
 */
void draw_Object(Object object);


/**
 * Function to draw a board by an image
 * \param game_board : Board, a game board
 * \param array_img[] : MLV_Image *, array of image
 * \param x_source : int
 * \param y_source : int
 * \param width : unsigned int, the width of the image
 * \param height : unsigned int, the height of the image
 */
void draw_img_by_board(Board game_board, MLV_Image *array_img[], int x_source, int y_source, unsigned int width, unsigned int height);


/**
 * Function that initializes the appearance of a launcher
 * \param level : Board, the game board
 * \param is_reached : bool*,
 */
void launch(Board gameboard, bool *is_reached);

/*void gui_launcher(Board gameboard, bool *is_reached);*/

/*-----------------------------------*/



#endif