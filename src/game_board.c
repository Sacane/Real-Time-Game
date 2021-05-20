/**
 * \file game_board.c
 * \authors Ramaroson Rakotomihamina Johan && Li Christine
 * \date : 01-04-21
 * \last modification : 21-05-21
 * 
 * File containing the functions ---- 
 *
 */

#include "../include/game_board.h"
#include <string.h>


/**
 * \fn Board malloc_board (Coordinates size)
 * \brief Function to perform allocations to obtain a level of the given size 
 *
 * \param size : Coordinates, size of the board
 * \return Board, a game board
 */
Board malloc_board (Coordinates size){

    Board tmp;
    unsigned int i;

    tmp = (Board)malloc(sizeof(Level));
    verif_malloc(tmp);
    tmp->size = size;
    tmp->mulptiplayer_mode = false;
    tmp->is_game_over = false;
    tmp->objects = (Object**)malloc(sizeof(Object*) * size.y * size.x);
    verif_malloc(tmp->objects);
    for(i = 0; i < size.x; i++){
      tmp->objects[i] = (Object*)malloc(sizeof(Object) * size.y);
      verif_malloc(tmp->objects[i]);
    }
    return tmp;
}


/**
 * \fn void free_board (Board gameboard)
 * \brief Function that frees the memory taken by a level
 * \param gameboard : Board, level of the board
 */
void free_board (Board gameboard){
    
    unsigned int i, j;

    for(i = 0; i < gameboard->size.x; i++){
        for(j = 0; j < gameboard->size.y; j++){
            if(gameboard->objects[i][j].data)
                free(gameboard->objects[i][j].data);
                
        }
        free(gameboard->objects[i]);
    }
    
    free(gameboard->objects);
    free(gameboard);
}


/**
 * \fn Player init_player(Coordinates init_coo, Direction init_dir, unsigned long speed_player_init, TypeObject type)
 * \brief Function that initializes a player
 * \param init_coo : Coordinates, coordonates of the player
 * \param init_dir : Direction, direction of the player
 * \param speed_player_init : unsigned long, speed of the player
 * \param type : TypeObject
 * \return Player, a player
 */
Player init_player(Coordinates init_coo, Direction init_dir, unsigned long speed_player_init, TypeObject type){
    Player p;
    p.coo_player = init_coo;
    p.dir_player = init_dir;
    p.speed_player = speed_player_init;
    p.is_player_alive = true;
    p.can_player_move = true;
    p.typePlayer = type;
    p.has_player_win = false;
    return p;
}


/**
 * \fn void init_board(Board board, Coordinates size)
 * \brief Function that initializes a game level 
 * \param board : Board, a level of game
 * \param size : Coordinates, coordinates of the game board
 */
void init_board(Board board, Coordinates size){

    unsigned int i, j;
    for(i = 0; i < size.x; i++){
        for(j = 0; j < size.y; j++){
            board->objects[i][j].type = VIDE;
            board->objects[i][j].data = NULL;
        }
    }
}


/**
 * \fn void affiche_coordonnee(Coordinates coordonnee)
 * \brief Function to print coordinates
 * \param coordinate : Coordinate to print in the stdout
 */
void affiche_coordonnee(Coordinates coordonnee){
    printf("(%u, %u)", coordonnee.x, coordonnee.y);
}


/**
 * \fn bool equals_coordinates(Coordinates first, Coordinates second)
 * \brief Function that verify if two coordinates are equals or not
 * \param first : Coordinates, the first coordinate to compare
 * \param second : Coordinates, the second coordinate to compare
 * \return bool, true if both of the coordinates are equals, false otherwise
 */
bool equals_coordinates(Coordinates first, Coordinates second){
    return (first.y == second.y) && (first.x == second.x);
}


/**
 * \fn bool is_object_going_to_crash(unsigned int x, unsigned int y, Direction direction, Board board)
 * \brief Function to check if an object is heading towards the wall 
 * \param x : unsigned int, coordinate x of the position of the object to analize
 * \param y : unsigned int, coordinate y of the position of the object to analize
 * \param direction : Direction, the direction of the object 
 * \param board : Board, a gameboard 
 * \return bool, true if the object is heading towards the well, false otherwise
 */
bool is_object_going_to_crash(unsigned int x, unsigned int y, Direction direction, Board board){
    
    if((x <= 0 && direction == NORTH) || (x >= board->size.x-1 && direction == SOUTH)||
    (y <= 0 && direction == WEST) || (y >= board->size.y - 1 && direction == EAST)){
        
        return true;
    }
    switch(direction){
        case NORTH:
            if(board->objects[x-1][y].type == WALL || 
            board->objects[x-1][y].type == DOOR){
                return true;
            }
            break;
        case SOUTH:
            if(board->objects[x+1][y].type == WALL || 
            board->objects[x+1][y].type == DOOR){
                return true;
            }
            break;
        case WEST:
            if(board->objects[x][y-1].type == WALL || 
            board->objects[x][y-1].type == DOOR){
                return true;
            }
            break;
        case EAST:
            if(board->objects[x][y+1].type == WALL || 
            board->objects[x][y+1].type == DOOR){
                return true;
            }
            break;
    }

    return false;

}




