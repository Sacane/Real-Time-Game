#include "../include/test.h"



static bool test_add_event(int *total_test) {
    *total_test += 1;
    Heap test_heap = malloc_heap(INITIAL_SIZE);
    Event event1, event2, event3, event4, event5, event6, event7, event8, event9;
    
    event1.moment = 300;
    event2.moment = 2050;
    event3.moment = 1002;
    event4.moment = 293;
    event5.moment = 450;
    event6.moment = 1080;
    event7.moment = 850;
    event8.moment = 1300;
    event9.moment = 1000;
    
    add_event(test_heap, event1);

    if(test_heap->valeurs[0].moment != 300){
        free_heap(test_heap);
        return false;
    }
    
    add_event(test_heap, event2);

    if(is_heap(test_heap) == false){
        free_heap(test_heap);
        return false;
    }

    add_event(test_heap, event3);
    /* On vérifie que tas[1] et tas[2] plus petit que tas[1] */

    add_event(test_heap, event4);
    add_event(test_heap, event5);
    add_event(test_heap, event6);
    add_event(test_heap, event7);
    add_event(test_heap, event8);
    add_event(test_heap, event9);


    if(is_heap(test_heap) == false){
        free_heap(test_heap);
        return false;
    }

	free_heap(test_heap);

    return true;
}

static bool test_minimum_aux(Event min, Heap Tas){
    unsigned int i;
    
    for(i = 0; i < Tas->taille; i++){
        if(min.moment > Tas->valeurs[i].moment){
            return false;
        }
    }
    return true;
}

static bool test_ote_minimum(int *total_test){
    *total_test += 1;
	Heap arbre = malloc_heap(INITIAL_SIZE);
	Event event1, event2, event3, event4, event5, eventMin;
    Coordonnees pos1, pos2, pos3, pos4, pos5;
    pos1.x = 0;
    pos1.y = 0;
    pos2.x = 1;
    pos2.y = 1;
    pos3.x = 2;
    pos3.y = 2;
    pos4.x = 3;
    pos4.y = 3;
    pos5.x = 4; 
    pos5.y = 4;

    event1.moment = 300;
    event1.coo_obj = pos1;
    event2.moment = 2050;
    event2.coo_obj = pos2;
    event3.moment = 1002;
    event3.coo_obj = pos3;
    event4.moment = 293;
    event4.coo_obj = pos4;
    event5.moment = 450;
    event5.coo_obj = pos5;
    
	add_event(arbre, event1);
	add_event(arbre, event2);
	add_event(arbre, event3);
	add_event(arbre, event4);
	add_event(arbre, event5);
	eventMin = heap_pop(arbre);

    /* Le minimum est bien la valeur extraite */
	if (test_minimum_aux(eventMin, arbre) == false){
		free_heap(arbre);
		return false;
	}

    if(arbre->valeurs[0].moment == 293){
        printf("La valeur est toujours dans le tas\n");
        return false;
    }

    /* Test si le tas est toujours un tas */
	if(is_heap(arbre) == false){
        printf("Le tableau n'est plus un tas\n");
		free_heap(arbre);
		return false; 
	}

    free_heap(arbre);
	return true; 
}


static bool test_build_heap(int *total_test){
    *total_test += 1;
	Board level = level0();
    Heap arbre;
    
    Coordonnees lanceur1;
    lanceur1.x = 0;
    lanceur1.y = 0;
    
    Coordonnees lanceur2;
    lanceur2.x = 3;
    lanceur2.y = 5;

	arbre = construit_Tas(level);
	
    if(!arbre){
        free_board(level);
		free_heap(arbre);
        return false;
    }
    
	if(is_heap(arbre) == false){
        free_board(level);
		free_heap(arbre);
		return false; 
	}

	if(est_coordonnee_equivalent(lanceur1, (arbre->valeurs[0]).coo_obj) == false){
        free_board(level);
        free_heap(arbre);
        return false;
    }

	if(est_coordonnee_equivalent(lanceur2, (arbre->valeurs[1]).coo_obj) == false){
        free_board(level);
        free_heap(arbre);
        return false;
    }
    
	free_heap(arbre);
	free_board(level);
	return true;

}

