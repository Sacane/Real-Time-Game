/**
 * \file test.c
 * \authors Ramaroson Rakotomihamina Johan && Li Christine
 * \date : 01-04-21
 * \last modification : 21-05-21
 * 
 * File containing the functions ---- 
 *
 */

#include "../include/test.h"



/**
 * \fn static bool test_add_event(int *total_test)
 * \brief Test function of the add_event function
 * \param total_test : int *
 * \return bool, true if the test succeeded, false otherwise
 */
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

    if(test_heap->values[0].moment != 300){
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


/**
 * \fn static bool test_minimum_aux(Event min, Heap Tas)
 * \brief Test function of the minimun_aux function
 * \param total_test : int *
 * \return bool, true if the test succeeded, false otherwise
 */
static bool test_minimum_aux(Event min, Heap Tas){
    unsigned int i;
    
    for(i = 0; i < Tas->size; i++){
        if(min.moment > Tas->values[i].moment){
            return false;
        }
    }
    return true;
}


/**
 * \fn static bool test_ote_minimum(int *total_test)
 * \brief Test function of the ote_minimum function
 * \param total_test : int *
 * \return bool, true if the test succeeded, false otherwise
 */
static bool test_ote_minimum(int *total_test){
    *total_test += 1;
	Heap arbre = malloc_heap(INITIAL_SIZE);
	Event event1, event2, event3, event4, event5, eventMin;
    Coordinates pos1, pos2, pos3, pos4, pos5;
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

    if(arbre->values[0].moment == 293){
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


/**
 * \fn static bool test_build_heap(int *total_test)
 * \brief Test function of the build_heap function
 * \param total_test : int *
 * \return bool, true if the test succeeded, false otherwise
 */
static bool test_build_heap(int *total_test){
    *total_test += 1;
	Board level = level0();
    Heap arbre;
    
    Coordinates lanceur1;
    lanceur1.x = 0;
    lanceur1.y = 0;
    
    Coordinates lanceur2;
    lanceur2.x = 3;
    lanceur2.y = 5;

	arbre = build_heap_by_board(level);
	
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

	if(equals_coordinates(lanceur1, (arbre->values[0]).coo_obj) == false){
        free_board(level);
        free_heap(arbre);
        return false;
    }

	if(equals_coordinates(lanceur2, (arbre->values[1]).coo_obj) == false){
        free_board(level);
        free_heap(arbre);
        return false;
    }
    
	free_heap(arbre);
	free_board(level);
	return true;

}


/**
 * \fn static bool test_move_projectile_NORTH(int *total_test)
 * \brief Test function of the move_projectile function (to the North)
 * \param total_test : int *
 * \return bool, true if the test succeeded, false otherwise
 */
static bool test_move_projectile_NORTH(int *total_test){

    *total_test += 1;
	Board level = level0();
	Object object; 
    Deplacement* deplacement;
    deplacement = (Deplacement*)malloc(sizeof(Deplacement));
    verif_malloc(deplacement);
	Coordinates coo;

	deplacement->direction = NORTH;
	coo.x = 3;
    coo.y = 2;
	object.type = PROJECTILE; 
	object.data = deplacement;
    level->objects[coo.x][coo.y] = object;
	move_projectile(level, &coo);

	if(level->objects[3][2].type != VIDE){
        printf("Projectile non-déplacé (NORTH) !");
		return false;
	}

	if(level->objects[2][2].type != PROJECTILE){
        printf("Projectile pas au bon endroit (NORTH) !\n");
		return false;
	}
    
    Coordinates new_coord;
    new_coord.x = 2;
    new_coord.y = 2;

    move_projectile(level, &new_coord);

    if(level->objects[1][2].type != WALL){
        printf("Le mur a été modifié par un projectile (NORTH) !\n");
        return false;
    }


    Deplacement* dep;
    dep = (Deplacement*)malloc(sizeof(Deplacement));
    dep->direction = NORTH;
	Coordinates new1coord2;
	new1coord2.x = 0;
	new1coord2.y = 2;

    level->objects[new1coord2.x][new1coord2.y].type = PROJECTILE;
    level->objects[new1coord2.x][new1coord2.y].data = dep;

    move_projectile( level, &new1coord2);
	if (level->objects[0][2].type != VIDE){
        printf("Projectile toujours présent (NORTH) \n");
		return false;
	}

    free_board(level);
	return true; 
}


/**
 * \fn static bool test_move_projectile_SOUTH(int *total_test)
 * \brief Test function of the move_projectile function (to the South)
 * \param total_test : int *
 * \return bool, true if the test succeeded, false otherwise
 */
static bool test_move_projectile_SOUTH(int *total_test){

	*total_test += 1;
    Board level = level0();
    Object object;
    Deplacement *dep = (Deplacement*)malloc(sizeof(Deplacement));
    verif_malloc(dep);
	Coordinates coords;
    dep->direction = SOUTH;
    coords.x = 2;
    coords.y = 3;
    object.type = PROJECTILE;
    object.data = dep;
    level->objects[coords.x][coords.y] = object;

	move_projectile( level, &coords);

    if(level->objects[2][3].type != VIDE){
        printf("Projectile non-déplacé (SOUTH) !");
		return false;
	}

	if(level->objects[3][3].type != PROJECTILE){
        printf("Projectile pas au bon endroit (SOUTH) !\n");
		return false;
	}
    move_projectile( level, &coords);


    if(level->objects[4][3].type != PROJECTILE){
        printf("Projectile toujours présent (SOUTH)\n");
		return false;
	}
    Coordinates coord;
    coord.x = 4;
    coord.y = 3;
    move_projectile( level, &coord);

    free_board(level);
	return true; 
}


/**
 * \fn static bool test_move_projectile_EAST(int *total_test)
 * \brief Test function of the move_projectile function (to the East)
 * \param total_test : int *
 * \return bool, true if the test succeeded, false otherwise
 */
static bool test_move_projectile_EAST(int *total_test){

    *total_test += 1;
	Board level = level0();
	Object object;
    Deplacement* deplacement;
    deplacement = (Deplacement*)malloc(sizeof(Deplacement));
    verif_malloc(deplacement);
    Coordinates coord;
	
	deplacement->direction = EAST;
    coord.x = 0;
    coord.y = 7;
	object.type = PROJECTILE; 
	object.data = deplacement;
    level->objects[coord.x][coord.y] = object;


	move_projectile(level, &coord); 


	if(level->objects[0][7].type != VIDE){
        printf("Projectile non-déplacé ! (EAST)");
		return false;
	}

	if(level->objects[0][8].type != PROJECTILE){
        printf("Projectile pas au bon endroit (EAST)!\n");
		return false;
	}

    move_projectile(level, &coord); 
    
	if (level->objects[0][9].type != PROJECTILE){
        printf("Projectile toujours présent (EAST) \n");
		return false;
	}

    Coordinates coords; 
    coords.x = 0;
    coords.y = 9; 
    move_projectile(level, &coords); 
    
	free_board(level);
	return true; 
}


/**
 * \fn static bool test_move_projectile_WEST(int *total_test)
 * \brief Test function of the move_projectile function (to the West)
 * \param total_test : int *
 * \return bool, true if the test succeeded, false otherwise
 */
static bool test_move_projectile_WEST(int *total_test){

	*total_test += 1;
	Board level = level0();
	Object object; 
    Deplacement* deplacement;
    deplacement = (Deplacement*)malloc(sizeof(Deplacement));
    verif_malloc(deplacement);
	Coordinates coo;

	deplacement->direction = WEST;
	coo.x = 2;
    coo.y = 2;
	object.type = PROJECTILE; 
	object.data = deplacement;
    level->objects[coo.x][coo.y] = object;

	move_projectile(level, &coo);
	
	if(level->objects[2][2].type != VIDE){
        printf("Projectile non-déplacé (WEST)!");
		return false;
	}

	if(level->objects[2][1].type != PROJECTILE){
        printf("Projectile pas au bon endroit (WEST)!\n");
		return false;
	}
    
    move_projectile(level, &coo);

	if (level->objects[2][0].type != PROJECTILE){
        printf("Projectile toujours présent (WEST) \n");
		return false;
	}

    Coordinates coord;
    coord.x = 2;
    coord.y = 0;
    move_projectile(level, &coord);
    if(level->objects[2][0].type != VIDE){
        printf("Le projectile est toujours là ! (WEST)\n");
        return false;
    }

	free_board(level);
	return true; 
}


/**
 * \fn static bool test_move_projectile_WEST(int *total_test)
 * \brief Test function of the equals_heap function 
 * \param total_test : int *
 * \return bool, If the remaining coordinate is among the elements of the heap, the function return true, false otherwise
 */
static bool test_equals_heap(Heap heap, Coordinates remaining){
    unsigned int i;
    for(i = 0; i < heap->size; i++){
        if(equals_coordinates(remaining, heap->values[i].coo_obj)){
            return true;
        }
    }
    return false;
}


/**
 * \fn static bool test_trigger_launcher(int *total_test)
 * \brief Test function of the trigger_launcher function 
 * \param total_test : int *
 * \return bool, true if the test succeeded, false otherwise
 */
static bool test_trigger_launcher(int *total_test){
    *total_test += 1;
    Board level = level0();
    Heap tas;
    Coordinates eval;
    tas = build_heap_by_board(level);
    Event e = heap_pop(tas);
    int i;

    trigger_launcher(level, tas, e.coo_obj, e);

    do{

        e = heap_pop(tas);

    }while(level->objects[e.coo_obj.x][e.coo_obj.y].type != LAUNCHER);

    trigger_launcher(level, tas, e.coo_obj, e);

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


/**
 * \fn static void qtest(const char* name_fun, int *counter, int *total_test, bool(*test_function)(int *total_test))
 * \brief Test function qtest
 * \param total_test : int *
 * \return bool, true if the test succeeded, false otherwise
 */
static void qtest(const char* name_fun, int *counter, int *total_test, bool(*test_function)(int *total_test)){
    if(test_function(total_test)){
        (*counter)++;
        printf("test function '%s' : success\n", name_fun);
    }
    else{
        printf("test function '%s' : failure\n", name_fun);
    }
}


/**
 * \fn void main_test()
 * \brief Function 'main' of tests 
 */
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
