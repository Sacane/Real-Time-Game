#include "../include/test.h"


static bool test_evenement_pret(int *total_test){
    *total_test += 1;
    unsigned long eval;
	Arbre test_tas;
    test_tas = malloc_Tas(INITIAL_SIZE);
    test_tas->taille = 15;
    test_tas->valeurs[0].moment = 1000;
    test_tas->valeurs[1].moment = 1300;
    test_tas->valeurs[2].moment = 2000;
    
    while(true){
        eval = maintenant();
        if(eval == 800){
            if(un_evenement_est_pret(test_tas) == true){
				free_Tas(test_tas);
                return false;
            }
        }
        if(eval == 1000){
            if(un_evenement_est_pret(test_tas) == false){
				free_Tas(test_tas);
                return false;
            }
        }
        break;
    }
    free_Tas(test_tas);
    return true;
}

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
    affiche_Tas(arbre);
	eventMin = ote_minimum(arbre);
    printf("test après ote minmum\n");

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
        printf("Le tas n'est plus un tas\n");
        affiche_Tas(arbre);
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
    deplacement = (Deplacement*)malloc(sizeof(deplacement));
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
    dep = (Deplacement*)malloc(sizeof(deplacement));
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

    free(dep);
	free(deplacement);
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
    
    free(dep);
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

    printf("test projectile présent : \n");
    
	if (niveau->objets[0][9].type != PROJECTILE){
        printf("Projectile toujours présent (droite) \n");
		return false;
	}

    Coordonnees coords; 
    coords.x = 0;
    coords.y = 9; 
    deplace_projectile(niveau, &coords); 
    
	free_Niveau(niveau);
	free(deplacement);
	return true; 
}

static bool test_deplace_projectile_gauche(int *total_test){

	*total_test += 1;
	Plateau niveau = niveau0();
	Objet objet; 
    Deplacement* deplacement;
    deplacement = (Deplacement*)malloc(sizeof(deplacement));
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
	free(deplacement);
	return true; 
}

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
    tas = malloc_Tas(512);
    Coordonnees pos_lanceur;
    pos_lanceur.x = 3;
    pos_lanceur.y = 5;

    Coordonnees pos_lanceur2;
    pos_lanceur2.x = 0;
    pos_lanceur2.y = 0;

    Coordonnees component;

    declenche_lanceur(niveau, tas, pos_lanceur);
    
    component.x = pos_lanceur.x - 1;
    component.y = pos_lanceur.y;

    if(niveau->objets[component.x][component.y].type != PROJECTILE){
        printf("Erreur, projectile non créer\n");
        return false;
    }
    if(!test_equals_heap(tas, component)){
        printf("Erreur, le projectile à la position : 3 5 n'est pas insérer dans le tas\n");
        return false;
    }
    declenche_lanceur(niveau, tas, pos_lanceur2);
    
    component.x = pos_lanceur2.x + 1;
    component.y = pos_lanceur2.y;


    component.x = pos_lanceur2.x;
    component.y = pos_lanceur2.y + 1;

    if(!test_equals_heap(tas, component)){
        printf("Erreur, le projectile à la position : 0 1 n'est pas insérer dans le tas\n");
        return false;
    }
    free_Tas(tas);
    free_Niveau(niveau);
    return true;
}

static bool test_declenche_projectile(int *total_test){
	
	*total_test += 1;
	Arbre tas;
	tas = malloc_Tas(512);
	Plateau niveau = niveau0();

    Coordonnees pos_lanceur;
    pos_lanceur.x = 3;
    pos_lanceur.y = 5;
    Evenement ev;

    affiche_Niveau(niveau);

    declenche_lanceur(niveau, tas, pos_lanceur);

    ev = ote_minimum(tas);

    declenche_projectile(tas, niveau, ev.coo_obj);

    affiche_Niveau(niveau);

    ev = ote_minimum(tas);

    declenche_projectile(tas, niveau, ev.coo_obj);

    affiche_Niveau(niveau);

    ev = ote_minimum(tas);

    declenche_projectile(tas, niveau, ev.coo_obj);

    affiche_Niveau(niveau);
    affiche_Tas(tas);

    ev = ote_minimum(tas);

    /*declenche_projectile(tas, niveau, ev.coo_obj);*/

    affiche_Niveau(niveau);
    affiche_Tas(tas);

    if(!estTas(tas)){
        return false;
    }

    
    free_Niveau(niveau);
    free_Tas(tas);
	return true;
}