/*
    - Tester si l'ancien coordonnée du projectile à bien comme type "VIDE"
    - Tester si la nouvelle coordonnée dans le level contient bien le projectile
    - Tester si lorsqu'il y a un mur, le projectile est bien effacé du Board
*/
static bool test_move_projectile_NORTH(int *total_test){

    *total_test += 1;
	Board level = level0();
	Objet objet; 
    Deplacement* deplacement;
    deplacement = (Deplacement*)malloc(sizeof(Deplacement));
    verif_malloc(deplacement);
	Coordonnees coordonnees;

	deplacement->direction = NORTH;
	coordonnees.x = 3;
    coordonnees.y = 2;
	objet.type = PROJECTILE; 
	objet.donnee_suppl = deplacement;
    level->objets[coordonnees.x][coordonnees.y] = objet;
	deplace_projectile(level, &coordonnees);

	if(level->objets[3][2].type != VIDE){
        printf("Projectile non-déplacé (NORTH) !");
		return false;
	}

	if(level->objets[2][2].type != PROJECTILE){
        printf("Projectile pas au bon endroit (NORTH) !\n");
		return false;
	}
    
    Coordonnees new_coord;
    new_coord.x = 2;
    new_coord.y = 2;

    deplace_projectile(level, &new_coord);

    if(level->objets[1][2].type != WALL){
        printf("Le mur a été modifié par un projectile (NORTH) !\n");
        return false;
    }


    Deplacement* dep;
    dep = (Deplacement*)malloc(sizeof(Deplacement));
    dep->direction = NORTH;
	Coordonnees new1coord2;
	new1coord2.x = 0;
	new1coord2.y = 2;

    level->objets[new1coord2.x][new1coord2.y].type = PROJECTILE;
    level->objets[new1coord2.x][new1coord2.y].donnee_suppl = dep;

    deplace_projectile( level, &new1coord2);
	if (level->objets[0][2].type != VIDE){
        printf("Projectile toujours présent (NORTH) \n");
		return false;
	}

    free_board(level);
	return true; 
}

static bool test_move_projectile_SOUTH(int *total_test){

	*total_test += 1;
    Board level = level0();
    Objet objet;
    Deplacement *dep = (Deplacement*)malloc(sizeof(Deplacement));
    verif_malloc(dep);
	Coordonnees coords;
    dep->direction = SOUTH;
    coords.x = 2;
    coords.y = 3;
    objet.type = PROJECTILE;
    objet.donnee_suppl = dep;
    level->objets[coords.x][coords.y] = objet;

	deplace_projectile( level, &coords);

    if(level->objets[2][3].type != VIDE){
        printf("Projectile non-déplacé (SOUTH) !");
		return false;
	}

	if(level->objets[3][3].type != PROJECTILE){
        printf("Projectile pas au bon endroit (SOUTH) !\n");
		return false;
	}
    deplace_projectile( level, &coords);


    if(level->objets[4][3].type != PROJECTILE){
        printf("Projectile toujours présent (SOUTH)\n");
		return false;
	}
    Coordonnees coord;
    coord.x = 4;
    coord.y = 3;
    deplace_projectile( level, &coord);

    free_board(level);
	return true; 
}


static bool test_move_projectile_EAST(int *total_test){

    *total_test += 1;
	Board level = level0();
	Objet objet;
    Deplacement* deplacement;
    deplacement = (Deplacement*)malloc(sizeof(Deplacement));
    verif_malloc(deplacement);
    Coordonnees coord;
	
	deplacement->direction = EAST;
    coord.x = 0;
    coord.y = 7;
	objet.type = PROJECTILE; 
	objet.donnee_suppl = deplacement;
    level->objets[coord.x][coord.y] = objet;


	deplace_projectile(level, &coord); 


	if(level->objets[0][7].type != VIDE){
        printf("Projectile non-déplacé ! (EAST)");
		return false;
	}

	if(level->objets[0][8].type != PROJECTILE){
        printf("Projectile pas au bon endroit (EAST)!\n");
		return false;
	}

    deplace_projectile(level, &coord); 
    
	if (level->objets[0][9].type != PROJECTILE){
        printf("Projectile toujours présent (EAST) \n");
		return false;
	}

    Coordonnees coords; 
    coords.x = 0;
    coords.y = 9; 
    deplace_projectile(level, &coords); 
    
	free_board(level);
	return true; 
}

