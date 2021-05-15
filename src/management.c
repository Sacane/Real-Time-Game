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

Arbre build_heap_by_board(Board board){
	Arbre heap;
    heap = malloc_Tas(INITIAL_SIZE); 
	Evenement evenement;
	unsigned int i, j, k;
    Generation *gen = (Generation*)malloc(sizeof(Generation));
    verif_malloc(gen);
	for(i = 0; i < board->size.x ; i++){
		for(j = 0; j < board->size.y; j++){
            for(k = 0; k < board->box[i][j]->size; k++){
                if(board->box[i][j]->obj[k].type == LANCEUR){
                    memcpy(gen, board->box[i][j]->obj[k].donnee_suppl, sizeof(Generation));
                    evenement.coo_obj.x = i;
                    evenement.coo_obj.y = j;
                    evenement.index = k;
                    printf("%d\n", k);
                    evenement.moment = gen->intervalle;
                    ajoute_evenement(heap, evenement);
                }
            }
		}
	}
    free(gen);
	return heap;
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
    if(est_coordonnee_equivalent(*pos_projectile, plateau->coo_perso)){
        plateau->est_vivant = false;
    }
    free(generation);
}

/*Prend en paramètre l'ancien lanceur dans le tas et remet à jour le tas pour remettre l'évènement du lanceur 1 seconde après retrait du tas*/
static void update_launcher(Evenement lanceur, Arbre tas, Coordonnees pos_lanceur, Plateau niveau){
    printf("ON ENTRE\n");
    unsigned long update_moment;
    Generation *generation = (Generation*)malloc(sizeof(Generation));
    verif_malloc(generation);
    Evenement new_launcher;
    memcpy(generation, niveau->objets[pos_lanceur.x][pos_lanceur.y].donnee_suppl, sizeof(Generation));
    update_moment = lanceur.moment + generation->intervalle;
    new_launcher.moment = update_moment;
    printf("actual moment : %lu\n", update_moment);
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

    update_launcher(ancien_lanceur, tas, pos_lanceur, niveau);

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

    /* Lancer l'évènement e */
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

/*int create_projectile_by_direction(Board board, Arbre heap, Direction direction, Coordonnees pos_launcher, unsigned int index, Evenement old_proj, Coordonnees *pos_projectile){
    assert(board->box[pos_launcher.x][pos_launcher.y]->obj[index].type == LANCEUR);

    Coordonnees coo_projectile;
    Deplacement *depl = NULL;
    Generation *gen = NULL;
    Objet projectile_created;
    int index_tmp;
    Evenement ev_projectile;

    gen = (Generation*)malloc(sizeof(Generation));
    verif_malloc(gen);
    depl = (Deplacement*)malloc(sizeof(Deplacement));
    verif_malloc(depl);

    memcpy(gen, board->box[pos_launcher.x][pos_launcher.y]->obj[index].donnee_suppl, sizeof(Generation));

    depl->allure = gen->allure_proj;
    depl->direction = direction;
    assert(depl != NULL);
    printf("Evenement avant : %lu, %lu\n", gen->intervalle, depl->allure);

    switch(direction){
        case HAUT:
            pos_projectile->x = pos_launcher.x - 1;
            pos_projectile->y = pos_launcher.y;
            break;
        case BAS:
            pos_projectile->x = pos_launcher.x + 1;
            pos_projectile->y = pos_launcher.y;
            break;
        case DROITE:
            pos_projectile->x = pos_launcher.x;
            pos_projectile->y = pos_launcher.y + 1;
            break;
        case GAUCHE:
            pos_projectile->x = pos_launcher.x;
            pos_projectile->y = pos_launcher.y - 1;
            break;
    }
    printf("Après\n");
    projectile_created.type = PROJECTILE;
    projectile_created.donnee_suppl = (Deplacement*)malloc(sizeof(Deplacement));
    memcpy(projectile_created.donnee_suppl, depl, sizeof(Deplacement));

    index_tmp = add_object_in_array(board->box[pos_projectile->x][pos_projectile->y], projectile_created);

    if(est_coordonnee_equivalent(coo_projectile, board->player1.coo_player)){
        board->est_niveau_termine = true;
    }

    free(gen);

    return index_tmp;
}


static void update_heap_with_launcher(Evenement ev_launcher, Arbre heap, int index, Board board){

    Evenement new_launcher;
    Generation* gen = (Generation*)malloc(sizeof(Generation));
    memcpy(gen, board->box[ev_launcher.coo_obj.x][ev_launcher.coo_obj.y]->obj[index].donnee_suppl, sizeof(Generation));
    new_launcher.moment = ev_launcher.moment + gen->intervalle;
    printf("Moment : %lu\n", ev_launcher.moment);
    new_launcher.coo_obj = ev_launcher.coo_obj;
    new_launcher.index = index;
    ajoute_evenement(heap, new_launcher);
    free(gen);
}

void trigger_launcher(Board board, Arbre heap, Coordonnees coo_launcher, Evenement old_launcher){
    Generation *generation = (Generation*)malloc(sizeof(Generation));
    unsigned int index;
    verif_malloc(generation);
    memcpy(generation, board->box[coo_launcher.x][coo_launcher.y]->obj[old_launcher.index].donnee_suppl, sizeof(Generation));
    Direction direction;
    Evenement ev_proj;
    Coordonnees pos_projectile;
    for(direction = HAUT; direction <= DROITE; direction++){

        if(is_object_moveable(coo_launcher, direction, board)){
            index = create_projectile_by_direction(board, heap, direction, coo_launcher, old_launcher.index, old_launcher, &pos_projectile);
            ev_proj.moment = old_launcher.moment + generation->allure_proj;
            printf("Ah\n");
            ev_proj.coo_obj = pos_projectile;
            ajoute_evenement(heap, ev_proj);
        }
    }
    update_heap_with_launcher(old_launcher, heap, old_launcher.index, board);
    free(generation);

}

void trigger_projectile(Board board, Arbre heap, Evenement ev_proj){
    printf("0triggered\n");
    assert(board->box[ev_proj.coo_obj.x][ev_proj.coo_obj.y]->obj[ev_proj.index].type == PROJECTILE);
    assert(board->box[ev_proj.coo_obj.x][ev_proj.coo_obj.y]->obj[ev_proj.index].donnee_suppl != NULL);
    Evenement new_ev_projectile;
    unsigned long moment;
    int index_test;
    Deplacement *dep = (Deplacement*)malloc(sizeof(Deplacement));
    Coordonnees coo_tmp = ev_proj.coo_obj;
    memcpy(dep, board->box[ev_proj.coo_obj.x][ev_proj.coo_obj.y]->obj[ev_proj.index].donnee_suppl, sizeof(Deplacement));
    moment = ev_proj.moment + dep->allure;
    printf("ev_proj moment : %lu, depl allure : %lu\n", ev_proj.moment, dep->allure);
    index_test = move_projectile(board, &coo_tmp, ev_proj.index);
    affiche_coordonnee(coo_tmp);
    if(index_test >= 0){
        printf("Deplacé !\n");
        new_ev_projectile.index = (unsigned int)index_test;
        new_ev_projectile.moment = moment;
        new_ev_projectile.coo_obj = coo_tmp;
        ajoute_evenement(heap, new_ev_projectile);
    }
    printf("ev_proj moment : %lu, depl allure : %lu\n", ev_proj.moment, dep->allure);

    free(dep);
}

void execute_event(Evenement e, Arbre heap, Board board){
    assert(heap != NULL);
    assert(board != NULL);
    
    switch(board->box[e.coo_obj.x][e.coo_obj.y]->obj[e.index].type){
        case PROJECTILE:
            trigger_projectile(board, heap, e);
            break;
        case LANCEUR:
            trigger_launcher(board, heap, e.coo_obj, e);
            break;
        default:
            break;
    }
}*/