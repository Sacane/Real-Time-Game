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