/**
 * \fn bool going_to_obj(Board board, Player player, TypeObject type)
 * \brief Check if the next case where the player is going in its next move
 * \param type : TypeObject to check the next case's type
 * \param player : Player to check its direction 
 * \param board : Board, a game board
 * \return true if the player goes to an object, false otherwise
*/
bool going_to_obj(Board board, Player player, TypeObject type){
    switch(player.dir_player){
        case NORTH:
            if(board->objects[player.coo_player.x - 1][player.coo_player.y].type == type){
                return true;
            }
            break;
        case SOUTH:
            if(board->objects[player.coo_player.x + 1][player.coo_player.y].type == type){
                return true;
            }
            break;
        case WEST:
            if(board->objects[player.coo_player.x][player.coo_player.y - 1].type == type){
                return true;
            }
            break;
        case EAST:
            if(board->objects[player.coo_player.x][player.coo_player.y + 1].type == type){
                return true;
            }
            break;
    }
    return false;
}


/**
 * \fn void move_projectile(Board board, Coordinates *coordinate)
 * \brief Function to move a projectile 
 * \param board : Board, a game board
 * \param coordinates : Coordinates*, coordinates of the projectile
 */
void move_projectile(Board board, Coordinates *coordinate){
    
    assert(board != NULL);
    assert(board->objects[coordinate->x][coordinate->y].type == PROJECTILE);
    
    Deplacement* deplacement;
    
    deplacement = (Deplacement*)malloc(sizeof(Deplacement));
    verif_malloc(deplacement);
    memcpy(deplacement, board->objects[coordinate->x][coordinate->y].data, sizeof(Deplacement));

    if(is_object_going_to_crash(coordinate->x, coordinate->y, deplacement->direction, board)){
        free(deplacement);
        board->objects[coordinate->x][coordinate->y].type = VIDE;

        return;
    }
    
    switch((deplacement)->direction){

        case NORTH:

            board->objects[--coordinate->x][coordinate->y].type = PROJECTILE;
            board->objects[coordinate->x][coordinate->y].data = deplacement;
            fill_projectile(&board->objects[coordinate->x][coordinate->y], deplacement);
            board->objects[coordinate->x + 1][coordinate->y].type = VIDE;

            break;
        case SOUTH:
            
            board->objects[++coordinate->x][coordinate->y].type = PROJECTILE;
            board->objects[coordinate->x][coordinate->y].data = deplacement;
            fill_projectile(&board->objects[coordinate->x][coordinate->y], deplacement);
            
            board->objects[coordinate->x - 1][coordinate->y].type = VIDE;

            
            break;
        case EAST:
            
            board->objects[coordinate->x][++coordinate->y].type = PROJECTILE;
            board->objects[coordinate->x][coordinate->y].data = deplacement;
            fill_projectile(&board->objects[coordinate->x][coordinate->y], deplacement);
            board->objects[coordinate->x][coordinate->y - 1].type = VIDE;

            break;
        case WEST:
            board->objects[coordinate->x][--coordinate->y].type = PROJECTILE;
            board->objects[coordinate->x][coordinate->y].data = deplacement;
            fill_projectile(&board->objects[coordinate->x][coordinate->y], deplacement);
            board->objects[coordinate->x][coordinate->y + 1].type = VIDE;
		
            break;
    }

    if(equals_coordinates(*coordinate, board->p1.coo_player)){
        board->p1.is_player_alive = false;
    }
    if(board->mulptiplayer_mode){
        
        if(equals_coordinates(*coordinate, board->p2.coo_player)){
            printf("EQUALS multiplayer\n");
            board->p2.is_player_alive = false;
        }
    }

}


/**
 * \fn bool check_victory(Board board)
 * \brief Check if the player(s) won the game according to the state of the board
 * \param board : Board, a game board 
 * \return true if the game is win, false if not
*/
bool check_victory(Board board){
    if(board->mulptiplayer_mode){
        if(board->p1.has_player_win && board->p2.has_player_win){
            return true;
        }
    }
    else{
        if(board->p1.has_player_win){
            return true;
        }
    }
    return false;
}


/**
 * \fn bool check_game_over(Board board)
 * \brief Check if the game is over according to the state of the board
 * \param board : Board, a gameboard 
 * \return true if the game is lost, false if not.
*/
bool check_game_over(Board board){
    return (board->mulptiplayer_mode) ? (!board->p1.is_player_alive || !board->p2.is_player_alive) : (!board->p1.is_player_alive);
}