static bool test_move_projectile_WEST(int *total_test){

	*total_test += 1;
	Board level = level0();
	Objet objet; 
    Deplacement* deplacement;
    deplacement = (Deplacement*)malloc(sizeof(Deplacement));
    verif_malloc(deplacement);
	Coordonnees coordonnees;

	deplacement->direction = WEST;
	coordonnees.x = 2;
    coordonnees.y = 2;
	objet.type = PROJECTILE; 
	objet.donnee_suppl = deplacement;
    level->objets[coordonnees.x][coordonnees.y] = objet;

	deplace_projectile(level, &coordonnees);
	
	if(level->objets[2][2].type != VIDE){
        printf("Projectile non-déplacé (WEST)!");
		return false;
	}

	if(level->objets[2][1].type != PROJECTILE){
        printf("Projectile pas au bon endroit (WEST)!\n");
		return false;
	}
    
    deplace_projectile(level, &coordonnees);

	if (level->objets[2][0].type != PROJECTILE){
        printf("Projectile toujours présent (WEST) \n");
		return false;
	}

    Coordonnees coord;
    coord.x = 2;
    coord.y = 0;
    deplace_projectile(level, &coord);
    if(level->objets[2][0].type != VIDE){
        printf("Le projectile est toujours là ! (WEST)\n");
        return false;
    }

	free_board(level);
	return true; 
}

/* Si la coordonnée remaining se trouve parmis les éléments du tas, la fonction return true, false sinon */
static bool test_equals_heap(Heap heap, Coordonnees remaining){
    unsigned int i;
    for(i = 0; i < heap->taille; i++){
        if(est_coordonnee_equivalent(remaining, heap->valeurs[i].coo_obj)){
            return true;
        }
    }
    return false;
}

static bool test_trigger_launcher(int *total_test){
    *total_test += 1;
    Board level = level0();
    Heap tas;
    Coordonnees eval;
    tas = construit_Tas(level);
    Event e = heap_pop(tas);
    int i;

    declenche_lanceur(level, tas, e.coo_obj, e);

    do{

        e = heap_pop(tas);

    }while(level->objets[e.coo_obj.x][e.coo_obj.y].type != LAUNCHER);

    declenche_lanceur(level, tas, e.coo_obj, e);

    for(i = NORTH; i <= EAST; i++){
        switch(i){
            case NORTH:
                eval.x = e.coo_obj.x - 1;
                eval.y = e.coo_obj.y;
                break;
            case SOUTH:
                eval.x = e.coo_obj.x + 1;
                eval.y = e.coo_obj.y;
                break;
            case EAST:
                eval.x = e.coo_obj.x;
                eval.y = e.coo_obj.y + 1;
                break;
            case WEST:
                eval.x = e.coo_obj.x;
                eval.y = e.coo_obj.y - 1;
                break;
        }
        if(!test_equals_heap(tas, eval)){
            printf("Le projectile n'est pas dans le tas\n");
            return false;
        }
    }


    free_heap(tas);
    free_board(level);
    return true;
}





static void qtest(const char* name_fun, int *counter, int *total_test, bool(*test_function)(int *total_test)){
    if(test_function(total_test)){
        (*counter)++;
        printf("test function '%s' : success\n", name_fun);
    }
    else{
        printf("test function '%s' : failure\n", name_fun);
    }
}




void main_test(){
    int compteur = 0;
    int total_test = 0;

    qtest("test_add_event", &compteur, &total_test, test_add_event);

    qtest("test_ote_minimum", &compteur, &total_test, test_ote_minimum);

    qtest("test_build_heap", &compteur, &total_test, test_build_heap);

    qtest("test_move_projectile_NORTH", &compteur, &total_test, test_move_projectile_NORTH);

	qtest("test_move_projectile_SOUTH", &compteur, &total_test, test_move_projectile_SOUTH);

	qtest("test_move_projectile_EAST", &compteur, &total_test, test_move_projectile_EAST);

    qtest("test_move_projectile_WEST", &compteur, &total_test, test_move_projectile_WEST);

    qtest("test_trigger_launcher", &compteur, &total_test, test_trigger_launcher);


    printf("Résultat totaux des tests : %d / %d\n", compteur, total_test);
}