static bool test_execute_evenement(int *total_test){
    (*total_test)++;

    Plateau niveau = niveau0();
    Arbre tas;
    tas = malloc_Tas(512);
    tas = construit_Tas(niveau);


    
    Evenement ev = ote_minimum(tas);

    execute_evenement(ev, tas, niveau);

    ev = ote_minimum(tas);

    execute_evenement(ev, tas, niveau);

    affiche_Tas(tas);
    affiche_Niveau(niveau);

    ev = ote_minimum(tas);

    execute_evenement(ev, tas, niveau);
    
    affiche_Tas(tas);
    affiche_Niveau(niveau);
    
    free_Niveau(niveau);
    free_Tas(tas);


    return true;
}

void main_test(){
    int compteur = 0;
    int total_test = 0;
    if(test_evenement_pret(&total_test) == true){
        compteur++;
        printf("test 'un_evenement_est_pret' : réussi\n");
    }
    else{
        printf("test 'un_evenement_est_pret' : échoué\n");
    }

    if(test_ajoute_evenement(&total_test) == true){
        compteur++;
        printf("test 'ajoute_evenement' : réussi\n");
    }
    else{
        printf("test 'ajoute_evenement' : échoué\n");
    }

	if(test_ote_minimum(&total_test) == true){
        compteur++;
        printf("test 'ote_minimum' : réussi\n");
    }
    else{
        printf("test 'ote_minimum' : échoué\n");
    }
    
    if(test_contruit_tas(&total_test) == true){
        compteur++;
        printf("test 'construit_tas' : réussi\n");
    }
    else{
        printf("test 'construit_tas' : échoué\n");
    }

	if(test_deplace_projectile_haut(&total_test) == true){
        compteur++;
        printf("test vers le haut 'deplace_projectile_haut' : réussi\n");
    }
    else{
        printf("test vers le haut 'deplace_projectile_haut' : échoué\n");
    }
	
	if(test_deplace_projectile_bas(&total_test) == true){
        compteur++;
        printf("test vers le bas 'deplace_projectile_bas' : réussi\n");
    }
    else{
        printf("test vers le bas 'deplace_projectile_bas' : échoué\n");
    }
	
	if(test_deplace_projectile_droite(&total_test) == true){
        compteur++;
        printf("test vers la droite 'deplace_projectile_droite' : réussi\n");
    }
    else{
        printf("test vers la droite 'deplace_projectile_droite' : échoué\n");
    }
	
	if(test_deplace_projectile_gauche(&total_test) == true){
        compteur++;
        printf("test vers la gauche 'deplace_projectile_gauche' : réussi\n");
    }
    else{
        printf("test vers la gauche 'deplace_projectile_gauche' : échoué\n");
    }

	if(test_declenche_projectile(&total_test) == true){
        compteur++;
        printf("test 'declenche_projectile' : réussi\n");
    }
    else{
        printf("test 'declenche_projectile' : échoué\n");
    }
    /*
    if(test_declenche_lanceur(&total_test)){
        compteur++;
        printf("test de la fonction 'declenche_lanceur' : réussi\n");
    }
    else{
        printf("test de la fonction 'declenche_lanceur' : échoué\n");
    }

	if(test_execute_evenement(&total_test)){
        compteur++;
        printf("test de la fonction 'execute_evenement' : réussi\n");
    }
    else{
        printf("test de la fonction 'execute_evenement' : échoué\n");
    }*/
    

    printf("Résultat totaux des tests : %d / %d\n", compteur, total_test);
}