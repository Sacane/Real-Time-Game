#include "../include/objet.h"


void remplis_projectile(Objet* lanceur, Deplacement* deplacement){
    assert(lanceur != NULL);
    assert(lanceur->type == LANCEUR);
    assert(deplacement != NULL);

    lanceur->donnee_suppl = deplacement;
}

void remplis_lanceur(Objet* projectile, Generation* gen){
    assert(projectile != NULL);
    assert(projectile->type == PROJECTILE);
    assert(gen != NULL);
    projectile->donnee_suppl = gen;
}

void verif_malloc(void *objet){
    if(NULL == objet){
        fprintf(stderr, "Allocation échoué\n");
        exit(1);
    }
}