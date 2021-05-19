#ifndef __IMAGE__H__
#define __IMAGE__H__

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


#endif