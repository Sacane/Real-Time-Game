#include "../include/objet.h"


void remplis_projectile(Objet* obj, Deplacement* deplacement){
    if(obj->type != LANCEUR){
        printf("Erreur, l'objet n'est pas un lanceur !\n");
        return;
    }
    obj->donnee_suppl = deplacement;
}

void remplis_lanceur(Objet* lanceur, Generation* gen){
    if(lanceur->type != PROJECTILE){
      printf("Erreur, l'objet n'est pas un lanceur !\n");
      return;
    }
    lanceur->donnee_suppl = gen;
}

void verif_malloc(void *objet){
    if(NULL == objet){
        fprintf(stderr, "Allocation échoué\n");
        exit(1);
    }
}