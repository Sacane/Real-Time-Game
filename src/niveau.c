#include "../include/niveau.h"
#include <string.h>

Plateau malloc_Niveau (Coordonnees taille){

    Plateau tmp;
    unsigned int i;

    tmp = (Plateau)malloc(sizeof(Niveau));
    tmp->taille = taille;
    tmp->mulptiplayer_mode = false;
    tmp->is_game_over = false;
    tmp->objets = (Objet**)malloc(sizeof(Objet*) * taille.y * taille.x);
    for(i = 0; i < taille.x; i++){
      tmp->objets[i] = (Objet*)malloc(sizeof(Objet) * taille.y);
    }
    return tmp;
}



void free_Niveau (Plateau niveau){
    
    unsigned int i, j;

    for(i = 0; i < niveau->taille.x; i++){
        for(j = 0; j < niveau->taille.y; j++){
            if(niveau->objets[i][j].donnee_suppl)
                free(niveau->objets[i][j].donnee_suppl);
        }
        free(niveau->objets[i]);
    }
    
    free(niveau->objets);
    free(niveau);
}

Player init_player(Coordonnees init_coo, Direction init_dir, unsigned long speed_player_init, TypeObjet type){
    Player p;
    p.coo_player = init_coo;
    p.dir_player = init_dir;
    p.speed_player = speed_player_init;
    p.is_player_alive = true;
    p.can_player_move = true;
    p.typePlayer = type;
    return p;
}

void init_niveaux(Plateau niveau, Coordonnees taille){

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

bool se_dirige_vers_mur(unsigned int x, unsigned int y, Direction direction, Plateau plateau){
    if((x <= 0 && direction == HAUT) || (x >= plateau->taille.x-1 && direction == BAS)||
    (y <= 0 && direction == GAUCHE) || (y >= plateau->taille.y - 1 && direction == DROITE)){
        return true;
    }
    switch(direction){
        case HAUT:
            if(plateau->objets[x-1][y].type == MUR){
                return true;
            }
            break;
        case BAS:
            if(plateau->objets[x+1][y].type == MUR){
                return true;
            }
            break;
        case GAUCHE:
            if(plateau->objets[x][y-1].type == MUR){
                return true;
            }
            break;
        case DROITE:
            if(plateau->objets[x][y+1].type == MUR){
                return true;
            }
            break;
    }

    return false;
}

bool going_to_switch(Plateau board, Player player){

    switch(player.dir_player){
        case HAUT:
            if(board->objets[player.coo_player.x - 1][player.coo_player.y].type == SWITCH){
                return true;
            }
            break;
        case BAS:
            if(board->objets[player.coo_player.x + 1][player.coo_player.y].type == SWITCH){
                return true;
            }
            break;
        case GAUCHE:
            if(board->objets[player.coo_player.x][player.coo_player.y - 1].type == SWITCH){
                return true;
            }
            break;
        case DROITE:
            if(board->objets[player.coo_player.x][player.coo_player.y + 1].type == SWITCH){
                return true;
            }
            break;
    }
    return false;
}

bool going_to_obj(Plateau board, Player player, TypeObjet type){
    switch(player.dir_player){
        case HAUT:
            if(board->objets[player.coo_player.x - 1][player.coo_player.y].type == type){
                return true;
            }
            break;
        case BAS:
            if(board->objets[player.coo_player.x + 1][player.coo_player.y].type == type){
                return true;
            }
            break;
        case GAUCHE:
            if(board->objets[player.coo_player.x][player.coo_player.y - 1].type == type){
                return true;
            }
            break;
        case DROITE:
            if(board->objets[player.coo_player.x][player.coo_player.y + 1].type == type){
                return true;
            }
            break;
    }
    return false;
}

void deplace_projectile(Plateau niveau, Coordonnees *coordonnees){
    
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

        case HAUT:

            niveau->objets[--coordonnees->x][coordonnees->y].type = PROJECTILE;
            niveau->objets[coordonnees->x][coordonnees->y].donnee_suppl = deplacement;
            remplis_projectile(&niveau->objets[coordonnees->x][coordonnees->y], deplacement);
            niveau->objets[coordonnees->x + 1][coordonnees->y].type = VIDE;

            break;
        case BAS:
            
            niveau->objets[++coordonnees->x][coordonnees->y].type = PROJECTILE;
            niveau->objets[coordonnees->x][coordonnees->y].donnee_suppl = deplacement;
            remplis_projectile(&niveau->objets[coordonnees->x][coordonnees->y], deplacement);
            
            niveau->objets[coordonnees->x - 1][coordonnees->y].type = VIDE;

            
            break;
        case DROITE:
            
            niveau->objets[coordonnees->x][++coordonnees->y].type = PROJECTILE;
            niveau->objets[coordonnees->x][coordonnees->y].donnee_suppl = deplacement;
            remplis_projectile(&niveau->objets[coordonnees->x][coordonnees->y], deplacement);
            niveau->objets[coordonnees->x][coordonnees->y - 1].type = VIDE;

            break;
        case GAUCHE:
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
            niveau->p2.is_player_alive = false;
        }
    }

}

bool check_game_over(Plateau board){
    return (board->mulptiplayer_mode) ? (!board->p1.is_player_alive && !board->p2.is_player_alive) : (!board->p1.is_player_alive);
}

int move_players(Plateau niveau, Player *player){
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
        case HAUT:
            player->coo_player.x -= 1;
            break;
        case BAS:
            player->coo_player.x += 1;
            break; 
        case DROITE:
            player->coo_player.y += 1;
            break;
        case GAUCHE:
            player->coo_player.y -= 1;
            break;
    }
    if(niveau->objets[player->coo_player.x][player->coo_player.y].type == PROJECTILE){
        printf("You just walk into a projectile ! Game OVER.\n");
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
        player->is_player_alive = false;
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

bool check_player_reached(Plateau niveau){
    return (!niveau->mulptiplayer_mode) ? (est_coordonnee_equivalent(niveau->p1.coo_player, niveau->coo_destination)) : (est_coordonnee_equivalent(niveau->p1.coo_player, niveau->coo_destination) && (est_coordonnee_equivalent(niveau->p2.coo_player, niveau->coo_destination)));
}

void affiche_Niveau (Plateau niveau) {

	unsigned int i, j;
    Deplacement *dep;
	for(i = 0; i < niveau->taille.x ; i++) {
		for(j = 0; j < niveau->taille.y; j++) {

			switch (niveau->objets[i][j].type)
			{
			case VIDE: 
				printf(".");
				break;
			case LANCEUR: 
				printf("O");
				break;
			case MUR: 
				printf("#");
				break;
			
			case PROJECTILE: 
                dep = niveau->objets[i][j].donnee_suppl;
				switch (dep->direction)
				{
				case HAUT: 
					printf("^");
					break;
				case GAUCHE:
					printf("<");
					break;
				case BAS: 
					printf("v");
					break;
				case DROITE: 
					printf(">");
					break;
				}
				break;

			case PERSONNAGE:
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


