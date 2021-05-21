/**
 * \file : gui.h
 * \authors : Johan RAMAROSON RAKOTOMIHAMINA - Christine LI
 * \date : 10-05-21
 * \last modification : 21-05-21
 * 
 * File containing the prototypes of the functions of the file image.c
 *
 */

#ifndef __IMAGE__H__
#define __IMAGE__H__

#include <MLV/MLV_all.h>
#include "wrapper.h"

#define SIZE_ARR_IMG 20 /* We can store max 20 img in the array of img, */
                        /* If you attend to add more than 20 images, you have to increment this value */

/* Enumeration to represent the differents images for the objects in the game */
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
 * Function to initialize an array of image according to its type
 * \param array_img[] : The array to initialize
 */
void init_array_img(MLV_Image *array_img[]);


/**
 * Resize all the images in the array of images
 * \param array_img[] : MLV_Image*
 * \param width : int, the width of the image
 * \param height : int, the height of the image
 */
void resize_all_img(MLV_Image* array_img[],  int width, int height);


/**
 * Function to free the memory space of an image array
 * \param array_img[] : MLV_Image *, array of image
 */
void free_array_img(MLV_Image *array[]);


#endif