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

static void draw_img(Plateau niveau, MLV_Image *array_img[], int x_source, int y_source, unsigned int width, unsigned int height){
	int x_height, y_height;
	x_height = y_source * width;
	y_height = x_source * height;
	Deplacement *depl = (Deplacement*)malloc(sizeof(Deplacement));
	switch(niveau->objets[x_source][y_source].type){
		case VIDE: 
			break;
		case PROJECTILE:
			depl = niveau->objets[x_source][y_source].donnee_suppl;
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

void update_plateau(Plateau niveau, MLV_Image *array_img[], MLV_Image *font, unsigned int width, unsigned int height){

	unsigned int i, j;

	MLV_draw_image(font, 0, 0);
	for(i = 0; i < niveau->taille.x; ++i){
		for(j = 0; j < niveau->taille.y; ++j){
			draw_img(niveau, array_img, i, j, width, height);
		}
	}
	MLV_actualise_window();
}

static void refresh_projectile(Coordonnees coo_proj, Plateau board, unsigned int width, unsigned height, MLV_Image* array_img[], MLV_Image* font){
	
	Deplacement *depl = (Deplacement*)malloc(sizeof(Deplacement));
	MLV_draw_partial_image(font, (coo_proj.y) * width, (coo_proj.x) * height, width, height, (coo_proj.y) * width, (coo_proj.x) * height);
	depl = board->objets[coo_proj.x][coo_proj.y].donnee_suppl;
	if(se_dirige_vers_mur(coo_proj.x, coo_proj.y, depl->direction, board)){
		return;
	}

	switch(depl->direction){
		case HAUT:
			draw_img(board, array_img, coo_proj.x - 1, coo_proj.y, width, height);
			break;
		case BAS:
			draw_img(board, array_img, coo_proj.x + 1, coo_proj.y, width, height);
			break;
		case DROITE:
			draw_img(board, array_img, coo_proj.x, coo_proj.y + 1, width, height);
			break;
		case GAUCHE:
			draw_img(board, array_img, coo_proj.x, coo_proj.y - 1, width, height);
			break;
	}
}

static void refresh_launcher(Coordonnees coo_launcher, Plateau board, unsigned int width, unsigned int height, MLV_Image* array_img[]){
	Direction direction;

	for(direction = HAUT; direction <= DROITE; direction++){
		if(!se_dirige_vers_mur(coo_launcher.x, coo_launcher.y, direction, board)){
			switch(direction){
				case HAUT:
					draw_img(board, array_img, coo_launcher.x - 1, coo_launcher.y, width, height);
					break;
				case DROITE:
					draw_img(board, array_img, coo_launcher.x, coo_launcher.y + 1, width, height);
					break;
				case GAUCHE:
					draw_img(board, array_img, coo_launcher.x, coo_launcher.y - 1, width, height);
					break;
				case BAS:
					draw_img(board, array_img, coo_launcher.x + 1, coo_launcher.y, width, height);
					break;
			}
		}
	}
}

static void refresh_character(Coordonnees coo_obj, Plateau board, unsigned int width, unsigned int height, MLV_Image* array_img[], MLV_Image* font){
	
	switch(board->objets[coo_obj.x][coo_obj.y].type){
		case PERSONNAGE:
			switch(board->dir_perso){
				case HAUT:
					if(!se_dirige_vers_mur(coo_obj.x + 1, coo_obj.y, HAUT, board)){
						MLV_draw_partial_image(font, (coo_obj.y) * width, (coo_obj.x + 1) * height, width, height, (coo_obj.y) * width, (coo_obj.x + 1) * height);
					}
					break;
				case DROITE:
					if(!se_dirige_vers_mur(coo_obj.x, coo_obj.y - 1, DROITE, board)){
						MLV_draw_partial_image(font, (coo_obj.y - 1) * width, (coo_obj.x) * height, width, height, (coo_obj.y - 1) * width, (coo_obj.x) * height);
					}
					break;
				case GAUCHE:
					if(!se_dirige_vers_mur(coo_obj.x, coo_obj.y + 1, GAUCHE, board)){
						MLV_draw_partial_image(font, (coo_obj.y + 1) * width, (coo_obj.x) * height, width, height, (coo_obj.y + 1) * width, (coo_obj.x) * height);
					}
					break;
				case BAS:
					if(!se_dirige_vers_mur(coo_obj.x - 1, coo_obj.y, BAS, board)){
						MLV_draw_partial_image(font, (coo_obj.y) * width, (coo_obj.x - 1) * height, width, height, (coo_obj.y) * width, (coo_obj.x - 1) * height);
					}
					break;
			}
			break;
		default:
			return;
		
	}
	draw_img(board, array_img, coo_obj.x, coo_obj.y, width, height);
	MLV_actualise_window();
}

int action_listener(MLV_Keyboard_button button, Plateau board){

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
		case MLV_KEYBOARD_ESCAPE:
			return 0;
		default:
			return -1;
	}
	if(board->depl_perso_autorise == true){
		return deplace_joueur(board);
	}++++++++++
	return -1;
}

void launch_gui(Plateau niveau, bool *is_reached){
    unsigned int x, y;
    int decalage_x, decalage_y;
    MLV_Image *font;
    MLV_Image *array_img[11];
	unsigned int width, height;
    MLV_Keyboard_button touche;
	Arbre tas;
	Evenement e;
	TypeObjet obj;
	
	MLV_get_desktop_size(&x, &y);
    decalage_x = (niveau->taille.y < niveau->taille.x) ? 50 : 25;
    decalage_y = (niveau->taille.y > niveau->taille.x) ? 50 : 25;
	width = (x / (niveau->taille.y)) - decalage_y;
	height = (y / niveau->taille.x) - decalage_x; 

    tas = construit_Tas (niveau);

    MLV_create_window("RealTimeGame", "Game", x, y);

    init_array_img(array_img);
    resize_all_img(array_img, width, height);
    font = MLV_load_image("assets/font.jpeg");
	if(NULL == font){
		fprintf(stderr, "Image non-existente ou impossible à charger\n");
		exit(1);
	}
    MLV_resize_image(font, width * niveau->taille.y, height * niveau->taille.x);
	MLV_draw_image(array_img[CHARACTER_SOUTH], niveau->coo_perso.y, niveau->coo_perso.x);
    
	niveau->dir_perso = BAS;
	update_plateau(niveau, array_img, font, width, height);
    while (true) {
        if(niveau->est_vivant == false){
            break;
        }
		
        verifie_mouvement_personnage(niveau);
        while(MLV_get_event(&touche, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL) != MLV_NONE){
			
			switch(action_listener(touche, niveau)){
				case 0:
					niveau->est_vivant = false;
					break;
				case 1:
					refresh_character(niveau->coo_perso, niveau, width, height, array_img, font);
				case -1:
					break;
				default:
					break;
			}
        }
        
        if (un_evenement_est_pret(tas)){
            e = ote_minimum(tas);
			obj = niveau->objets[e.coo_obj.x][e.coo_obj.y].type;
            execute_evenement(e, tas, niveau);
			if(obj == PROJECTILE){
				refresh_projectile(e.coo_obj, niveau, width, height, array_img, font);
			}else if(obj == LANCEUR){
				refresh_launcher(e.coo_obj, niveau, width, height, array_img);
			}
            while(e.moment == tas->valeurs[0].moment){
                e = ote_minimum(tas);
				obj = niveau->objets[e.coo_obj.x][e.coo_obj.y].type;
				execute_evenement(e, tas, niveau);
				if(obj == PROJECTILE){
					refresh_projectile(e.coo_obj, niveau, width, height, array_img, font);
				}else if(obj == LANCEUR){
					refresh_launcher(e.coo_obj, niveau, width, height, array_img);
				}
			}
			
            MLV_actualise_window();
            
        }   
        else
            millisleep (10);
		if(check_level_reached(niveau)){
			(*is_reached) = true;
			break;
		}
        
    }
    MLV_free_image(font);
    free_array_img(array_img);
    MLV_free_window();
    printf("program ended in : %lu seconds\n", clock() / ((1000) * une_milliseconde));
    free_Tas(tas);
    printf("end_free\n");
}

void launch_gui_bis(Plateau niveau, bool *is_reached){
    unsigned int x, y;
    int decalage_x, decalage_y;
    MLV_Image *font;
    MLV_Image *array_img[11];
	unsigned int width, height;
    MLV_Keyboard_button touche;
	Arbre tas;
	Evenement e;
	TypeObjet obj;
	
	MLV_get_desktop_size(&x, &y);
    decalage_x = (niveau->taille.y < niveau->taille.x) ? 50 : 25;
    decalage_y = (niveau->taille.y > niveau->taille.x) ? 50 : 25;
	width = (x / (niveau->taille.y)) - decalage_y;
	height = (y / niveau->taille.x) - decalage_x; 

    tas = construit_Tas (niveau);

    MLV_create_window("RealTimeGame", "Game", x, y);

    init_array_img(array_img);
    resize_all_img(array_img, width, height);
    font = MLV_load_image("assets/font.jpeg");
	if(NULL == font){
		fprintf(stderr, "Image non-existente ou impossible à charger\n");
		exit(1);
	}
    MLV_resize_image(font, width * niveau->taille.y, height * niveau->taille.x);
	MLV_draw_image(array_img[CHARACTER_SOUTH], niveau->coo_perso.y, niveau->coo_perso.x);
    
	niveau->dir_perso = BAS;
	update_plateau(niveau, array_img, font, width, height);
    while (true) {
        if(niveau->est_vivant == false){
            break;
        }
		
        verifie_mouvement_personnage(niveau);
        if(MLV_get_keyboard_state(MLV_KEYBOARD_z) == MLV_PRESSED){
			touche = MLV_KEYBOARD_z;
			switch(action_listener(touche, niveau)){
				case 0:
					niveau->est_vivant = false;
					break;
				case 1:
					refresh_character(niveau->coo_perso, niveau, width, height, array_img, font);
				case -1:
					break;
				default:
					break;
			}
        }
		if(MLV_get_keyboard_state(MLV_KEYBOARD_s) == MLV_PRESSED){
			touche = MLV_KEYBOARD_s;
			switch(action_listener(touche, niveau)){
				case 0:
					niveau->est_vivant = false;
					break;
				case 1:
					refresh_character(niveau->coo_perso, niveau, width, height, array_img, font);
				case -1:
					break;
				default:
					break;
			}
		}
		if(MLV_get_keyboard_state(MLV_KEYBOARD_q) == MLV_PRESSED){
			touche = MLV_KEYBOARD_q;
			switch(action_listener(touche, niveau)){
				case 0:
					niveau->est_vivant = false;
					break;
				case 1:
					refresh_character(niveau->coo_perso, niveau, width, height, array_img, font);
				case -1:
					break;
				default:
					break;
			}
		}
		if(MLV_get_keyboard_state(MLV_KEYBOARD_d) == MLV_PRESSED){
			touche = MLV_KEYBOARD_d;
			switch(action_listener(touche, niveau)){
				case 0:
					niveau->est_vivant = false;
					break;
				case 1:
					refresh_character(niveau->coo_perso, niveau, width, height, array_img, font);
				case -1:
					break;
				default:
					break;
			}
		}
        
        if (un_evenement_est_pret(tas)){
            e = ote_minimum(tas);
			obj = niveau->objets[e.coo_obj.x][e.coo_obj.y].type;
            execute_evenement(e, tas, niveau);
			if(obj == PROJECTILE){
				refresh_projectile(e.coo_obj, niveau, width, height, array_img, font);
			}else if(obj == LANCEUR){
				refresh_launcher(e.coo_obj, niveau, width, height, array_img);
			}
            while(e.moment == tas->valeurs[0].moment){
                e = ote_minimum(tas);
				obj = niveau->objets[e.coo_obj.x][e.coo_obj.y].type;
				execute_evenement(e, tas, niveau);
				if(obj == PROJECTILE){
					refresh_projectile(e.coo_obj, niveau, width, height, array_img, font);
				}else if(obj == LANCEUR){
					refresh_launcher(e.coo_obj, niveau, width, height, array_img);
				}
			}
			
            MLV_actualise_window();
            
        }   
        else
            millisleep (10);
		if(check_level_reached(niveau)){
			(*is_reached) = true;
			break;
		}
        
    }
    MLV_free_image(font);
    free_array_img(array_img);
    MLV_free_window();
    printf("program ended in : %lu seconds\n", clock() / ((1000) * une_milliseconde));
    free_Tas(tas);
    printf("end_free\n");
}