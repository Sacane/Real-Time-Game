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
}

void resize_all_img(MLV_Image* array_img[],  int width, int height){
	int i;
	for(i = CHARACTER_SOUTH; i <= PLAYER2_WEST_IMG; i++){
		MLV_resize_image(array_img[i], width, height);
	}
}

void free_array_img(MLV_Image *array[]){
	int i;
	for(i = CHARACTER_SOUTH; i <= PLAYER2_WEST_IMG; i++){
		MLV_free_image(array[i]);
	}
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
		case PLAYER1:
			switch(niveau->p1.dir_player){
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
		case PLAYER2:
			switch(niveau->p2.dir_player){
				case HAUT:
					MLV_draw_image(array_img[PLAYER2_NORTH_IMG], x_height, y_height);
					break;
				case BAS:
					MLV_draw_image(array_img[PLAYER2_SOUTH_IMG], x_height, y_height);
					break;
				case DROITE:
					MLV_draw_image(array_img[PLAYER2_EAST_IMG], x_height, y_height);
					break;
				case GAUCHE:
					MLV_draw_image(array_img[PLAYER2_WEST_IMG], x_height, y_height);
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

static void refresh_player(Coordonnees coo_player, Plateau board, unsigned int width, unsigned int height, MLV_Image* array_img[], MLV_Image* font){
	printf("%u, %u\n", coo_player.x, coo_player.y);
	switch(board->objets[coo_player.x][coo_player.y].type){
		case PERSONNAGE:
		case PLAYER1:
			switch(board->p1.dir_player){
				case HAUT:
					if(!se_dirige_vers_mur(coo_player.x + 1, coo_player.y, HAUT, board)){
						MLV_draw_partial_image(font, (coo_player.y) * width, (coo_player.x + 1) * height, width, height, (coo_player.y) * width, (coo_player.x + 1) * height);
					}
					break;
				case DROITE:
					if(!se_dirige_vers_mur(coo_player.x, coo_player.y - 1, DROITE, board)){
						MLV_draw_partial_image(font, (coo_player.y - 1) * width, (coo_player.x) * height, width, height, (coo_player.y - 1) * width, (coo_player.x) * height);
					}
					break;
				case GAUCHE:
					if(!se_dirige_vers_mur(coo_player.x, coo_player.y + 1, GAUCHE, board)){
						MLV_draw_partial_image(font, (coo_player.y + 1) * width, (coo_player.x) * height, width, height, (coo_player.y + 1) * width, (coo_player.x) * height);
					}
					break;
				case BAS:
					if(!se_dirige_vers_mur(coo_player.x - 1, coo_player.y, BAS, board)){
						MLV_draw_partial_image(font, (coo_player.y) * width, (coo_player.x - 1) * height, width, height, (coo_player.y) * width, (coo_player.x - 1) * height);
					}
					break;
				if(board->p1.is_player_alive == false){
					MLV_actualise_window();
					return;
				}
			}
			break;
		case PLAYER2:
			switch(board->p2.dir_player){
				case HAUT:
					if(!se_dirige_vers_mur(coo_player.x + 1, coo_player.y, HAUT, board)){
						MLV_draw_partial_image(font, (coo_player.y) * width, (coo_player.x + 1) * height, width, height, (coo_player.y) * width, (coo_player.x + 1) * height);
					}
					break;
				case DROITE:
					if(!se_dirige_vers_mur(coo_player.x, coo_player.y - 1, DROITE, board)){
						MLV_draw_partial_image(font, (coo_player.y - 1) * width, (coo_player.x) * height, width, height, (coo_player.y - 1) * width, (coo_player.x) * height);
					}
					break;
				case GAUCHE:
					if(!se_dirige_vers_mur(coo_player.x, coo_player.y + 1, GAUCHE, board)){
						MLV_draw_partial_image(font, (coo_player.y + 1) * width, (coo_player.x) * height, width, height, (coo_player.y + 1) * width, (coo_player.x) * height);
					}
					break;
				case BAS:
					if(!se_dirige_vers_mur(coo_player.x - 1, coo_player.y, BAS, board)){
						MLV_draw_partial_image(font, (coo_player.y) * width, (coo_player.x - 1) * height, width, height, (coo_player.y) * width, (coo_player.x - 1) * height);
					}
					break;
			}
			if(board->p2.is_player_alive == false){
				MLV_actualise_window();
				return;
			}
			break;

		default:
			return;
		
	}
	draw_img(board, array_img, coo_player.x, coo_player.y, width, height);
	MLV_actualise_window();
}



int listener(MLV_Keyboard_button button, Plateau board, Player *player){
	switch(button){
		case MLV_KEYBOARD_z:
			board->p1.dir_player = HAUT;
			break;
		case MLV_KEYBOARD_q:
			board->p1.dir_player = GAUCHE;
			break;
		case MLV_KEYBOARD_s:
			board->p1.dir_player = BAS;
			break;
		case MLV_KEYBOARD_d:
			board->p1.dir_player = DROITE;
			break;
		case MLV_KEYBOARD_ESCAPE:
			return 0;
		case MLV_KEYBOARD_UP:
			if(!board->mulptiplayer_mode)
				break;
			board->p2.dir_player = HAUT;
			break;
		case MLV_KEYBOARD_DOWN:
			if(!board->mulptiplayer_mode)
				break;
			board->p2.dir_player = BAS;
			break;
		case MLV_KEYBOARD_RIGHT:
			if(!board->mulptiplayer_mode)
				break;
			board->p2.dir_player = DROITE;
			break;
		case MLV_KEYBOARD_LEFT:
			if(!board->mulptiplayer_mode)
				break;
			board->p2.dir_player = GAUCHE;
			break;
		default:
			return -1;
	}
	
	if(player->can_player_move == true){
		printf("AH\n");
		return move_players(board, player);
	}
	return -1;
}		
/*return 1 if the player who move is the player1, 0 if it's the player 2*/
static int check_which_player_move(MLV_Keyboard_button touche){
	switch(touche){
		case MLV_KEYBOARD_z:
		case MLV_KEYBOARD_s:
		case MLV_KEYBOARD_q:
		case MLV_KEYBOARD_d:
			return 1;
		case MLV_KEYBOARD_UP:
		case MLV_KEYBOARD_DOWN:
		case MLV_KEYBOARD_LEFT:
		case MLV_KEYBOARD_RIGHT:
			return 0;
		default:
			break;
	}
	return -1;
}

void launch(Plateau niveau, bool *is_reached){
    unsigned int x, y;
    int decalage_x, decalage_y;
    MLV_Image *font;
    MLV_Image *array_img[15];
	unsigned int width, height;
    MLV_Keyboard_button touche;
	Arbre tas;
	Evenement e;
	TypeObjet obj;
	MLV_Button_state state;

	MLV_get_desktop_size(&x, &y);
    decalage_x = (niveau->taille.y < niveau->taille.x) ? 50 : 25;
    decalage_y = (niveau->taille.y > niveau->taille.x) ? 50 : 25;
	width = (x / (niveau->taille.y)) - decalage_y;
	height = (y / niveau->taille.x) - decalage_x; 

    tas = construit_Tas (niveau);

    MLV_create_window("RealTimeGame", "Game", x, y);
	printf("before init image\n");
    init_array_img(array_img);
	printf("after init image\n");
    resize_all_img(array_img, width, height);
	printf("after resize\n");
    font = MLV_load_image("assets/font.jpeg");
	if(NULL == font){
		fprintf(stderr, "Image non-existente ou impossible à charger\n");
		exit(1);
	}
    MLV_resize_image(font, width * niveau->taille.y, height * niveau->taille.x);
	MLV_draw_image(array_img[CHARACTER_SOUTH], niveau->p1.coo_player.y, niveau->p1.coo_player.x);
	
	update_plateau(niveau, array_img, font, width, height);
    while (true) {
		check_game_over(niveau);
		if(niveau->is_game_over == true){
			break;
		}

        check_player_move(&(niveau->p1));
		if(niveau->mulptiplayer_mode){
			check_player_move(&(niveau->p2));
		}
		MLV_get_event(&touche, NULL, NULL, NULL, NULL, NULL, NULL, NULL, &state);

		if(state == MLV_PRESSED){
			if(touche == MLV_KEYBOARD_ESCAPE){
				niveau->is_game_over = true;
			}
			switch(check_which_player_move(touche)){
				case 1:
					switch(listener(touche, niveau, &(niveau->p1))){
						case -1:
							break;
						case 0:
							niveau->is_game_over = true;
							break;
						case 1:
							refresh_player(niveau->p1.coo_player, niveau, width, height, array_img, font);
							break;
						default:
							break;
					}
					break;

				case 0:
					switch(listener(touche, niveau, &(niveau->p2))){
						case -1:

							break;
						case 0:
							niveau->is_game_over = true;
							break;
						case 1:
							refresh_player(niveau->p2.coo_player, niveau, width, height, array_img, font);
							break;
						default:
							break;
					}
					break;
				case -1:
					break;
				default:
					break;
			}
			

			state = MLV_RELEASED;
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
		if(check_player_reached(niveau)){
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