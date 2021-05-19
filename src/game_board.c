#include "../include/game_board.h"
#include <string.h>

Board malloc_board (Coordinates taille){

    Board tmp;
    unsigned int i;

    tmp = (Board)malloc(sizeof(Level));
    tmp->taille = taille;
    tmp->mulptiplayer_mode = false;
    tmp->is_game_over = false;
    tmp->objets = (Objet**)malloc(sizeof(Objet*) * taille.y * taille.x);
    for(i = 0; i < taille.x; i++){
      tmp->objets[i] = (Objet*)malloc(sizeof(Objet) * taille.y);
    }
    return tmp;
}

void free_board (Board gameboard){
    
    unsigned int i, j;

    for(i = 0; i < gameboard->taille.x; i++){
        for(j = 0; j < gameboard->taille.y; j++){
            if(gameboard->objets[i][j].data)
                free(gameboard->objets[i][j].data);
                
        }
        free(gameboard->objets[i]);
    }
    
    free(gameboard->objets);
    free(gameboard);
}

Player init_player(Coordinates init_coo, Direction init_dir, unsigned long speed_player_init, TypeObjet type){
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

void init_board(Board board, Coordinates taille){

    unsigned int i, j;
    for(i = 0; i < taille.x; i++){
        for(j = 0; j < taille.y; j++){
            board->objets[i][j].type = VIDE;
            board->objets[i][j].data = NULL;
        }
    }
}


void affiche_coordonnee(Coordinates coordonnee){
    printf("(%u, %u)", coordonnee.x, coordonnee.y);
}

bool equals_coordinates(Coordinates first, Coordinates second){
    return (first.y == second.y) && (first.x == second.x);
}

bool se_dirige_vers_mur(unsigned int x, unsigned int y, Direction direction, Board board){
    
    if((x <= 0 && direction == NORTH) || (x >= board->taille.x-1 && direction == SOUTH)||
    (y <= 0 && direction == WEST) || (y >= board->taille.y - 1 && direction == EAST)){
        
        return true;
    }
    switch(direction){
        case NORTH:
            if(board->objets[x-1][y].type == WALL || 
            board->objets[x-1][y].type == DOOR){
                return true;
            }
            break;
        case SOUTH:
            if(board->objets[x+1][y].type == WALL || 
            board->objets[x+1][y].type == DOOR){
                return true;
            }
            break;
        case WEST:
            if(board->objets[x][y-1].type == WALL || 
            board->objets[x][y-1].type == DOOR){
                return true;
            }
            break;
        case EAST:
            if(board->objets[x][y+1].type == WALL || 
            board->objets[x][y+1].type == DOOR){
                return true;
            }
            break;
    }

    return false;
}

bool going_to_switch(Board board, Player player){

    switch(player.dir_player){
        case NORTH:
            if(board->objets[player.coo_player.x - 1][player.coo_player.y].type == SWITCH){
                return true;
            }
            break;
        case SOUTH:
            if(board->objets[player.coo_player.x + 1][player.coo_player.y].type == SWITCH){
                return true;
            }
            break;
        case WEST:
            if(board->objets[player.coo_player.x][player.coo_player.y - 1].type == SWITCH){
                return true;
            }
            break;
        case EAST:
            if(board->objets[player.coo_player.x][player.coo_player.y + 1].type == SWITCH){
                return true;
            }
            break;
    }
    return false;
}

bool going_to_obj(Board board, Player player, TypeObjet type){
    switch(player.dir_player){
        case NORTH:
            if(board->objets[player.coo_player.x - 1][player.coo_player.y].type == type){
                return true;
            }
            break;
        case SOUTH:
            if(board->objets[player.coo_player.x + 1][player.coo_player.y].type == type){
                return true;
            }
            break;
        case WEST:
            if(board->objets[player.coo_player.x][player.coo_player.y - 1].type == type){
                return true;
            }
            break;
        case EAST:
            if(board->objets[player.coo_player.x][player.coo_player.y + 1].type == type){
                return true;
            }
            break;
    }
    return false;
}

void move_projectile(Board board, Coordinates *coordinate){
    
    assert(board != NULL);
    assert(board->objets[coordinate->x][coordinate->y].type == PROJECTILE);
    
    Deplacement* deplacement;
    
    deplacement = (Deplacement*)malloc(sizeof(Deplacement));

    memcpy(deplacement, board->objets[coordinate->x][coordinate->y].data, sizeof(Deplacement));

    if(se_dirige_vers_mur(coordinate->x, coordinate->y, deplacement->direction, board)){
        free(deplacement);
        board->objets[coordinate->x][coordinate->y].type = VIDE;

        return;
    }
    
    switch((deplacement)->direction){

        case NORTH:

            board->objets[--coordinate->x][coordinate->y].type = PROJECTILE;
            board->objets[coordinate->x][coordinate->y].data = deplacement;
            fill_projectile(&board->objets[coordinate->x][coordinate->y], deplacement);
            board->objets[coordinate->x + 1][coordinate->y].type = VIDE;

            break;
        case SOUTH:
            
            board->objets[++coordinate->x][coordinate->y].type = PROJECTILE;
            board->objets[coordinate->x][coordinate->y].data = deplacement;
            fill_projectile(&board->objets[coordinate->x][coordinate->y], deplacement);
            
            board->objets[coordinate->x - 1][coordinate->y].type = VIDE;

            
            break;
        case EAST:
            
            board->objets[coordinate->x][++coordinate->y].type = PROJECTILE;
            board->objets[coordinate->x][coordinate->y].data = deplacement;
            fill_projectile(&board->objets[coordinate->x][coordinate->y], deplacement);
            board->objets[coordinate->x][coordinate->y - 1].type = VIDE;

            break;
        case WEST:
            board->objets[coordinate->x][--coordinate->y].type = PROJECTILE;
            board->objets[coordinate->x][coordinate->y].data = deplacement;
            fill_projectile(&board->objets[coordinate->x][coordinate->y], deplacement);
            board->objets[coordinate->x][coordinate->y + 1].type = VIDE;
		
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

bool check_game_over(Board board){
    return (board->mulptiplayer_mode) ? (!board->p1.is_player_alive || !board->p2.is_player_alive) : (!board->p1.is_player_alive);
}

int move_players(Board board, Player *player){
    assert(board != NULL);

    Trigger *trigger;
    
    if(se_dirige_vers_mur(player->coo_player.x, player->coo_player.y, player->dir_player, board)){
        return -1;
    }
    if(board->objets[player->coo_player.x][player->coo_player.y].type == DESTINATION){
        return -1;
    }
    
    board->objets[player->coo_player.x][player->coo_player.y].type = VIDE;
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
    
    if(board->objets[player->coo_player.x][player->coo_player.y].type == PROJECTILE){
        printf("You just walk into a projectile ! Game OVER.\n");
        player->is_player_alive = false;
        return 0;
    }
    if(board->objets[player->coo_player.x][player->coo_player.y].type == SWITCH){
        trigger = (Trigger*)malloc(sizeof(Trigger));
        memcpy(trigger, board->objets[player->coo_player.x][player->coo_player.y].data, sizeof(Trigger));
        board->objets[trigger->coo_door.x][trigger->coo_door.y].type = VIDE;

        free(trigger);
    }
    if(board->objets[player->coo_player.x][player->coo_player.y].type != DESTINATION){
        board->objets[player->coo_player.x][player->coo_player.y].type = player->typePlayer;
    }
    else{
        
        return -1;
    }
    player->can_player_move = false;
    player->moment_depl_player = maintenant() + player->speed_player;
    return 1;
}

void check_player_move(Player *p){
    if(maintenant() >= p->moment_depl_player){
        p->can_player_move = true;
    }
}

bool check_player_reached(Board board){
    return (!board->mulptiplayer_mode) ? (equals_coordinates(board->p1.coo_player, board->coo_destination)) : (equals_coordinates(board->p1.coo_player, board->coo_destination) && (equals_coordinates(board->p2.coo_player, board->coo_destination)));
}

void trigger_switch(Board board, Player player){
    Trigger *trigger;
    trigger = (Trigger*)malloc(sizeof(Trigger));
    switch(player.dir_player){
        case NORTH:
            memcpy(trigger, board->objets[player.coo_player.x - 1][player.coo_player.y].data, sizeof(Trigger));
            break;
        case SOUTH:
            memcpy(trigger, board->objets[player.coo_player.x + 1][player.coo_player.y].data, sizeof(Trigger));
            break;
        case EAST:
            memcpy(trigger, board->objets[player.coo_player.x][player.coo_player.y + 1].data, sizeof(Trigger));
            break;
        case WEST:
            memcpy(trigger, board->objets[player.coo_player.x][player.coo_player.y - 1].data, sizeof(Trigger));
            break;
    }
    board->objets[trigger->coo_door.x][trigger->coo_door.y].type = VIDE;

    board->objets[trigger->coo_door.x][trigger->coo_door.y].data = NULL;
    free(trigger);
}

void print_board (Board board) {

	unsigned int i, j;
    Deplacement *dep;
	for(i = 0; i < board->taille.x ; i++) {
		for(j = 0; j < board->taille.y; j++) {

			switch (board->objets[i][j].type)
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
                dep = board->objets[i][j].data;
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


