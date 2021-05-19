#include "../include/image.h"


void init_array_img(MLV_Image* array_img[]){
	
	array_img[PROJECTILE_EAST] = MLV_load_image("assets/projectiles/proj_east.png");
	array_img[PROJECTILE_NORTH] = MLV_load_image("assets/projectiles/proj_north.png");
	array_img[PROJECTILE_SOUTH] = MLV_load_image("assets/projectiles/proj_south.png");
	array_img[PROJECTILE_WEST] = MLV_load_image("assets/projectiles/proj_west.png");
	array_img[CHARACTER_EAST] = MLV_load_image("assets/character/character_east.png");
	array_img[CHARACTER_NORTH] = MLV_load_image("assets/character/character_north.png");
	array_img[CHARACTER_SOUTH] = MLV_load_image("assets/character/character_south.png");
	array_img[CHARACTER_WEST] = MLV_load_image("assets/character/character_west.png");
	array_img[WALL_IMG] = MLV_load_image("assets/Wall.png");
	array_img[LAUNCHER_IMG] = MLV_load_image("assets/launcher.png");
	array_img[DEST] = MLV_load_image("assets/dest.png");
	array_img[PLAYER2_NORTH_IMG] = MLV_load_image("assets/character/player2_north.png");
	if(!array_img[PLAYER2_NORTH_IMG]){
		fprintf(stderr,"null player_north\n");
		exit(EXIT_FAILURE);
	}
	array_img[PLAYER2_SOUTH_IMG] = MLV_load_image("assets/character/player2_south.png");
	if(!array_img[PLAYER2_SOUTH_IMG]){
		fprintf(stderr,"null player_south\n");
		exit(EXIT_FAILURE);
	}
	array_img[PLAYER2_EAST_IMG] = MLV_load_image("assets/character/player2_east.png");
	if(!array_img[PLAYER2_EAST_IMG]){
		fprintf(stderr,"null player_east\n");
		exit(EXIT_FAILURE);
	}
	array_img[PLAYER2_WEST_IMG] = MLV_load_image("assets/character/player2_west.png");
	if(!array_img[PLAYER2_WEST_IMG]){
		fprintf(stderr, "null player_west\n");
		exit(EXIT_FAILURE);
	}
	array_img[SWITCH_IMG] = MLV_load_image("assets/switch.png");
}

void resize_all_img(MLV_Image* array_img[],  int width, int height){
	int i;
	for(i = CHARACTER_SOUTH; i <= SWITCH_IMG; i++){
		MLV_resize_image(array_img[i], width, height);
	}
}

void free_array_img(MLV_Image *array[]){
	int i;
	for(i = CHARACTER_SOUTH; i <= SWITCH_IMG; i++){
		MLV_free_image(array[i]);
	}
}

