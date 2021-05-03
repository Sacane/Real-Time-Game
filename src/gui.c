#include "../include/gui.h"


void init_array_img(MLV_Image* array_img[]){
	
	array_img[PROJECTILE_EAST] = MLV_load_image("assets/projectiles/proj_east.png");
	array_img[PROJECTILE_NORTH] = MLV_load_image("assets/projectiles/proj_north.png");
	array_img[PROJECTILE_SOUTH] = MLV_load_image("assets/projectiles/proj_south.png");
	array_img[PROJECTILE_WEST] = MLV_load_image("assets/projectiles/proj_west.png");
	array_img[CHARACTER_EAST] = MLV_load_image("assets/character/character_east.png");
	array_img[CHARACTER_NORTH] = MLV_load_image("assets/character/character_north.png");
	array_img[CHARACTER_SOUTH] = MLV_load_image("assets/character/character_south.png");
	array_img[CHARACTER_WEST] = MLV_load_image("assets/character/character_west.png");
	array_img[WALL] = MLV_load_image("assets/Wall.png");
	array_img[LAUNCHER] = MLV_load_image("assets/launcher.png");
	array_img[DEST] = MLV_load_image("assets/dest.png");
	
}

void resize_all_img(MLV_Image* array_img[],  int width, int height){
	int i;
	for(i = CHARACTER_SOUTH; i <= DEST; i++){
		MLV_resize_image(array_img[i], width, height);
	}
}

void free_array_img(MLV_Image *array[]){
	int i;
	for(i = CHARACTER_SOUTH; i <= DEST; i++){
		MLV_free_image(array[i]);
	}
}


static void init_vertical(int taillecase, int colonne, int lignes){
	int i, j;
	for(i = 0; i < colonne+1; i++){
		for(j = 0; j < lignes+1; j++){
			MLV_draw_line(i*taillecase, j*taillecase, i*taillecase, taillecase, MLV_COLOR_WHITE);
		}
	}
	MLV_actualise_window();
}

static void init_horizontal(int taillecase, int colonne, int ligne){
	int i, j;
	for(i = 0; i < ligne+1; i++){
		for(j = 0; j < colonne+1; j++){
			MLV_draw_line(j*taillecase, i*taillecase, taillecase, i*taillecase, MLV_COLOR_WHITE);
		}
	}
	MLV_actualise_window();
}

void init_plateau(Plateau niveau, int height, MLV_Image* font){
	MLV_draw_image(font, 0, 0);  
    init_vertical(height, niveau->taille.y, niveau->taille.x);
    init_horizontal(height, niveau->taille.y, niveau->taille.x);
    MLV_draw_line(0, 0, 0, height, MLV_COLOR_WHITE);
    MLV_draw_rectangle(0, 0, height * niveau->taille.y, height * niveau->taille.x, MLV_COLOR_WHITE);
    MLV_actualise_window();
}

void update_plateau(Plateau niveau, MLV_Image *array_img[], MLV_Image *font, unsigned int width, unsigned int height){

	unsigned int i, j;
	int x_height, y_height;
	Deplacement *depl = (Deplacement*)malloc(sizeof(Deplacement));
	MLV_draw_image(font, 0, 0);
	for(i = 0; i < niveau->taille.x; ++i){
		for(j = 0; j < niveau->taille.y; ++j){
			x_height = j * width;
			y_height = i * height;
			switch(niveau->objets[i][j].type){
				case VIDE: 
					break;
				case PROJECTILE:
					depl = niveau->objets[i][j].donnee_suppl;
					switch(depl->direction){
						case HAUT:
							MLV_draw_image(array_img[PROJECTILE_NORTH], x_height, y_height);
							break;
						case BAS:
							MLV_draw_image(array_img[PROJECTILE_SOUTH], x_height, y_height);
							break;
						case DROITE:
							MLV_draw_image(array_img[PROJECTILE_EAST], x_height, y_height);
							break;
						case GAUCHE:
							MLV_draw_image(array_img[PROJECTILE_WEST], x_height, y_height);
							break;
					}
					break;
				case LANCEUR:
					MLV_draw_image(array_img[LAUNCHER], x_height, y_height);
					break;
				case PERSONNAGE:
					switch(niveau->dir_perso){
						case HAUT:
							MLV_draw_image(array_img[CHARACTER_NORTH], x_height, y_height);
							break;
						case BAS:
							MLV_draw_image(array_img[CHARACTER_SOUTH], x_height, y_height);
							break;
						case DROITE:
							MLV_draw_image(array_img[CHARACTER_EAST], x_height, y_height);
							break;
						case GAUCHE:
							MLV_draw_image(array_img[CHARACTER_WEST], x_height, y_height);
							break;
					}
					break;
				case MUR:
					MLV_draw_image(array_img[WALL], x_height, y_height);
					break;
				case DESTINATION:
					MLV_draw_image(array_img[DEST], x_height, y_height);
					break;
				default:
					break;
			}
		}
	}
}

void action_listener(MLV_Keyboard_button button, Plateau board){
	switch(button){
		case MLV_KEYBOARD_z:
			board->dir_perso = HAUT;
			break;
		case MLV_KEYBOARD_q:
			board->dir_perso = GAUCHE;
			break;
		case MLV_KEYBOARD_s:
			board->dir_perso = BAS;
			break;
		case MLV_KEYBOARD_d:
			board->dir_perso = DROITE;
			break;
		default:
			return;
	}
	if(board->depl_perso_autorise == true)
		deplace_joueur(board);

}