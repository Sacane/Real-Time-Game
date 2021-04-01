#include "../include/niveau.h"


Plateau malloc_Niveau (Coordonnees taille){

    Plateau tmp;
    unsigned int i;

    tmp = (Plateau)malloc(sizeof(Niveau));
    tmp->taille = taille;

    tmp->objets = malloc(sizeof(Objet*)*taille.x + sizeof(Objet) *taille.y * taille.x);
    for(i = 0; i < taille.x; i++){
      tmp->objets[i] = (Objet*)malloc(sizeof(Objet)*taille.x + taille.x * taille.y);
    }
    return tmp;
}


void free_Niveau (Plateau niveau){
    unsigned int i;

  
    for(i = 0; i < niveau->taille.x; i++){
        free(niveau->objets[i]);
    }
    free(niveau->objets);
    free(niveau);


}

void deplacer_joueur(Plateau niveau, Direction direction){

    niveau->objets[niveau->coo_perso.x][niveau->coo_perso.y].type = VIDE;
    
    switch(direction){
        case HAUT:
            niveau->coo_perso.y += 1;
            break;
        case BAS:
            niveau->coo_perso.y -= 1;
            break;
        case DROITE:
            niveau->coo_perso.x += 1;
            break;
        case GAUCHE:
            niveau->coo_perso.x -= 1;
            break;
            
    }
}