#include "../include/objet.h"


void remplis_projectile(Objet* lanceur, Deplacement* deplacement){
    assert(lanceur->type == LANCEUR);
    lanceur->donnee_suppl = deplacement;
}

void remplis_lanceur(Objet* projectile, Generation* gen){
    assert(projectile->type == PROJECTILE);
    projectile->donnee_suppl = gen;
}

void verif_malloc(void *objet){
    if(NULL == objet){
        fprintf(stderr, "Allocation échoué\n");
        exit(1);
    }
}