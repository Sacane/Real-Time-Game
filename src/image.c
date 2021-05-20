/**
 * \file image.c
 * \authors Ramaroson Rakotomihamina Johan && Li Christine
 * \date : 01-04-21
 * \last modification : 21-05-21
 * 
 * Module used to manipulate and initialize the image used in the game
 *
 */

#include "../include/image.h"


/**
 * \fn void init_array_img(MLV_Image* array_img[])
 * \brief Function to initialize an array of image
 * \param array_img[] : MLV_Image *, array of image
 */
void init_array_img(MLV_Image* array_img[]){
	
	array_img[PROJECTILE_EAST] = MLV_load_image("assets/projectiles/proj_east.png");
    verif_malloc(array_img[PROJECTILE_EAST]);
	array_img[PROJECTILE_NORTH] = MLV_load_image("assets/projectiles/proj_north.png");
    verif_malloc(array_img[PROJECTILE_NORTH]);
	array_img[PROJECTILE_SOUTH] = MLV_load_image("assets/projectiles/proj_south.png");
    verif_malloc(array_img[PROJECTILE_SOUTH]);
	array_img[PROJECTILE_WEST] = MLV_load_image("assets/projectiles/proj_west.png");
    verif_malloc(array_img[PROJECTILE_WEST]);
	array_img[CHARACTER_EAST] = MLV_load_image("assets/character/character_east.png");
    verif_malloc(array_img[CHARACTER_EAST]);
	array_img[CHARACTER_NORTH] = MLV_load_image("assets/character/character_north.png");
    verif_malloc(array_img[CHARACTER_NORTH]);
	array_img[CHARACTER_SOUTH] = MLV_load_image("assets/character/character_south.png");
    verif_malloc(array_img[CHARACTER_SOUTH]);
	array_img[CHARACTER_WEST] = MLV_load_image("assets/character/character_west.png");
    verif_malloc(array_img[CHARACTER_WEST]);
	array_img[WALL_IMG] = MLV_load_image("assets/Wall.png");
    verif_malloc(array_img[WALL_IMG]);
	array_img[LAUNCHER_IMG] = MLV_load_image("assets/launcher.png");
    verif_malloc(array_img[LAUNCHER_IMG]);
	array_img[DEST] = MLV_load_image("assets/dest.png");
    verif_malloc(array_img[DEST]);
	array_img[PLAYER2_NORTH_IMG] = MLV_load_image("assets/character/player2_north.png");
    verif_malloc(array_img[PLAYER2_NORTH_IMG]);
	array_img[PLAYER2_SOUTH_IMG] = MLV_load_image("assets/character/player2_south.png");
    verif_malloc(array_img[PLAYER2_SOUTH_IMG]);
	array_img[PLAYER2_EAST_IMG] = MLV_load_image("assets/character/player2_east.png");
    verif_malloc(array_img[PLAYER2_EAST_IMG]);
	array_img[PLAYER2_WEST_IMG] = MLV_load_image("assets/character/player2_west.png");
    verif_malloc(array_img[PLAYER2_WEST_IMG]);
	array_img[SWITCH_IMG] = MLV_load_image("assets/switch.png");
    verif_malloc(array_img[SWITCH_IMG]);
}


/**
 * \fn void resize_all_img(MLV_Image* array_img[],  int width, int height)
 * \brief Function to resize an image
 * \param array_img[] : MLV_Image*
 * \param width : int, the width of the image
 * \param height : int, the height of the image
 */
void resize_all_img(MLV_Image* array_img[],  int width, int height){
	int i;
	for(i = CHARACTER_SOUTH; i <= SWITCH_IMG; i++){
		MLV_resize_image(array_img[i], width, height);
	}
}


/**
 * \fn void free_array_img(MLV_Image *array[])
 * \brief Function to free the memory space of an image array
 * \param array of the image to free 
 */
void free_array_img(MLV_Image *array[]){
	int i;
	for(i = CHARACTER_SOUTH; i <= SWITCH_IMG; i++){
		MLV_free_image(array[i]);
	}
}