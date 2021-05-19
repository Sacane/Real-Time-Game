#include "../include/management.h"


Heap build_heap_by_board(Board niveau){
    printf("%u x %u\n", niveau->taille.x, niveau->taille.y);
    printf("Construct\n");
	Heap heap;
    heap = malloc_heap(INITIAL_SIZE); 
	Event event;
	unsigned int i, j;
    Generation *gen = (Generation*)malloc(sizeof(Generation));
    verif_malloc(gen);
	for(i = 0; i < niveau->taille.x ; i++){
		for(j = 0; j < niveau->taille.y; j++){
			if(niveau->objets[i][j].type == LAUNCHER) {
                printf("agter\n");
                assert(niveau->objets[i][j].data != NULL);
                memcpy(gen, niveau->objets[i][j].data, sizeof(Generation));
                printf("ad\n");
				event.coo_obj.x = i;
				event.coo_obj.y = j;
				event.moment = gen->intervalle;
				add_event(heap, event);
			}
		}
	}
    free(gen);
	return heap;
}


static void spawn_projectile_by_direction(Board board, Direction direction, Coordinates *pos_projectile, Coordinates pos_lanceur){
	
    Deplacement* deplacement;
    deplacement = (Deplacement*)malloc(sizeof(Deplacement));
    verif_malloc(deplacement);
    Generation *generation = (Generation*)malloc(sizeof(Generation));
    verif_malloc(generation);
    memcpy(generation, board->objets[pos_lanceur.x][pos_lanceur.y].data, sizeof(Generation));
    deplacement->allure = generation->allure_proj;
    
    switch(direction){
        case NORTH:
            pos_projectile->x = pos_lanceur.x - 1;
            pos_projectile->y = pos_lanceur.y;
            deplacement->direction = NORTH;
            break;
        case SOUTH:
            pos_projectile->x = pos_lanceur.x + 1;
            pos_projectile->y = pos_lanceur.y;
            deplacement->direction = SOUTH;
            break;
        case EAST:
            pos_projectile->x = pos_lanceur.x;
            pos_projectile->y = pos_lanceur.y + 1;
            deplacement->direction = EAST;
            break;
        case WEST:
            pos_projectile->x = pos_lanceur.x;
            pos_projectile->y = pos_lanceur.y - 1;
            deplacement->direction = WEST;
            break;
        default:
            printf("Erreur de direction\n");
    }
    board->objets[pos_projectile->x][pos_projectile->y].type = PROJECTILE;
    board->objets[pos_projectile->x][pos_projectile->y].data = deplacement;

    if(equals_coordinates(*pos_projectile, board->p1.coo_player)){
        board->p1.is_player_alive = false;
    }
    if(board->mulptiplayer_mode){
        if(equals_coordinates(*pos_projectile, board->p2.coo_player)){
            board->p2.is_player_alive = false;
        }
    }
    free(generation);
}

/*Prend en paramètre l'ancien lanceur dans le tas et remet à jour le tas pour remettre l'évènement du lanceur 1 seconde après retrait du tas*/
static void update_launcher_in_heap(Event lanceur, Heap tas, Coordinates pos_lanceur, Board niveau){

    unsigned long update_moment;
    Generation *generation = (Generation*)malloc(sizeof(Generation));
    verif_malloc(generation);
    Event new_launcher;
    memcpy(generation, niveau->objets[pos_lanceur.x][pos_lanceur.y].data, sizeof(Generation));
    update_moment = lanceur.moment + generation->intervalle;
    new_launcher.moment = update_moment;
    new_launcher.coo_obj = lanceur.coo_obj;
    add_event(tas, new_launcher);

    free(generation);
}

void trigger_launcher(Board niveau, Heap tas, Coordinates pos_lanceur, Event ancien_lanceur){
	
    assert(niveau != NULL);
    assert(tas != NULL);
    assert(niveau->objets[pos_lanceur.x][pos_lanceur.y].type == LAUNCHER);
    assert(pos_lanceur.x <= niveau->taille.x);
    assert(pos_lanceur.y <= niveau->taille.y);
    
    Generation *generation = (Generation*)malloc(sizeof(Generation));
    verif_malloc(generation);
    memcpy(generation, niveau->objets[pos_lanceur.x][pos_lanceur.y].data, sizeof(Generation));
    Direction direction;
    Coordinates pos_projectile;
    Event event_proj;

    for(direction = NORTH; direction <= EAST; direction++){
        if(!se_dirige_vers_mur(pos_lanceur.x, pos_lanceur.y, direction, niveau)){
            spawn_projectile_by_direction(niveau, direction, &pos_projectile, pos_lanceur);
            event_proj.moment = ancien_lanceur.moment + generation->allure_proj;
            event_proj.coo_obj = pos_projectile;
            add_event(tas, event_proj);
        }
    }

    update_launcher_in_heap(ancien_lanceur, tas, pos_lanceur, niveau);

    free(generation);
}


