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


