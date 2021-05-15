#include "../include/board.h"



Player init_player(Coordonnees coordonnee, Direction dir_player){


    Player player; 

    player.dir_player = dir_player;
    player.depl_player_autorise = true;
    player.moment_depl_perso = 0;
    player.allure_perso = une_milliseconde * 50;
    player.coo_player = coordonnee;
    return player;

}


Board malloc_board(Coordonnees size){
    
    Board board; 
    unsigned int i, j;
    
    board = (Board)malloc(sizeof(Game));
    board->size = size;
    board->box = (Array**)malloc(sizeof(Objects*) * size.x * size.y); 
    board->est_niveau_termine = false;
    for(i=0; i < size.x; i++){
        board->box[i] = (Array*)malloc(sizeof(Objects)*size.y);
        for(j = 0; j < size.y; j++){
            board->box[i][j] = NULL;
            board->box[i][j] = malloc_arr_objects(ARR_SIZE);
        }
    }
    return board;

}

void free_board(Board board){
    unsigned int i, j;

    for(i = 0; i < board->size.x; i++){
        for(j = 0; j < board->size.y; j++){
            big_free_array(board->box[i][j]);
        }
        free(board->box[i]);
    }
    free(board->box);
    free(board);
}



bool se_dirige_vers_obstacle(unsigned int x, unsigned int y, Direction direction, Board board){
    if((x <= 0 && direction == HAUT) || (x >= board->size.x-1 && direction == BAS)||
    (y <= 0 && direction == GAUCHE) || (y >= board->size.y - 1 && direction == DROITE)){
        return true;
    }
    switch(direction){
        case HAUT:
            if(is_type_in_lst((board->box[x-1][y]), MUR)){
                return true;
            }
            break;
        case BAS:
            if(is_type_in_lst(board->box[x+1][y], MUR)){
                return true;
            }
            break;
        case GAUCHE:
            if(is_type_in_lst(board->box[x][y-1], MUR)){
                return true;
            }
            break;
        case DROITE:
            if(is_type_in_lst(board->box[x][y+1], MUR)){
                return true;
            }
            break;
    }

    return false;
}

bool is_object_moveable(Coordonnees coo_obj, Direction direction, Board board){
    printf("enter\n");
    if((coo_obj.x <= 0 && direction == HAUT) || (coo_obj.x >= board->size.x-1 && direction == BAS)||
    (coo_obj.y <= 0 && direction == GAUCHE) || (coo_obj.y >= board->size.y - 1 && direction == DROITE)){
        return false;
    }

    switch(direction){
        case HAUT:
            if(is_wall_in_box((board->box[coo_obj.x-1][coo_obj.y]))){
                return false;
            }
            break;
        case BAS:
            if(is_wall_in_box(board->box[coo_obj.x+1][coo_obj.y])){
                return false;
            }
            break;
        case GAUCHE:
            if(is_wall_in_box(board->box[coo_obj.x][coo_obj.y-1])){
                return false;
            }
            break;
        case DROITE:
            if(is_wall_in_box(board->box[coo_obj.x][coo_obj.y+1])){
                return false;
            }
            break;
    }
    printf("end objet_movable\n");
    return true;
}

int move_projectile(Board gameboard, Coordonnees *coo_proj, unsigned int index){
    assert(gameboard != NULL);
    assert(index <= gameboard->box[coo_proj->x][coo_proj->y]->size);
    assert(gameboard->box[coo_proj->x][coo_proj->y]->obj[index].type == PROJECTILE);
    int new_index;
    Deplacement* deplacement;
    deplacement = (Deplacement*)malloc(sizeof(Deplacement));

    memcpy(deplacement, gameboard->box[coo_proj->x][coo_proj->y]->obj[index].donnee_suppl, sizeof(Deplacement));

    Objet projectile = extract_object_in_array(gameboard->box[coo_proj->x][coo_proj->y], index);
    
    if(!is_object_moveable(*coo_proj, deplacement->direction, gameboard)){
        free(deplacement);
        return -1;
    }

    switch((deplacement)->direction){

        case HAUT:
        
            new_index = add_object_in_array(gameboard->box[--coo_proj->x][coo_proj->y], projectile);

            break;
        case BAS:
        
            new_index = add_object_in_array(gameboard->box[++coo_proj->x][coo_proj->y], projectile);
            
            break;
        case DROITE:

            new_index = add_object_in_array(gameboard->box[coo_proj->x][++coo_proj->y], projectile);

            break;
        case GAUCHE:
            
            new_index = add_object_in_array(gameboard->box[coo_proj->x][--coo_proj->y], projectile);
		
            break;
    }
    free(deplacement);
    return new_index;
}

void check_movement_players(Board board){

	assert(NULL != board);

	if(maintenant() >= board->player1.moment_depl_perso){
		board->player1.depl_player_autorise = true;
	}
}



/**
 * \arg niveau : plateau concernant le déplacement du joueur
 * Deplace le joueur selon une direction renseigné
 * \return true si le personnage ne meurt pas après son déplacement, false sinon.
 */
int move_player(Board board, Player *player){

    int index;
    Objet obj_player;
    if(!is_object_moveable(player->coo_player, player->dir_player, board)){
        return -1;
    }
    obj_player = extract_object_in_array(board->box[player->coo_player.x][player->coo_player.y], player->index);
    switch(player->dir_player){
        case GAUCHE:
            player->coo_player.y -= 1;
            break;
        case DROITE:
            player->coo_player.y += 1;
            break;
        case BAS:
            player->coo_player.x += 1;
            break;
        case HAUT:
            player->coo_player.x -= 1;
            break;
    }
    if(is_type_in_lst(board->box[player->coo_player.x][player->coo_player.y], PROJECTILE)){
        printf("Vous avez marché sur un projectile, BOOM !\n");
        return 0;
    }
    index = add_object_in_array(board->box[player->coo_player.x][player->coo_player.y], obj_player);
    player->depl_player_autorise = false;
    player->moment_depl_perso = maintenant() + player->allure_perso;
    player->index = (unsigned int)index;
    return 1;
}

bool check_level_reached_b(Board board, Player player){
    
    return est_coordonnee_equivalent(player.coo_player, board->coo_destination);
}


/*void verifie_mouvement_personnage(Player *player){

	if(maintenant() >= player->moment_depl_perso){
		player->moment_depl_perso = true;
	}
}

bool check_level_reached(Board board){
    assert(board != NULL);
    
    return est_coordonnee_equivalent(board->player1.coo_player, board->coo_destination) ||
    est_coordonnee_equivalent(board->player2.coo_player, board->coo_destination);
}*/



