#include "../include/management.h"

/* On suppose que le tas n'est pas encore alloué, on le construit en fonction des éléments du niveau */
Arbre construit_Tas(Plateau niveau){
    
	Arbre arbre;
    arbre = malloc_Tas(INITIAL_SIZE); 
	Evenement evenement;
	unsigned int i, j;
    Generation *gen = (Generation*)malloc(sizeof(Generation));
    verif_malloc(gen);
	for(i = 0; i < niveau->taille.x ; i++){
		for(j = 0; j < niveau->taille.y; j++){
			if(niveau->objets[i][j].type == LANCEUR) {
                memcpy(gen, niveau->objets[i][j].donnee_suppl, sizeof(Generation));
            
				evenement.coo_obj.x = i;
				evenement.coo_obj.y = j;
				evenement.moment = gen->intervalle;
				ajoute_evenement(arbre, evenement);
			}
		}
	}
    free(gen);
	return arbre;
}


void creer_projectile_selon_direction(Plateau plateau, Direction direction, Coordonnees *pos_projectile, Coordonnees pos_lanceur){
	
    Deplacement* deplacement;
    deplacement = (Deplacement*)malloc(sizeof(Deplacement));
    verif_malloc(deplacement);
    Generation *generation = (Generation*)malloc(sizeof(Generation));
    verif_malloc(generation);
    memcpy(generation, plateau->objets[pos_lanceur.x][pos_lanceur.y].donnee_suppl, sizeof(Generation));
    deplacement->allure = generation->allure_proj;
    
    switch(direction){
        case HAUT:
            pos_projectile->x = pos_lanceur.x - 1;
            pos_projectile->y = pos_lanceur.y;
            deplacement->direction = HAUT;
            break;
        case BAS:
            pos_projectile->x = pos_lanceur.x + 1;
            pos_projectile->y = pos_lanceur.y;
            deplacement->direction = BAS;
            break;
        case DROITE:
            pos_projectile->x = pos_lanceur.x;
            pos_projectile->y = pos_lanceur.y + 1;
            deplacement->direction = DROITE;
            break;
        case GAUCHE:
            pos_projectile->x = pos_lanceur.x;
            pos_projectile->y = pos_lanceur.y - 1;
            deplacement->direction = GAUCHE;
            break;
        default:
            printf("Erreur de direction\n");
    }
    plateau->objets[pos_projectile->x][pos_projectile->y].type = PROJECTILE;
    plateau->objets[pos_projectile->x][pos_projectile->y].donnee_suppl = deplacement;

    if(est_coordonnee_equivalent(*pos_projectile, plateau->p1.coo_player)){
        plateau->p1.is_player_alive = false;
    }
    if(plateau->mulptiplayer_mode){
        if(est_coordonnee_equivalent(*pos_projectile, plateau->p2.coo_player)){
            plateau->p2.is_player_alive = false;
        }
    }
    free(generation);
}

/*Prend en paramètre l'ancien lanceur dans le tas et remet à jour le tas pour remettre l'évènement du lanceur 1 seconde après retrait du tas*/
static void update_launcher_in_heap(Evenement lanceur, Arbre tas, Coordonnees pos_lanceur, Plateau niveau){

    unsigned long update_moment;
    Generation *generation = (Generation*)malloc(sizeof(Generation));
    verif_malloc(generation);
    Evenement new_launcher;
    memcpy(generation, niveau->objets[pos_lanceur.x][pos_lanceur.y].donnee_suppl, sizeof(Generation));
    update_moment = lanceur.moment + generation->intervalle;
    new_launcher.moment = update_moment;
    new_launcher.coo_obj = lanceur.coo_obj;
    ajoute_evenement(tas, new_launcher);

    free(generation);
}

void declenche_lanceur(Plateau niveau, Arbre tas, Coordonnees pos_lanceur, Evenement ancien_lanceur){
	
    assert(niveau != NULL);
    assert(tas != NULL);
    assert(niveau->objets[pos_lanceur.x][pos_lanceur.y].type == LANCEUR);
    assert(pos_lanceur.x <= niveau->taille.x);
    assert(pos_lanceur.y <= niveau->taille.y);
    
    Generation *generation = (Generation*)malloc(sizeof(Generation));
    verif_malloc(generation);
    memcpy(generation, niveau->objets[pos_lanceur.x][pos_lanceur.y].donnee_suppl, sizeof(Generation));
    Direction direction;
    Coordonnees pos_projectile;
    Evenement evenement_projectile;

    for(direction = HAUT; direction <= DROITE; direction++){
        if(!se_dirige_vers_mur(pos_lanceur.x, pos_lanceur.y, direction, niveau)){
            creer_projectile_selon_direction(niveau, direction, &pos_projectile, pos_lanceur);
            evenement_projectile.moment = ancien_lanceur.moment + generation->allure_proj;
            evenement_projectile.coo_obj = pos_projectile;
            ajoute_evenement(tas, evenement_projectile);
        }
    }

    update_launcher_in_heap(ancien_lanceur, tas, pos_lanceur, niveau);

    free(generation);
}

