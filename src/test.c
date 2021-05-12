#include "../include/test.h"



static bool test_ajoute_evenement(int *total_test) {
    *total_test += 1;
    Arbre test_arbre = malloc_Tas(INITIAL_SIZE);
    Evenement event1, event2, event3, event4, event5, event6, event7, event8, event9;
    
    event1.moment = 300;
    event2.moment = 2050;
    event3.moment = 1002;
    event4.moment = 293;
    event5.moment = 450;
    event6.moment = 1080;
    event7.moment = 850;
    event8.moment = 1300;
    event9.moment = 1000;
    
    ajoute_evenement(test_arbre, event1);

    if(test_arbre->valeurs[0].moment != 300){
        free_Tas(test_arbre);
        return false;
    }
    
    ajoute_evenement(test_arbre, event2);

    if(estTas(test_arbre) == false){
        free_Tas(test_arbre);
        return false;
    }

    ajoute_evenement(test_arbre, event3);
    /* On vérifie que tas[1] et tas[2] plus petit que tas[1] */

    ajoute_evenement(test_arbre, event4);
    ajoute_evenement(test_arbre, event5);
    ajoute_evenement(test_arbre, event6);
    ajoute_evenement(test_arbre, event7);
    ajoute_evenement(test_arbre, event8);
    ajoute_evenement(test_arbre, event9);


    if(estTas(test_arbre) == false){
        free_Tas(test_arbre);
        return false;
    }

	free_Tas(test_arbre);

    return true;
}

static bool test_minimum_aux(Evenement min, Arbre Tas){
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
	Arbre arbre = malloc_Tas(INITIAL_SIZE);
	Evenement event1, event2, event3, event4, event5, eventMin;
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
    
	ajoute_evenement(arbre, event1);
	ajoute_evenement(arbre, event2);
	ajoute_evenement(arbre, event3);
	ajoute_evenement(arbre, event4);
	ajoute_evenement(arbre, event5);
	eventMin = ote_minimum(arbre);

    /* Le minimum est bien la valeur extraite */
	if (test_minimum_aux(eventMin, arbre) == false){
		free_Tas(arbre);
		return false;
	}

    if(arbre->valeurs[0].moment == 293){
        printf("La valeur est toujours dans le tas\n");
        return false;
    }

    /* Test si le tas est toujours un tas */
	if(estTas(arbre) == false){
        printf("Le tableau n'est plus un tas\n");
		free_Tas(arbre);
		return false; 
	}

    free_Tas(arbre);
	return true; 
}


static bool test_contruit_tas(int *total_test){
    *total_test += 1;
	Plateau niveau = niveau0();
    Arbre arbre;
    
    Coordonnees lanceur1;
    lanceur1.x = 0;
    lanceur1.y = 0;
    
    Coordonnees lanceur2;
    lanceur2.x = 3;
    lanceur2.y = 5;

	arbre = construit_Tas(niveau);
	
    if(!arbre){
        free_Niveau(niveau);
		free_Tas(arbre);
        return false;
    }
    
	if(estTas(arbre) == false){
        free_Niveau(niveau);
		free_Tas(arbre);
		return false; 
	}

	if(est_coordonnee_equivalent(lanceur1, (arbre->valeurs[0]).coo_obj) == false){
        free_Niveau(niveau);
        free_Tas(arbre);
        return false;
    }

	if(est_coordonnee_equivalent(lanceur2, (arbre->valeurs[1]).coo_obj) == false){
        free_Niveau(niveau);
        free_Tas(arbre);
        return false;
    }
    
	free_Tas(arbre);
	free_Niveau(niveau);
	return true;

}

/*
    - Tester si l'ancien coordonnée du projectile à bien comme type "VIDE"
    - Tester si la nouvelle coordonnée dans le niveau contient bien le projectile
    - Tester si lorsqu'il y a un mur, le projectile est bien effacé du plateau
*/
static bool test_deplace_projectile_haut(int *total_test){

    *total_test += 1;
	Plateau niveau = niveau0();
	Objet objet; 
    Deplacement* deplacement;
    deplacement = (Deplacement*)malloc(sizeof(Deplacement));
    verif_malloc(deplacement);
	Coordonnees coordonnees;

	deplacement->direction = HAUT;
	coordonnees.x = 3;
    coordonnees.y = 2;
	objet.type = PROJECTILE; 
	objet.donnee_suppl = deplacement;
    niveau->objets[coordonnees.x][coordonnees.y] = objet;
	deplace_projectile(niveau, &coordonnees);

	if(niveau->objets[3][2].type != VIDE){
        printf("Projectile non-déplacé (haut) !");
		return false;
	}

	if(niveau->objets[2][2].type != PROJECTILE){
        printf("Projectile pas au bon endroit (haut) !\n");
		return false;
	}
    
    Coordonnees new_coord;
    new_coord.x = 2;
    new_coord.y = 2;

    deplace_projectile(niveau, &new_coord);

    if(niveau->objets[1][2].type != MUR){
        printf("Le mur a été modifié par un projectile (haut) !\n");
        return false;
    }


    Deplacement* dep;
    dep = (Deplacement*)malloc(sizeof(Deplacement));
    dep->direction = HAUT;
	Coordonnees new1coord2;
	new1coord2.x = 0;
	new1coord2.y = 2;

    niveau->objets[new1coord2.x][new1coord2.y].type = PROJECTILE;
    niveau->objets[new1coord2.x][new1coord2.y].donnee_suppl = dep;

    deplace_projectile( niveau, &new1coord2);
	if (niveau->objets[0][2].type != VIDE){
        printf("Projectile toujours présent (haut) \n");
		return false;
	}

    free_Niveau(niveau);
	return true; 
}

