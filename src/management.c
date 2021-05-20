/**
 * \file management.c
 * \authors Ramaroson Rakotomihamina Johan && Li Christine
 * \date : 01-04-21
 * \last modification : 21-05-21
 * 
 * This module is used to manage all functions related to the management of the game.
 *
 */

#include "../include/management.h"


/**
 * \fn Heap build_heap_by_board(Board level)
 * \brief Function to build a heap containing the initial Events of a Level
 * Carefull : we suppose the heap not allocated yet, the function does it already.
 * \param level : Board, a game board
 * \return Heap, the Heap filled according to the initials event in the gameboard.
 */
Heap build_heap_by_board(Board level){
    printf("%u x %u\n", level->size.x, level->size.y);
    printf("Construct\n");
	Heap heap;
    heap = malloc_heap(INITIAL_SIZE); 
	Event event;
	unsigned int i, j;
    Generation *gen = (Generation*)malloc(sizeof(Generation));
    verif_malloc(gen);
	for(i = 0; i < level->size.x ; i++){
		for(j = 0; j < level->size.y; j++){
			if(level->objects[i][j].type == LAUNCHER) {
                
                assert(level->objects[i][j].data != NULL);
                memcpy(gen, level->objects[i][j].data, sizeof(Generation));
                
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


/**
 * \fn static void spawn_projectile_by_direction(Board board, Direction direction, Coordinates *pos_projectile, Coordinates pos_launcher)
 * \param board : Board, a game board
 * \param direction : Direction, a direction to take
 * \param pos_projectile : Coordinates *, coordinate of the projectile
 * \param pos_launcher : Coordinates, coordinate of the launcher
 */
static void spawn_projectile_by_direction(Board board, Direction direction, Coordinates *pos_projectile, Coordinates pos_launcher){
	
    Deplacement* deplacement;
    deplacement = (Deplacement*)malloc(sizeof(Deplacement));
    verif_malloc(deplacement);
    Generation *generation = (Generation*)malloc(sizeof(Generation));
    verif_malloc(generation);
    memcpy(generation, board->objects[pos_launcher.x][pos_launcher.y].data, sizeof(Generation));
    deplacement->allure = generation->allure_proj;
    
    switch(direction){
        case NORTH:
            pos_projectile->x = pos_launcher.x - 1;
            pos_projectile->y = pos_launcher.y;
            deplacement->direction = NORTH;
            break;
        case SOUTH:
            pos_projectile->x = pos_launcher.x + 1;
            pos_projectile->y = pos_launcher.y;
            deplacement->direction = SOUTH;
            break;
        case EAST:
            pos_projectile->x = pos_launcher.x;
            pos_projectile->y = pos_launcher.y + 1;
            deplacement->direction = EAST;
            break;
        case WEST:
            pos_projectile->x = pos_launcher.x;
            pos_projectile->y = pos_launcher.y - 1;
            deplacement->direction = WEST;
            break;
        default:
            printf("Erreur de direction\n");
    }
    board->objects[pos_projectile->x][pos_projectile->y].type = PROJECTILE;
    board->objects[pos_projectile->x][pos_projectile->y].data = deplacement;

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



/**
 * \fn static void update_launcher_in_heap(Event launcher, Heap heap, Coordinates pos_launcher, Board level)
 * \brief Takes the old launcher in the heap as a parameter and updates the heap to reset the launcher event 1 second after removal from the heap
 * \param launcher : Event, a launcher
 * \param heap : Heap, a heap to deal with
 * \param pos_launcher : Coordinates, coordinate of the launcher
 * \param level : Board, a game board
 */
static void update_launcher_in_heap(Event launcher, Heap heap, Coordinates pos_launcher, Board level){

    unsigned long update_moment;
    Generation *generation = (Generation*)malloc(sizeof(Generation));
    verif_malloc(generation);
    Event new_launcher;
    memcpy(generation, level->objects[pos_launcher.x][pos_launcher.y].data, sizeof(Generation));
    update_moment = launcher.moment + generation->intervalle;
    new_launcher.moment = update_moment;
    new_launcher.coo_obj = launcher.coo_obj;
    add_event(heap, new_launcher);

    free(generation);
}


/**
 * \fn void trigger_launcher(Board level, Heap heap, Coordinates pos_launcher, Event previous_launcher)
 * \brief Function to activate a player's event
 * \param level : Board, a game board
 * \param heap : Heap, a pointer to a heap
 * \param pos_launcher : Coordinates, coordinates of laucher
 * \param previous_launcher : Event, the player event
 */
void trigger_launcher(Board level, Heap heap, Coordinates pos_launcher, Event previous_launcher){
	
    assert(level != NULL);
    assert(heap != NULL);
    assert(level->objects[pos_launcher.x][pos_launcher.y].type == LAUNCHER);
    assert(pos_launcher.x <= level->size.x);
    assert(pos_launcher.y <= level->size.y);
    
    Generation *generation = (Generation*)malloc(sizeof(Generation));
    verif_malloc(generation);
    memcpy(generation, level->objects[pos_launcher.x][pos_launcher.y].data, sizeof(Generation));
    Direction direction;
    Coordinates pos_projectile;
    Event event_proj;

    for(direction = NORTH; direction <= EAST; direction++){
        if(!is_object_going_to_crash(pos_launcher.x, pos_launcher.y, direction, level)){
            spawn_projectile_by_direction(level, direction, &pos_projectile, pos_launcher);
            event_proj.moment = previous_launcher.moment + generation->allure_proj;
            event_proj.coo_obj = pos_projectile;
            add_event(heap, event_proj);
        }
    }

    update_launcher_in_heap(previous_launcher, heap, pos_launcher, level);

    free(generation);
}


/**
 * \fn void trigger_projectile(Heap heap, Board level, Coordinates pos_projectile, Event projectile)
 * \brief Function to activate the event of a projectile
 * \param heap : Heap, a pointer to a heap
 * \param level : Board, a game board
 * \param pos_projectile : Coordinates, coordinates of a projectile
 * \param projectile : Event, the projectile event
 */
void trigger_projectile(Heap heap, Board level, Coordinates pos_projectile, Event projectile){

	assert(heap != NULL);
	assert(level != NULL);
	assert(pos_projectile.x <= level->size.x);
	assert(pos_projectile.y <= level->size.y);
    assert(level->objects[pos_projectile.x][pos_projectile.y].type == PROJECTILE);

    Event evenement_projectile;
    Deplacement *dep = (Deplacement*)malloc(sizeof(Deplacement));
    dep = level->objects[pos_projectile.x][pos_projectile.y].data;
    move_projectile(level, &pos_projectile);
    unsigned long moment = projectile.moment + dep->allure;

	if(pos_projectile.x <= level->size.x && pos_projectile.y <= level->size.y){
		evenement_projectile.moment = moment;
		evenement_projectile.coo_obj = pos_projectile;
		add_event(heap, evenement_projectile);
    }
}


/** 
 * \fn void execute_event(Event e, Heap heap, Board level)
 * \brief Execute an event according to the coordinate of the object in the given gameboard,
 * this function also update the heap's state by adding the next event according to the event e given.
 * \param e : event to execute
 * \param heap : Heap, heap to add the next event
 * \param level : Board, gameboard to update according to the event
 */
void execute_event(Event e, Heap heap, Board level) {

    assert(heap != NULL);
	assert(heap->values != NULL);
    assert(level != NULL);
	assert(e.coo_obj.x <= level->size.x);
    assert(e.coo_obj.y <= level->size.y);
    Coordinates coo_event;
    coo_event.x = e.coo_obj.x;
    coo_event.y = e.coo_obj.y;

    switch(level->objects[coo_event.x][coo_event.y].type){
        case PROJECTILE:
            trigger_projectile(heap, level, coo_event, e);
            break;
        case LAUNCHER:
            trigger_launcher(level, heap, coo_event, e);
            break;
        default:
            break;
    }
}


/**
 * \fn void launch_command(Board board, bool *is_reached)
 * \brief Launch the game in the command line. 
 * \param board : Board, The gameboard containing all the object and players in the game.
 * \param is_reached : boolean to check if the game is reached or lost.
 */ 
void launch_command(Board board, bool *is_reached){
    
    init_stdin();
    Heap heap = build_heap_by_board(board);
    Event e;
	char touche;
    int success = true;
    bool moving = false;

    print_board(board);

    while (true) {
        
        if(check_victory(board)){
            (*is_reached) = true;
            break;
        }
        if(board->p1.is_player_alive == false){
            (*is_reached) = false;
            break;
        }
        if(board->mulptiplayer_mode){
            if(board->p2.is_player_alive == false){
                (*is_reached) = false;
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
            (*is_reached) = false;
            break;
        }
        if ( is_event_ready(heap)) {

            e = heap_pop(heap);
            
            execute_event(e, heap, board);
            while(e.moment == heap->values[0].moment){
                e = heap_pop(heap);
                execute_event(e, heap, board);
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
    free_heap(heap);
    restaure_stdin();

}