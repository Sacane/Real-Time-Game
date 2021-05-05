#include "../include/board.h"

/* a modifié en local*/

Player init_player(Coordonnees coordonnee, Direction dir_player){


    Player player; 
    Coordonnees coo_player; 
    coo_player.x = coordonnee.x;
    coo_player.y = coordonnee.y;
    Direction dir;
    dir = dir_player;
    player.depl_player_autorise = true;
    player.moment_depl_perso = 0;
    player.allure_perso = une_milliseconde * 50;

    return player;

}


Board malloc_board(Coordonnees size){

    Board board; 
    unsigned int i;

    board = (Board)malloc(sizeof(Game));
    board->box = (List_obj**)malloc(sizeof(List*) * size.x * size.y); 
    board->est_niveau_termine = false;
    for(i=0; i < size.x; i++){
        board->box[i] = (List_obj*)malloc(sizeof(List)*size.y);
    }
    return board;

}

void free_board(Board board){
    unsigned int i, j;

    for(i = 0; i < board->size.x; i++){
        for(j = 0; j < board->size.y; j++){
            if(board->box[i][j])
                free_list(board->box[i][j]);
        }
        free(board->box[i]);
    }
    free(board);
}

void init_board(Board board, Coordonnees size){

    unsigned int i, j;
    for(i = 0; i < size.x; i++){
        for(j = 0; j < size.y; j++){
            board->box[i][j] = NULL; 
        }
    }
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


void deplace_projectile_b(Board board, Coordonnees *coordonnees, Objet projectile){
    
    assert(board != NULL);
    assert(is_type_in_lst(board->box[coordonnees->x][coordonnees->y], PROJECTILE));
    assert(projectile.type == PROJECTILE);

    
    Deplacement* deplacement;
    
    deplacement = (Deplacement*)malloc(sizeof(Deplacement));

    memcpy(deplacement, projectile.donnee_suppl, sizeof(Deplacement));

    if(se_dirige_vers_obstacle(coordonnees->x, coordonnees->y, deplacement->direction, board)){
        free(deplacement);
        board->box[coordonnees->x][coordonnees->y] = delete_obj_in_list(board->box[coordonnees->x][coordonnees->y], projectile);
        return;
    }
    
    switch((deplacement)->direction){

        case HAUT:
            board->box[coordonnees->x][coordonnees->y] = delete_obj_in_list(board->box[coordonnees->x][coordonnees->y], projectile);

            add_obj_in_lst(&board->box[--coordonnees->x][coordonnees->y], projectile);
            break;
        case BAS:
            
            board->box[coordonnees->x][coordonnees->y] = delete_obj_in_list(board->box[coordonnees->x][coordonnees->y], projectile);
            add_obj_in_lst(&board->box[++coordonnees->x][coordonnees->y], projectile);
            
            break;
        case DROITE:

            board->box[coordonnees->x][coordonnees->y] = delete_obj_in_list(board->box[coordonnees->x][coordonnees->y], projectile);
            add_obj_in_lst(&board->box[coordonnees->x][++coordonnees->y], projectile);


            break;
        case GAUCHE:

            board->box[coordonnees->x][coordonnees->y] = delete_obj_in_list(board->box[coordonnees->x][coordonnees->y], projectile);
            add_obj_in_lst(&board->box[--coordonnees->x][--coordonnees->y], projectile);

            break;
    }
    if(est_coordonnee_equivalent((*coordonnees), board->player1.coo_player) || 
        est_coordonnee_equivalent((*coordonnees), board->player2.coo_player)){
        board->est_niveau_termine = false;
    }
}



int deplace_joueur_b(Board board, Objet player_obj, Player *player){

    assert(board != NULL);
    
    if(se_dirige_vers_obstacle((board->player1.coo_player).x, (board->player1.coo_player).y, board->player1.dir_player, board)){
        return -1;
    }
    delete_obj_in_list(board->box[player->coo_player.x][player->coo_player.y], player_obj);
    switch(player->dir_player){
        case HAUT:
            (player->coo_player).x -= 1;
            break;
        case BAS:
            (player->coo_player).x += 1;
            break; 
        case DROITE:
            (player->coo_player).y += 1;
            break;
        case GAUCHE:
            (player->coo_player).y -= 1;
            break;
    }
    if(is_type_in_lst(board->box[player->coo_player.x][player->coo_player.y], PROJECTILE)){
        printf("Vous avez marché sur un projectile, Boom !\n");
        return 0;
    }
    
    player->depl_player_autorise = false;
    (player->moment_depl_perso) = maintenant() + player->allure_perso;
    add_obj_in_lst(&board->box[player->coo_player.x][player->coo_player.y], player_obj);
    return 1;
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