/**
 * \fn int move_players(Board board, Player *player){
    assert(board != NULL)
 * \brief Function that moves a player
 * \param board : Board, a game board 
 * \param player : Player*, a player
 * \return int 
*/
int move_players(Board board, Player *player){
    assert(board != NULL);

    Trigger *trigger;
    
    if(is_object_going_to_crash(player->coo_player.x, player->coo_player.y, player->dir_player, board)){
        return -1;
    }
    if(board->objects[player->coo_player.x][player->coo_player.y].type == DESTINATION){
        return -1;
    }
    
    board->objects[player->coo_player.x][player->coo_player.y].type = VIDE;
    switch(player->dir_player){
        case NORTH:
            player->coo_player.x -= 1;
            break;
        case SOUTH:
            player->coo_player.x += 1;
            break; 
        case EAST:
            player->coo_player.y += 1;
            break;
        case WEST:
            player->coo_player.y -= 1;
            break;
    }
    
    if(board->objects[player->coo_player.x][player->coo_player.y].type == PROJECTILE){
        printf("You just walk into a projectile ! Game OVER.\n");
        player->is_player_alive = false;
        return 0;
    }
    if(board->objects[player->coo_player.x][player->coo_player.y].type == SWITCH){
        trigger = (Trigger*)malloc(sizeof(Trigger));
        verif_malloc(trigger);
        memcpy(trigger, board->objects[player->coo_player.x][player->coo_player.y].data, sizeof(Trigger));
        board->objects[trigger->coo_door.x][trigger->coo_door.y].type = VIDE;

        free(trigger);
    }
    if(board->objects[player->coo_player.x][player->coo_player.y].type != DESTINATION){
        board->objects[player->coo_player.x][player->coo_player.y].type = player->typePlayer;
    }
    else{
        
        return -1;
    }
    player->can_player_move = false;
    player->moment_depl_player = maintenant() + player->speed_player;
    return 1;
}


/**
 * \fn void check_player_move(Player *p)
 * \brief Function that verify the player's movement
 * \param p : Player *, board for the player's movement
 */
void check_player_move(Player *p){
    if(maintenant() >= p->moment_depl_player){
        p->can_player_move = true;
    }
}


/**
 * \fn bool check_player_reached(Board board)
 * \brief Function to check if a level has been passed / reached
 * \param board : Board, a game board
 * \return bool, true if the level has been reached, false otherwise
 */
bool check_player_reached(Board board){
    return (!board->mulptiplayer_mode) ? (equals_coordinates(board->p1.coo_player, board->coo_destination)) : (equals_coordinates(board->p1.coo_player, board->coo_destination) && (equals_coordinates(board->p2.coo_player, board->coo_destination)));
}


/**
 * \fn void trigger_switch(Board board, Player player)
 * \param board : Board, to update after trigger the switch
 * \param player : Player, a player  
*/
void trigger_switch(Board board, Player player){
    Trigger *trigger;
    trigger = (Trigger*)malloc(sizeof(Trigger));
    verif_malloc(trigger);
    switch(player.dir_player){
        case NORTH:
            memcpy(trigger, board->objects[player.coo_player.x - 1][player.coo_player.y].data, sizeof(Trigger));
            break;
        case SOUTH:
            memcpy(trigger, board->objects[player.coo_player.x + 1][player.coo_player.y].data, sizeof(Trigger));
            break;
        case EAST:
            memcpy(trigger, board->objects[player.coo_player.x][player.coo_player.y + 1].data, sizeof(Trigger));
            break;
        case WEST:
            memcpy(trigger, board->objects[player.coo_player.x][player.coo_player.y - 1].data, sizeof(Trigger));
            break;
    }
    board->objects[trigger->coo_door.x][trigger->coo_door.y].type = VIDE;

    board->objects[trigger->coo_door.x][trigger->coo_door.y].data = NULL;
    free(trigger);
}


/**
 * \fn void print_board (Board board)
 * \brief Function that print in the terminal the level given in argument
 * \param board : Board, the game board
 */
void print_board (Board board) {

	unsigned int i, j;
    Deplacement *dep;
	for(i = 0; i < board->size.x ; i++) {
		for(j = 0; j < board->size.y; j++) {

			switch (board->objects[i][j].type)
			{
			case VIDE: 
				printf(".");
				break;
			case LAUNCHER: 
				printf("O");
				break;
			case WALL: 
				printf("#");
				break;
			
			case PROJECTILE: 
                dep = board->objects[i][j].data;
				switch (dep->direction)
				{
				case NORTH: 
					printf("^");
					break;
				case WEST:
					printf("<");
					break;
				case SOUTH: 
					printf("v");
					break;
				case EAST: 
					printf(">");
					break;
				}
				break;

            case PLAYER1:
            case PLAYER2:
				printf("P");
				break;
			case DESTINATION:
				printf("D");
				break;
            case SWITCH:
                printf("I");
                break;
            case DOOR:
                printf("§");
                break;
			default:
				printf(".");
				break;
			}

		}
		printf("\n");
	}
}


