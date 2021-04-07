#include "../include/niveau.h"


Plateau malloc_Niveau (Coordonnees taille){

    Plateau tmp;
    unsigned int i;

    tmp = (Plateau)malloc(sizeof(Niveau));
    tmp->taille = taille;

    tmp->objets = (Objet**)malloc(sizeof(Objet*) * taille.y * taille.x);
    for(i = 0; i < taille.x; i++){
      tmp->objets[i] = (Objet*)malloc(sizeof(Objet) * taille.y);
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

/**
 * Déplace le joueur selon une direction donnée
 */ 
void deplacer_joueur(Plateau niveau){

    niveau->objets[niveau->coo_perso.x][niveau->coo_perso.y].type = VIDE;
    
    switch(niveau->dir_perso){
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


/**
 * Vérifie si un personnage est en contact avec le bord du terrain et si il se dirige vers celui-ci 
*/
bool perso_en_contact(Plateau plateau){
    return (plateau->coo_perso.x == plateau->taille.x - 1 && plateau->dir_perso == DROITE) || 
            (plateau->coo_perso.x == plateau->taille.x + 1 && plateau->dir_perso == GAUCHE) || 
            (plateau->coo_perso.y == plateau->taille.y -1 && plateau->dir_perso == HAUT) ||
            (plateau->coo_perso.y == plateau->taille.y + 1 && plateau->dir_perso == BAS);
}

void affiche_coordonnee(Coordonnees coordonnee){
    printf("Coordonnée : (%ud, %ud)\n", coordonnee.x, coordonnee.y);
}

bool est_coordonnee_equivalent(Coordonnees first, Coordonnees second){
    return (first.y == second.y) && (first.x == second.x);
}