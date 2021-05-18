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

static void draw_img(Board niveau, MLV_Image *array_img[], int x_source, int y_source, unsigned int width, unsigned int height){
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
				case NORTH:
					MLV_draw_image(array_img[PROJECTILE_NORTH], x_height, y_height);
					break;
				case SOUTH:
					MLV_draw_image(array_img[PROJECTILE_SOUTH], x_height, y_height);
					break;
				case EAST:
					MLV_draw_image(array_img[PROJECTILE_EAST], x_height, y_height);
					break;
				case WEST:
					MLV_draw_image(array_img[PROJECTILE_WEST], x_height, y_height);
					break;
			}
			break;
		case LAUNCHER:
			MLV_draw_image(array_img[LAUNCHER_IMG], x_height, y_height);
			break;
		case PLAYER1:
			switch(niveau->p1.dir_player){
				case NORTH:
					MLV_draw_image(array_img[CHARACTER_NORTH], x_height, y_height);
					break;
				case SOUTH:
					MLV_draw_image(array_img[CHARACTER_SOUTH], x_height, y_height);
					break;
				case EAST:
					MLV_draw_image(array_img[CHARACTER_EAST], x_height, y_height);
					break;
				case WEST:
					MLV_draw_image(array_img[CHARACTER_WEST], x_height, y_height);
					break;
			}
			break;
		case PLAYER2:
			switch(niveau->p2.dir_player){
				case NORTH:
					MLV_draw_image(array_img[PLAYER2_NORTH_IMG], x_height, y_height);
					break;
				case SOUTH:
					MLV_draw_image(array_img[PLAYER2_SOUTH_IMG], x_height, y_height);
					break;
				case EAST:
					MLV_draw_image(array_img[PLAYER2_EAST_IMG], x_height, y_height);
					break;
				case WEST:
					MLV_draw_image(array_img[PLAYER2_WEST_IMG], x_height, y_height);
					break;
			}
			break;
		case WALL:
		case DOOR:
			MLV_draw_image(array_img[WALL_IMG], x_height, y_height);
			break;
		case DESTINATION:
			MLV_draw_image(array_img[DEST], x_height, y_height);
			break;
		case SWITCH:
			MLV_draw_image(array_img[SWITCH_IMG], x_height, y_height);
			break;
		default:
			break;

	}
}

void update_plateau(Board niveau, MLV_Image *array_img[], MLV_Image *font, unsigned int width, unsigned int height){

	unsigned int i, j;

	MLV_draw_image(font, 0, 0);
	for(i = 0; i < niveau->taille.x; ++i){
		for(j = 0; j < niveau->taille.y; ++j){
			draw_img(niveau, array_img, i, j, width, height);
		}
	}
	MLV_actualise_window();
}

static void refresh_projectile(Coordonnees coo_proj, Board board, unsigned int width, unsigned height, MLV_Image* array_img[], MLV_Image* font){
	
	Deplacement *depl = (Deplacement*)malloc(sizeof(Deplacement));
	MLV_draw_partial_image(font, (coo_proj.y) * width, (coo_proj.x) * height, width, height, (coo_proj.y) * width, (coo_proj.x) * height);
	depl = board->objets[coo_proj.x][coo_proj.y].donnee_suppl;
	if(se_dirige_vers_mur(coo_proj.x, coo_proj.y, depl->direction, board)){
		return;
	}

	switch(depl->direction){
		case NORTH:
			draw_img(board, array_img, coo_proj.x - 1, coo_proj.y, width, height);
			break;
		case SOUTH:
			draw_img(board, array_img, coo_proj.x + 1, coo_proj.y, width, height);
			break;
		case EAST:
			draw_img(board, array_img, coo_proj.x, coo_proj.y + 1, width, height);
			break;
		case WEST:
			draw_img(board, array_img, coo_proj.x, coo_proj.y - 1, width, height);
			break;
	}
}

