#include "../include/objet.h"


void remplis_projectile(Objet* obj, Deplacement* deplacement){

    assert(deplacement != NULL);

    obj->type = PROJECTILE;
    obj->donnee_suppl = deplacement;
}

void remplis_lanceur(Objet* lanceur, Generation* gen){

    assert(gen != NULL);

    lanceur->type = LANCEUR;
    lanceur->donnee_suppl = gen;
}

bool equals_obj(Objet obj1, Objet obj2){
    
    Deplacement* depl = malloc(sizeof(Deplacement));
    Deplacement* depl2 = malloc(sizeof(sizeof(Deplacement)));

    if(obj1.type != obj2.type){
        free(depl);
        free(depl2);
        return false;
    }
    switch(obj1.type){
        case PROJECTILE:
            memcpy(depl, obj1.donnee_suppl, sizeof(Deplacement));
            memcpy(depl2, obj2.donnee_suppl, sizeof(Deplacement));
            if(depl->direction != depl2->direction
            || depl->direction != depl2->direction){
                free(depl);
                free(depl2);
                return false;
            }

            break;
        default:    
            break;
    }
    free(depl);
    free(depl2);
    return true;
}

TypeObjet str_to_obj(char* type){
    if(strcmp(type, "PROJECTILE") == 0){
        return PROJECTILE;
    }
    if(strcmp(type, "LANCEUR") == 0){
        return LANCEUR;
    }
    if(strcmp(type, "PERSONNAGE") == 0){
        return PERSONNAGE;
    }
    if(strcmp(type, "MUR") == 0){
        return MUR;
    }
    return 0;
}