void trigger_projectile(Heap tas, Board niveau, Coordinates pos_projectile, Event projectile){

	assert(tas != NULL);
	assert(niveau != NULL);
	assert(pos_projectile.x <= niveau->taille.x);
	assert(pos_projectile.y <= niveau->taille.y);
    assert(niveau->objets[pos_projectile.x][pos_projectile.y].type == PROJECTILE);

    Event evenement_projectile;
    Deplacement *dep = (Deplacement*)malloc(sizeof(Deplacement));
    dep = niveau->objets[pos_projectile.x][pos_projectile.y].data;
    move_projectile(niveau, &pos_projectile);
    unsigned long moment = projectile.moment + dep->allure;

	if(pos_projectile.x <= niveau->taille.x && pos_projectile.y <= niveau->taille.y){
		evenement_projectile.moment = moment;
		evenement_projectile.coo_obj = pos_projectile;
		add_event(tas, evenement_projectile);
    }
}

void execute_event(Event e, Heap tas, Board niveau) {

    assert(tas != NULL);
	assert(tas->valeurs != NULL);
    assert(niveau != NULL);
	assert(e.coo_obj.x <= niveau->taille.x);
    assert(e.coo_obj.y <= niveau->taille.y);
    Coordinates coo_event;
    coo_event.x = e.coo_obj.x;
    coo_event.y = e.coo_obj.y;

    switch(niveau->objets[coo_event.x][coo_event.y].type){
        case PROJECTILE:
            trigger_projectile(tas, niveau, coo_event, e);
            break;
        case LAUNCHER:
            trigger_launcher(niveau, tas, coo_event, e);
            break;
        default:
            break;
    }
}

void launch_command(Board board, bool *is_reached){
    
    init_stdin();
    Heap tas = build_heap_by_board(board);
    Event e;
	char touche;
    int success = true;
    bool moving = false;

    print_board(board);

    while (true) {
        
        if(board->p1.is_player_alive == false){
            break;
        }
        if(board->mulptiplayer_mode){
            if(board->p2.is_player_alive == false){
                break;
            }
        }
        check_player_move(&(board->p1));
        if(board->mulptiplayer_mode)
            check_player_move(&(board->p2));
            
        while((touche = getchar()) != EOF){
            if(board->p1.can_player_move == true){
                switch (touche)
                {
                    case 'z':
                        board->p1.dir_player = NORTH;
                        moving = true;
                        break;
                    case 's':
                        board->p1.dir_player = SOUTH;
                        moving = true;
                        break;
                    case 'd':
                        board->p1.dir_player = EAST;
                        moving = true;
                        break;
                    case 'q':
                        board->p1.dir_player = WEST;
                        moving = true;
                        break;
                    default:
                        moving = false;
                        break;
                }
                if(board->p1.can_player_move == true && moving == true){
                    success = move_players(board, &(board->p1));
                    if(!success){
                        break;
                    }
                }
            }
            if(board->mulptiplayer_mode){
                if(board->p2.can_player_move == true){
                    switch(touche)
                    {
                        case 'o':
                            board->p2.dir_player = NORTH;
                            moving = true;
                            break;
                        case 'l':
                            board->p2.dir_player = SOUTH;
                            moving = true;
                            break;
                        case 'm':
                            board->p2.dir_player = EAST;
                            moving = true;
                            break;
                        case 'k':
                            board->p2.dir_player = WEST;
                            moving = true;
                            break;
                        default:
                            moving = false;
                            break;

                    }
                    if(board->p2.can_player_move && moving)
                        success = move_players(board, &(board->p2));
                    if(success == 0){
                        break;
                    }
                    else if(success == -1){
                        continue;
                    }
                }
            }
        }
        if(!success){
            break;
        }
        if ( is_event_ready(tas)) {

            e = heap_pop(tas);
            
            execute_event(e, tas, board);
            while(e.moment == tas->valeurs[0].moment){
                e = heap_pop(tas);
                execute_event(e, tas, board);
            }
            print_board(board);
    		printf("\n");
        }   
        else
            millisleep (10); 
        if(check_player_reached(board)){
            (*is_reached) = true;
            break;
        }
    }
    free_heap(tas);
    restaure_stdin();

}