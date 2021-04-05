#include "../include/test.h"

/* TODO : Finir le test d'ajout d'évènement */

static bool test_evenement_pret(){
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
                return false;
            }
        }
        if(eval == 1000){
            if(un_evenement_est_pret(test_tas) == false){
                return false;
            }
        }
        break;
    }
    return true;
}

static bool test_ajoute_evenement_test() {
    Arbre test_arbre = malloc_Tas(INITIAL_SIZE);
    Evenement event1, event2, event3, event4, event5;
    
    event1.moment = 300;
    event2.moment = 1000;
    event3.moment = 500;
    event4.moment = 800;
    event5.moment = 200;

    ajoute_evenement(test_arbre, event1);

    if(test_arbre->valeurs[0].moment != 300){
        
        return false;
    }
    
    ajoute_evenement(test_arbre, event2);
    ajoute_evenement(test_arbre, event3);

    if(estTas(test_arbre)){
        printf("%lu\n", test_arbre->valeurs[1].moment);
        return false;
    }
    ajoute_evenement(test_arbre, event3);
    ajoute_evenement(test_arbre, event4);
    ajoute_evenement(test_arbre, event5);

    if(estTas(test_arbre) == false){
        return false;
    }


    free_Tas(test_arbre);
    return true;
}

void main_test(){
    if(test_evenement_pret() == true){
        printf("Le test de  la fonction un_evenement_est_pret est passé\n");
    }
    else{
        printf("Le test de un_evenement_est_pret n'est pas passé \n");
    }

    if(test_ajoute_evenement_test() == true){
        printf("le test de la fonction test_ajoute_evenement_test est passé\n");
    }
    else{
        printf("le test de la fonction test_ajoute_evenement_test n'est pas passé\n");
    }
}