/*
 (1) - Déplace le projectile : en fonction de la direction
 (2) - si le projectile n'a pas disparu (mur / hors plateau), rajoute dans le tas l'évènement du projectile à la position mis à jour
*/
void declenche_projectile(Arbre tas, Plateau niveau, Coordonnees pos_projectile, Evenement projectile){

	assert(tas != NULL);
	assert(niveau != NULL);
	assert(pos_projectile.x <= niveau->taille.x);
	assert(pos_projectile.y <= niveau->taille.y);
    assert(niveau->objets[pos_projectile.x][pos_projectile.y].type == PROJECTILE);

    Evenement evenement_projectile;
    Deplacement *dep = (Deplacement*)malloc(sizeof(Deplacement));
    dep = niveau->objets[pos_projectile.x][pos_projectile.y].donnee_suppl;
    deplace_projectile(niveau, &pos_projectile);
    unsigned long moment = projectile.moment + dep->allure;

	if(pos_projectile.x <= niveau->taille.x && pos_projectile.y <= niveau->taille.y){
		evenement_projectile.moment = moment;
		evenement_projectile.coo_obj = pos_projectile;
		ajoute_evenement(tas, evenement_projectile);
    }
}

void execute_evenement(Evenement e, Arbre tas, Plateau niveau) {

    assert(tas != NULL);
	assert(tas->valeurs != NULL);
    assert(niveau != NULL);
	assert(e.coo_obj.x <= niveau->taille.x);
    assert(e.coo_obj.y <= niveau->taille.y);
    Coordonnees coord_evenement;
    coord_evenement.x = e.coo_obj.x;
    coord_evenement.y = e.coo_obj.y;

    switch(niveau->objets[coord_evenement.x][coord_evenement.y].type){
        case PROJECTILE:
            declenche_projectile(tas, niveau, coord_evenement, e);
            break;
        case LANCEUR:
            declenche_lanceur(niveau, tas, coord_evenement, e);
            break;
        default:
            break;
    }
}

void launch_command(Plateau niveau, bool *is_reached){
    
    init_stdin();
    Arbre tas = construit_Tas(niveau);
    Evenement e;
	char touche;
    int success = true;
    bool moving = false;

    affiche_Niveau(niveau);

    while (true) {
        
        if(niveau->p1.is_player_alive == false){
            break;
        }
        if(niveau->mulptiplayer_mode){
            if(niveau->p2.is_player_alive == false){
                break;
            }
        }
        check_player_move(&(niveau->p1));
        if(niveau->mulptiplayer_mode)
            check_player_move(&(niveau->p2));
            
        while((touche = getchar()) != EOF){
            if(niveau->p1.can_player_move == true){
                switch (touche)
                {
                    case 'z':
                        niveau->p1.dir_player = HAUT;
                        moving = true;
                        break;
                    case 's':
                        niveau->p1.dir_player = BAS;
                        moving = true;
                        break;
                    case 'd':
                        niveau->p1.dir_player = DROITE;
                        moving = true;
                        break;
                    case 'q':
                        niveau->p1.dir_player = GAUCHE;
                        moving = true;
                        break;
                    default:
                        moving = false;
                        break;
                }
                if(niveau->p1.can_player_move == true && moving == true){
                    success = move_players(niveau, &(niveau->p1));
                    if(!success){
                        break;
                    }
                }
            }
            if(niveau->mulptiplayer_mode){
                if(niveau->p2.can_player_move == true){
                    switch(touche)
                    {
                        case 'o':
                            niveau->p2.dir_player = HAUT;
                            moving = true;
                            break;
                        case 'l':
                            niveau->p2.dir_player = BAS;
                            moving = true;
                            break;
                        case 'm':
                            niveau->p2.dir_player = DROITE;
                            moving = true;
                            break;
                        case 'k':
                            niveau->p2.dir_player = GAUCHE;
                            moving = true;
                            break;
                        default:
                            moving = false;
                            break;

                    }
                    if(niveau->p2.can_player_move && moving)
                        success = move_players(niveau, &(niveau->p2));
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
        if ( un_evenement_est_pret(tas)) {

            e = ote_minimum(tas);
            
            execute_evenement(e, tas, niveau);
            while(e.moment == tas->valeurs[0].moment){
                e = ote_minimum(tas);
                execute_evenement(e, tas, niveau);
            }
            affiche_Niveau(niveau);
    		printf("\n");
        }   
        else
            millisleep (10); 
        if(check_player_reached(niveau)){
            (*is_reached) = true;
            break;
        }
    }
    free_Tas(tas);
    restaure_stdin();

}