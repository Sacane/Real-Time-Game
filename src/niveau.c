#include "../include/niveau.h"
#include <string.h>

Board malloc_board (Coordonnees taille){

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
            if(gameboard->objets[i][j].donnee_suppl)
                free(gameboard->objets[i][j].donnee_suppl);
                
        }
        free(gameboard->objets[i]);
    }
    
    free(gameboard->objets);
    free(gameboard);
}

Player init_player(Coordonnees init_coo, Direction init_dir, unsigned long speed_player_init, TypeObjet type){
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

void init_board(Board niveau, Coordonnees taille){

    unsigned int i, j;
    for(i = 0; i < taille.x; i++){
        for(j = 0; j < taille.y; j++){
            niveau->objets[i][j].type = VIDE;
            niveau->objets[i][j].donnee_suppl = NULL;
        }
    }
}


void affiche_coordonnee(Coordonnees coordonnee){
    printf("(%u, %u)", coordonnee.x, coordonnee.y);
}

bool est_coordonnee_equivalent(Coordonnees first, Coordonnees second){
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

void deplace_projectile(Board niveau, Coordonnees *coordonnees){
    
    assert(niveau != NULL);
    assert(niveau->objets[coordonnees->x][coordonnees->y].type == PROJECTILE);
    
    Deplacement* deplacement;
    
    deplacement = (Deplacement*)malloc(sizeof(Deplacement));

    memcpy(deplacement, niveau->objets[coordonnees->x][coordonnees->y].donnee_suppl, sizeof(Deplacement));

    if(se_dirige_vers_mur(coordonnees->x, coordonnees->y, deplacement->direction, niveau)){
        free(deplacement);
        niveau->objets[coordonnees->x][coordonnees->y].type = VIDE;

        return;
    }
    
    switch((deplacement)->direction){

        case NORTH:

            niveau->objets[--coordonnees->x][coordonnees->y].type = PROJECTILE;
            niveau->objets[coordonnees->x][coordonnees->y].donnee_suppl = deplacement;
            remplis_projectile(&niveau->objets[coordonnees->x][coordonnees->y], deplacement);
            niveau->objets[coordonnees->x + 1][coordonnees->y].type = VIDE;

            break;
        case SOUTH:
            
            niveau->objets[++coordonnees->x][coordonnees->y].type = PROJECTILE;
            niveau->objets[coordonnees->x][coordonnees->y].donnee_suppl = deplacement;
            remplis_projectile(&niveau->objets[coordonnees->x][coordonnees->y], deplacement);
            
            niveau->objets[coordonnees->x - 1][coordonnees->y].type = VIDE;

            
            break;
        case EAST:
            
            niveau->objets[coordonnees->x][++coordonnees->y].type = PROJECTILE;
            niveau->objets[coordonnees->x][coordonnees->y].donnee_suppl = deplacement;
            remplis_projectile(&niveau->objets[coordonnees->x][coordonnees->y], deplacement);
            niveau->objets[coordonnees->x][coordonnees->y - 1].type = VIDE;

            break;
        case WEST:
            niveau->objets[coordonnees->x][--coordonnees->y].type = PROJECTILE;
            niveau->objets[coordonnees->x][coordonnees->y].donnee_suppl = deplacement;
            remplis_projectile(&niveau->objets[coordonnees->x][coordonnees->y], deplacement);
            niveau->objets[coordonnees->x][coordonnees->y + 1].type = VIDE;
		
            break;
    }

    if(est_coordonnee_equivalent(*coordonnees, niveau->p1.coo_player)){
        niveau->p1.is_player_alive = false;
    }
    if(niveau->mulptiplayer_mode){
        
        if(est_coordonnee_equivalent(*coordonnees, niveau->p2.coo_player)){
            printf("EQUALS multiplayer\n");
            niveau->p2.is_player_alive = false;
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

int move_players(Board niveau, Player *player){
    assert(niveau != NULL);

    Trigger *trigger;
    
    if(se_dirige_vers_mur(player->coo_player.x, player->coo_player.y, player->dir_player, niveau)){
        return -1;
    }
    if(niveau->objets[player->coo_player.x][player->coo_player.y].type == DESTINATION){
        return -1;
    }
    
    niveau->objets[player->coo_player.x][player->coo_player.y].type = VIDE;
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
    
    if(niveau->objets[player->coo_player.x][player->coo_player.y].type == PROJECTILE){
        printf("You just walk into a projectile ! Game OVER.\n");
        player->is_player_alive = false;
        return 0;
    }
    if(niveau->objets[player->coo_player.x][player->coo_player.y].type == SWITCH){
        trigger = (Trigger*)malloc(sizeof(Trigger));
        memcpy(trigger, niveau->objets[player->coo_player.x][player->coo_player.y].donnee_suppl, sizeof(Trigger));
        niveau->objets[trigger->coo_door.x][trigger->coo_door.y].type = VIDE;

        free(trigger);
    }
    if(niveau->objets[player->coo_player.x][player->coo_player.y].type != DESTINATION){
        niveau->objets[player->coo_player.x][player->coo_player.y].type = player->typePlayer;
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

bool check_player_reached(Board niveau){
    return (!niveau->mulptiplayer_mode) ? (est_coordonnee_equivalent(niveau->p1.coo_player, niveau->coo_destination)) : (est_coordonnee_equivalent(niveau->p1.coo_player, niveau->coo_destination) && (est_coordonnee_equivalent(niveau->p2.coo_player, niveau->coo_destination)));
}

void trigger_switch(Board board, Player player){
    Trigger *trigger;
    trigger = (Trigger*)malloc(sizeof(Trigger));
    switch(player.dir_player){
        case NORTH:
            memcpy(trigger, board->objets[player.coo_player.x - 1][player.coo_player.y].donnee_suppl, sizeof(Trigger));
            break;
        case SOUTH:
            memcpy(trigger, board->objets[player.coo_player.x + 1][player.coo_player.y].donnee_suppl, sizeof(Trigger));
            break;
        case EAST:
            memcpy(trigger, board->objets[player.coo_player.x][player.coo_player.y + 1].donnee_suppl, sizeof(Trigger));
            break;
        case WEST:
            memcpy(trigger, board->objets[player.coo_player.x][player.coo_player.y - 1].donnee_suppl, sizeof(Trigger));
            break;
    }
    board->objets[trigger->coo_door.x][trigger->coo_door.y].type = VIDE;

    board->objets[trigger->coo_door.x][trigger->coo_door.y].donnee_suppl = NULL;
    free(trigger);
}

void print_board (Board niveau) {

	unsigned int i, j;
    Deplacement *dep;
	for(i = 0; i < niveau->taille.x ; i++) {
		for(j = 0; j < niveau->taille.y; j++) {

			switch (niveau->objets[i][j].type)
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
                dep = niveau->objets[i][j].donnee_suppl;
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


