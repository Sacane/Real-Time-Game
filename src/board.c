#include "../include/board.h"

/* a modifié en local*/

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
    board->box = (Array**)malloc(sizeof(Objects*) * size.x * size.y); 
    board->est_niveau_termine = false;
    for(i=0; i < size.x; i++){
        board->box[i] = (Array*)malloc(sizeof(Objects)*size.y);
        for(j = 0; j < size.y; j++){
            board->box[i][j] = NULL;
        }
    }
    return board;

}

void free_board(Board board){
    unsigned int i, j;

    for(i = 0; i < board->size.x; i++){
        for(j = 0; j < board->size.y; j++){
            if(board->box[i][j])
                big_free_array(board->box[i][j]);
        }
        free(board->box[i]);
    }
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



