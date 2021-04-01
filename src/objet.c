#include "../include/objet.h"


void remplis_projectile(Objet* projectile, Deplacement* deplacement){
  if(projectile->type != LANCEUR){
    printf("Erreur, l'objet n'est pas un lanceur !\n");
    return;
  }
  projectile->donnee_suppl = deplacement;
}

void remplis_lanceur(Objet* lanceur, Generation* gen){
  if(lanceur->type != PROJECTILE){
    printf("Erreur, l'objet n'est pas un lanceur !\n");
    return;
  }
  lanceur->donnee_suppl = gen;

}