static bool test_deplace_projectile_bas(int *total_test){

	*total_test += 1;
    Plateau niveau = niveau0();
    Objet objet;
    Deplacement *dep = (Deplacement*)malloc(sizeof(Deplacement));
    verif_malloc(dep);
	Coordonnees coords;
    dep->direction = BAS;
    coords.x = 2;
    coords.y = 3;
    objet.type = PROJECTILE;
    objet.donnee_suppl = dep;
    niveau->objets[coords.x][coords.y] = objet;

	deplace_projectile( niveau, &coords);

    if(niveau->objets[2][3].type != VIDE){
        printf("Projectile non-déplacé (bas) !");
		return false;
	}

	if(niveau->objets[3][3].type != PROJECTILE){
        printf("Projectile pas au bon endroit (bas) !\n");
		return false;
	}
    deplace_projectile( niveau, &coords);


    if(niveau->objets[4][3].type != PROJECTILE){
        printf("Projectile toujours présent (bas)\n");
		return false;
	}
    Coordonnees coord;
    coord.x = 4;
    coord.y = 3;
    deplace_projectile( niveau, &coord);

    free_Niveau(niveau);
	return true; 
}


static bool test_deplace_projectile_droite(int *total_test){

    *total_test += 1;
	Plateau niveau = niveau0();
	Objet objet;
    Deplacement* deplacement;
    deplacement = (Deplacement*)malloc(sizeof(Deplacement));
    verif_malloc(deplacement);
    Coordonnees coord;
	
	deplacement->direction = DROITE;
    coord.x = 0;
    coord.y = 7;
	objet.type = PROJECTILE; 
	objet.donnee_suppl = deplacement;
    niveau->objets[coord.x][coord.y] = objet;


	deplace_projectile(niveau, &coord); 


	if(niveau->objets[0][7].type != VIDE){
        printf("Projectile non-déplacé ! (droite)");
		return false;
	}

	if(niveau->objets[0][8].type != PROJECTILE){
        printf("Projectile pas au bon endroit (droite)!\n");
		return false;
	}

    deplace_projectile(niveau, &coord); 
    
	if (niveau->objets[0][9].type != PROJECTILE){
        printf("Projectile toujours présent (droite) \n");
		return false;
	}

    Coordonnees coords; 
    coords.x = 0;
    coords.y = 9; 
    deplace_projectile(niveau, &coords); 
    
	free_Niveau(niveau);
	return true; 
}

static bool test_deplace_projectile_gauche(int *total_test){

	*total_test += 1;
	Plateau niveau = niveau0();
	Objet objet; 
    Deplacement* deplacement;
    deplacement = (Deplacement*)malloc(sizeof(Deplacement));
    verif_malloc(deplacement);
	Coordonnees coordonnees;

	deplacement->direction = GAUCHE;
	coordonnees.x = 2;
    coordonnees.y = 2;
	objet.type = PROJECTILE; 
	objet.donnee_suppl = deplacement;
    niveau->objets[coordonnees.x][coordonnees.y] = objet;

	deplace_projectile(niveau, &coordonnees);
	
	if(niveau->objets[2][2].type != VIDE){
        printf("Projectile non-déplacé (gauche)!");
		return false;
	}

	if(niveau->objets[2][1].type != PROJECTILE){
        printf("Projectile pas au bon endroit (gauche)!\n");
		return false;
	}
    
    deplace_projectile(niveau, &coordonnees);

	if (niveau->objets[2][0].type != PROJECTILE){
        printf("Projectile toujours présent (gauche) \n");
		return false;
	}

    Coordonnees coord;
    coord.x = 2;
    coord.y = 0;
    deplace_projectile(niveau, &coord);
    if(niveau->objets[2][0].type != VIDE){
        printf("Le projectile est toujours là ! (gauche)\n");
        return false;
    }

	free_Niveau(niveau);
	return true; 
}

/* Si la coordonnée remaining se trouve parmis les éléments du tas, la fonction return true, false sinon */
static bool test_equals_heap(Arbre heap, Coordonnees remaining){
    unsigned int i;
    for(i = 0; i < heap->taille; i++){
        if(est_coordonnee_equivalent(remaining, heap->valeurs[i].coo_obj)){
            return true;
        }
    }
    return false;
}

