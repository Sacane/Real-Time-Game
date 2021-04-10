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
    
    event1.moment = 300;
    event2.moment = 2050;
    event3.moment = 1002;
    event4.moment = 293;
    event5.moment = 450;
    
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

    /* Test si le tas est toujours un tas */
	if(estTas(arbre) == false){
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
static bool test_deplace_projectile(int *total_test){
    *total_test += 1;
	Plateau niveau = niveau0();
	Objet objet; 
    Deplacement* deplacement;
    deplacement = (Deplacement*)malloc(sizeof(deplacement));
	Coordonnees coordonnees;

	deplacement->direction = HAUT;
	coordonnees.x = 3;
    coordonnees.y = 2;
	objet.type = PROJECTILE; 
	objet.donnee_suppl = deplacement;
    niveau->objets[coordonnees.x][coordonnees.y] = objet;
	
	deplace_projectile(objet, niveau, coordonnees);
    
	if(niveau->objets[3][2].type != VIDE){
        printf("Projectile non-déplacé !");
		return false;
	}

	if(niveau->objets[2][2].type != PROJECTILE){
        printf("Projectile pas au bon endroit !\n");
		return false;
	}

    Coordonnees new_coord;
    new_coord.x = 2;
    new_coord.y = 2;

    deplace_projectile(objet, niveau, new_coord);

    if(niveau->objets[1][2].type != MUR){
        printf("Le mur a été modifié par un projectile !\n");
        return false;
    }

	free_Niveau(niveau);
	free(deplacement);
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

	if(test_deplace_projectile(&total_test) == true){
        compteur++;
        printf("test 'deplace_projectile' : réussi\n");
    }
    else{
        printf("test 'deplace_projectile' : échoué\n");
    }
    printf("Résultat totaux des tests : %d / %d\n", compteur, total_test);

}


    