static void refresh_launcher(Coordonnees coo_launcher, Board board, unsigned int width, unsigned int height, MLV_Image* array_img[]){
	Direction direction;

	for(direction = NORTH; direction <= EAST; direction++){
		if(!se_dirige_vers_mur(coo_launcher.x, coo_launcher.y, direction, board)){
			switch(direction){
				case NORTH:
					draw_img(board, array_img, coo_launcher.x - 1, coo_launcher.y, width, height);
					break;
				case EAST:
					draw_img(board, array_img, coo_launcher.x, coo_launcher.y + 1, width, height);
					break;
				case WEST:
					draw_img(board, array_img, coo_launcher.x, coo_launcher.y - 1, width, height);
					break;
				case SOUTH:
					draw_img(board, array_img, coo_launcher.x + 1, coo_launcher.y, width, height);
					break;
			}
		}
	}
}

static void refresh_player(Coordonnees coo_player, Board board, unsigned int width, unsigned int height, MLV_Image* array_img[], MLV_Image* font){

	switch(board->objets[coo_player.x][coo_player.y].type){
		case PLAYER1:
			switch(board->p1.dir_player){
				case NORTH:
					if(!se_dirige_vers_mur(coo_player.x + 1, coo_player.y, NORTH, board)){
						MLV_draw_partial_image(font, (coo_player.y) * width, (coo_player.x + 1) * height, width, height, (coo_player.y) * width, (coo_player.x + 1) * height);
					}
					break;
				case EAST:
					if(!se_dirige_vers_mur(coo_player.x, coo_player.y - 1, EAST, board)){
						MLV_draw_partial_image(font, (coo_player.y - 1) * width, (coo_player.x) * height, width, height, (coo_player.y - 1) * width, (coo_player.x) * height);
					}
					break;
				case WEST:
					if(!se_dirige_vers_mur(coo_player.x, coo_player.y + 1, WEST, board)){
						MLV_draw_partial_image(font, (coo_player.y + 1) * width, (coo_player.x) * height, width, height, (coo_player.y + 1) * width, (coo_player.x) * height);
					}
					break;
				case SOUTH:
					if(!se_dirige_vers_mur(coo_player.x - 1, coo_player.y, SOUTH, board)){
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
				case NORTH:
					if(!se_dirige_vers_mur(coo_player.x + 1, coo_player.y, NORTH, board)){
						MLV_draw_partial_image(font, (coo_player.y) * width, (coo_player.x + 1) * height, width, height, (coo_player.y) * width, (coo_player.x + 1) * height);
					}
					break;
				case EAST:
					if(!se_dirige_vers_mur(coo_player.x, coo_player.y - 1, EAST, board)){
						MLV_draw_partial_image(font, (coo_player.y - 1) * width, (coo_player.x) * height, width, height, (coo_player.y - 1) * width, (coo_player.x) * height);
					}
					break;
				case WEST:
					if(!se_dirige_vers_mur(coo_player.x, coo_player.y + 1, WEST, board)){
						MLV_draw_partial_image(font, (coo_player.y + 1) * width, (coo_player.x) * height, width, height, (coo_player.y + 1) * width, (coo_player.x) * height);
					}
					break;
				case SOUTH:
					if(!se_dirige_vers_mur(coo_player.x - 1, coo_player.y, SOUTH, board)){
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



static int listener(MLV_Keyboard_button button, Board board, Player *player){
	printf("Listener\n");
	switch(button){
		case MLV_KEYBOARD_z:
			board->p1.dir_player = NORTH;
			break;
		case MLV_KEYBOARD_q:
			printf("WEST\n");
			board->p1.dir_player = WEST;
			break;
		case MLV_KEYBOARD_s:
			board->p1.dir_player = SOUTH;
			break;
		case MLV_KEYBOARD_d:
			board->p1.dir_player = EAST;
			break;
		case MLV_KEYBOARD_ESCAPE:
			return 0;
		case MLV_KEYBOARD_UP:
			if(!board->mulptiplayer_mode)
				break;
			board->p2.dir_player = NORTH;
			break;
		case MLV_KEYBOARD_DOWN:
			if(!board->mulptiplayer_mode)
				break;
			board->p2.dir_player = SOUTH;
			break;
		case MLV_KEYBOARD_RIGHT:
			if(!board->mulptiplayer_mode)
				break;
			board->p2.dir_player = EAST;
			break;
		case MLV_KEYBOARD_LEFT:
			if(!board->mulptiplayer_mode)
				break;
			board->p2.dir_player = WEST;
			break;
		default:
			return -1;
	}
	

	if(player->can_player_move == true && !se_dirige_vers_mur(player->coo_player.x, player->coo_player.y, player->dir_player, board)){
		
		return 1;
	}
	
	if(player->is_player_alive == false){
		return -1;
	}

	printf("end_listener (-1)\n");
	return -1;
}		

static int check_which_player_move(MLV_Keyboard_button touche){
	switch(touche){
		case MLV_KEYBOARD_z:
		case MLV_KEYBOARD_s:
		case MLV_KEYBOARD_q:
		case MLV_KEYBOARD_d:
			return PLAYER1;
		case MLV_KEYBOARD_UP:
		case MLV_KEYBOARD_DOWN:
		case MLV_KEYBOARD_LEFT:
		case MLV_KEYBOARD_RIGHT:
			return PLAYER2;
		default:
			break;
	}
	return -1;
}

static void refresh_switch(Board niveau, Player player, MLV_Image* font, unsigned int width, unsigned int height){

	Trigger *trigg;
	trigg = (Trigger*)malloc(sizeof(Trigger));
	switch(player.dir_player){
		case NORTH:
			memcpy(trigg, niveau->objets[player.coo_player.x - 1][player.coo_player.y].donnee_suppl, sizeof(Trigger));
			break;
		case SOUTH:
			memcpy(trigg, niveau->objets[player.coo_player.x + 1][player.coo_player.y].donnee_suppl, sizeof(Trigger));
			break;
		case EAST:
			memcpy(trigg, niveau->objets[player.coo_player.x][player.coo_player.y + 1].donnee_suppl, sizeof(Trigger));
			break;
		case WEST:
			memcpy(trigg, niveau->objets[player.coo_player.x][player.coo_player.y - 1].donnee_suppl, sizeof(Trigger));
			break;
	}

	
	MLV_draw_partial_image(font, (trigg->coo_door.y) * width, (trigg->coo_door.x) * height, width, height, (trigg->coo_door.y) * width, (trigg->coo_door.x) * height);

	free(trigg);
}

static void erase_player_after_reached(Board board, unsigned int width, unsigned int height, MLV_Image* font){
	if(!board->p1.is_player_alive){
		MLV_draw_partial_image(font, (board->p1.coo_player.y) * width, (board->p1.coo_player.x) * height, width, height, board->p1.coo_player.y * width, (board->p1.coo_player.x) * height);
	}
	if(board->mulptiplayer_mode){
		if(!board->p2.is_player_alive){
			MLV_draw_partial_image(font, (board->p2.coo_player.y) * width, (board->p2.coo_player.x) * height, width, height, board->p2.coo_player.y * width, (board->p2.coo_player.x) * height);
		}
	}
	MLV_actualise_window();
}

void launch(Board gameboard, bool *is_reached){
	assert(gameboard != NULL);
	printf("launch\n");
    unsigned int x, y;
    int decalage_x, decalage_y;
    MLV_Image *font;
    MLV_Image *array_img[SIZE_ARR_IMG];
	unsigned int width, height;
    MLV_Keyboard_button touche;
	Heap tas = construit_Tas(gameboard);
	Event e;
	TypeObjet obj;
	MLV_Button_state state;

	MLV_get_desktop_size(&x, &y);
	
    decalage_x = (gameboard->taille.y < gameboard->taille.x) ? 50 : 25;
    decalage_y = (gameboard->taille.y > gameboard->taille.x) ? 50 : 25;
	width = (x / (gameboard->taille.y)) - decalage_y;
	height = (y / gameboard->taille.x) - decalage_x; 
	width = 50;
	height = 45;
	printf("heap\n");
 
	printf("heap builded\n");
    MLV_create_window("RealTimeGame", "Game", x, y);
    init_array_img(array_img);
    resize_all_img(array_img, width, height);
    font = MLV_load_image("assets/font.jpeg");
	if(NULL == font){
		fprintf(stderr, "Image non-existente ou impossible à charger\n");
		exit(1);
	}
    MLV_resize_image(font, width * gameboard->taille.y, height * gameboard->taille.x);
	MLV_draw_image(array_img[CHARACTER_SOUTH], gameboard->p1.coo_player.y, gameboard->p1.coo_player.x);
	printf("update platea\n");
	update_plateau(gameboard, array_img, font, width, height);
    while (true) {
		if(gameboard->is_game_over){
			break;
		}
		if(check_victory(gameboard)){
			(*is_reached) = true;
			break;
		}
		if(check_game_over(gameboard)){
			break;
		}

        check_player_move(&(gameboard->p1));
		if(gameboard->mulptiplayer_mode){
			check_player_move(&(gameboard->p2));
		}
		MLV_get_event(&touche, NULL, NULL, NULL, NULL, NULL, NULL, NULL, &state);

		if(state == MLV_PRESSED){
			if(touche == MLV_KEYBOARD_ESCAPE){
				gameboard->is_game_over = true;
				break;
			}
			switch(check_which_player_move(touche)){
				case PLAYER1:
					if(listener(touche, gameboard, &(gameboard->p1)) == -1){
						break;
					}
					
					if(going_to_obj(gameboard, gameboard->p1, DESTINATION)){
						gameboard->p1.has_player_win = true;
						erase_player_after_reached(gameboard, width, height, font);
					}
					if(going_to_obj(gameboard, gameboard->p1, SWITCH)){
						printf("Ici\n");
						trigger_switch(gameboard, gameboard->p1);
						printf("end trigger\n");
						refresh_switch(gameboard, gameboard->p1, font, width, height);
						printf("end refresh\n");
					}

					if(!se_dirige_vers_mur(gameboard->p1.coo_player.x, gameboard->p1.coo_player.y, gameboard->p1.dir_player, gameboard)){
						printf("move\n");
						switch(move_players(gameboard, &(gameboard->p1))){
							
							case -1:
								
								break;
							case 0:
								printf("0\n");
								gameboard->p1.is_player_alive = false;
								break;
							case 1:
								refresh_player(gameboard->p1.coo_player, gameboard, width, height, array_img, font);
								break;
							default:
								break;
						}
					}
					break;

				case PLAYER2:
					if(listener(touche, gameboard, &(gameboard->p2))== -1){
						break;
					}
					if(going_to_obj(gameboard, gameboard->p2, DESTINATION)){
						gameboard->p2.has_player_win = true;
						erase_player_after_reached(gameboard, width, height, font);
					}
					if(going_to_obj(gameboard, gameboard->p2, SWITCH)){
						trigger_switch(gameboard, gameboard->p2);
						refresh_switch(gameboard, gameboard->p2, font, width, height);
					}
					switch(move_players(gameboard, &(gameboard->p2))){
						case -1:
							printf("destination\n");
							break;
						case 0:
							gameboard->p2.has_player_win = true;
							break;
						case 1:
							refresh_player(gameboard->p2.coo_player, gameboard, width, height, array_img, font);
							
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
        
        if (is_event_ready(tas)){
            e = heap_pop(tas);
			obj = gameboard->objets[e.coo_obj.x][e.coo_obj.y].type;
            execute_event(e, tas, gameboard);
			if(obj == PROJECTILE){
				refresh_projectile(e.coo_obj, gameboard, width, height, array_img, font);
			}else if(obj == LAUNCHER){
				refresh_launcher(e.coo_obj, gameboard, width, height, array_img);
			}
            while(e.moment == tas->valeurs[0].moment){
                e = heap_pop(tas);
				obj = gameboard->objets[e.coo_obj.x][e.coo_obj.y].type;
				execute_event(e, tas, gameboard);
				if(obj == PROJECTILE){
					refresh_projectile(e.coo_obj, gameboard, width, height, array_img, font);
				}else if(obj == LAUNCHER){
					refresh_launcher(e.coo_obj, gameboard, width, height, array_img);
				}
			}
			
            MLV_actualise_window();
            
        }   
        else
            millisleep (50);
		if(check_player_reached(gameboard)){
			(*is_reached) = true;

			break;
		}
        
    }
    MLV_free_image(font);
    free_array_img(array_img);
    MLV_free_window();
    printf("program ended in : %lu seconds\n", clock() / ((10000) * une_milliseconde));
    free_heap(tas);
	
    printf("end_free\n");
}