static bool test_declenche_lanceur(int *total_test){
    *total_test += 1;
    Plateau niveau = niveau0();
    Arbre tas;
    Coordonnees eval;
    tas = construit_Tas(niveau);
    Evenement e = ote_minimum(tas);
    int i;

    declenche_lanceur(niveau, tas, e.coo_obj, e);

    do{

        e = ote_minimum(tas);

    }while(niveau->objets[e.coo_obj.x][e.coo_obj.y].type != LANCEUR);

    declenche_lanceur(niveau, tas, e.coo_obj, e);

    for(i = HAUT; i <= DROITE; i++){
        switch(i){
            case HAUT:
                eval.x = e.coo_obj.x - 1;
                eval.y = e.coo_obj.y;
                break;
            case BAS:
                eval.x = e.coo_obj.x + 1;
                eval.y = e.coo_obj.y;
                break;
            case DROITE:
                eval.x = e.coo_obj.x;
                eval.y = e.coo_obj.y + 1;
                break;
            case GAUCHE:
                eval.x = e.coo_obj.x;
                eval.y = e.coo_obj.y - 1;
                break;
        }
        if(!test_equals_heap(tas, eval)){
            printf("Le projectile n'est pas dans le tas\n");
            return false;
        }
    }

    affiche_Niveau(niveau);

    free_Tas(tas);
    free_Niveau(niveau);
    return true;
}

/*static bool test_declenche_projectile(int *total_test){
	
	*total_test += 1;
	Arbre tas;
	Plateau niveau = niveau0();

    Evenement ev;

    ev = ote_minimum(tas);

    declenche_projectile(tas, niveau, ev.coo_obj, ev);

    ev = ote_minimum(tas);

    declenche_projectile(tas, niveau, ev.coo_obj, ev);

    ev = ote_minimum(tas);

    declenche_projectile(tas, niveau, ev.coo_obj, ev);

    ev = ote_minimum(tas);

    declenche_projectile(tas, niveau, ev.coo_obj, ev);

    if(!estTas(tas)){
        return false;
    }

    
    free_Niveau(niveau);
    free_Tas(tas);
	return true;
}*/

static bool test_equals_obj(int *total_test){
    (*total_test)++;
    Objet obj1;
    Objet obj2;
    Objet obj3;
    Objet obj4;

    Deplacement* dep1 = (Deplacement *)malloc(sizeof(Deplacement));
    Deplacement* dep2 = (Deplacement *)malloc(sizeof(Deplacement));
    Deplacement* dep3 = (Deplacement *)malloc(sizeof(Deplacement));
    Deplacement* dep4 = (Deplacement *)malloc(sizeof(Deplacement));

    dep1->allure = 3000;
    dep2->allure = 3000;
    dep3->allure = 3400;
    dep4->allure = 3000;

    dep1->direction = BAS;
    dep2->direction = BAS;
    dep3->direction = HAUT;
    dep4->direction = DROITE;

    obj1.type = PROJECTILE;
    obj2.type = PROJECTILE;
    obj3.type = PROJECTILE;
    obj4.type = PROJECTILE;

    obj1.donnee_suppl = dep1;
    obj2.donnee_suppl = dep2;
    obj3.donnee_suppl = dep3;
    obj4.donnee_suppl = dep4;

    if(!equals_obj(obj1, obj2)){
        printf("Erreur, obj1 et obj2 devraient être pareil\n");
        return false;
    }

    if(equals_obj(obj1, obj3)){
        printf("Erreur, obj1 et obj3 devraient être différent\n");
        return false;
    }

    if(equals_obj(obj2, obj4)){
        printf("Erreur, obj2 et obj4 devraient être différent\n");
        return false;
    }
    
    free(dep1);
    free(dep2);
    free(dep3);
    free(dep4);

    return true;
}







static void qtest(const char* nom_func, int *counter, int *total_test, bool(*test_function)(int *total_test)){
    if(test_function(total_test)){
        (*counter)++;
        printf("test function '%s' : success\n", nom_func);
    }
    else{
        printf("test function '%s' : failure\n", nom_func);
    }
}

void main_test(){
    int compteur = 0;
    int total_test = 0;

    qtest("test_ajoute_evenement", &compteur, &total_test, test_ajoute_evenement);

    qtest("test_ote_minimum", &compteur, &total_test, test_ote_minimum);

    qtest("test_contruit_tas", &compteur, &total_test, test_contruit_tas);

    qtest("test_deplace_projectile_haut", &compteur, &total_test, test_deplace_projectile_haut);

	qtest("test_deplace_projectile_bas", &compteur, &total_test, test_deplace_projectile_bas);

	qtest("test_deplace_projectile_droite", &compteur, &total_test, test_deplace_projectile_droite);

    qtest("test_deplace_projectile_gauche", &compteur, &total_test, test_deplace_projectile_gauche);

    qtest("test_declenche_lanceur", &compteur, &total_test, test_declenche_lanceur);

    qtest("test_equals_obj", &compteur, &total_test, test_equals_obj);

    printf("Résultat totaux des tests : %d / %d\n", compteur, total_test);
}