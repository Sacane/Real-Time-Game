#include "../include/niveau.h"
#include <string.h>

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
	
    unsigned int i, j;

    for(i = 0; i < niveau->taille.x; i++){
        for(j = 0; j < niveau->taille.y; j++){
            if(niveau->objets[i][j].type == PROJECTILE || niveau->objets[i][j].type == LANCEUR)
                free(niveau->objets[i][j].donnee_suppl);
        }
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
    printf("(%u, %u)", coordonnee.x, coordonnee.y);
}

bool est_coordonnee_equivalent(Coordonnees first, Coordonnees second){
    return (first.y == second.y) && (first.x == second.x);
}

bool se_dirige_vers_mur(unsigned int x, unsigned int y, Direction direction, Plateau plateau){
    if((x <= 0 && direction == HAUT) || (x >= plateau->taille.x-1 && direction == BAS)||
    (y <= 0 && direction == GAUCHE) || (y >= plateau->taille.y - 1 && direction == DROITE)){
        return true;
    }
    switch(direction){
        case HAUT:
            if(plateau->objets[x-1][y].type == MUR){
                return true;
            }
            break;
        case BAS:
            if(plateau->objets[x+1][y].type == MUR){
                return true;
            }
            break;
        case GAUCHE:
            if(plateau->objets[x][y-1].type == MUR){
                return true;
            }
            break;
        case DROITE:
            if(plateau->objets[x][y+1].type == MUR){
                return true;
            }
            break;
    }

    return false;
}

bool est_dans_plateau(Direction direction, Plateau plateau, unsigned int x, unsigned int y){
    switch(direction){
        case HAUT:
            if(x <= 0){
                return false;
            }
            break;
        case BAS:
            if(x >= plateau->taille.x-1){
                return false;
            }
            break;
        case GAUCHE:
            if(y <= 0){
                return false;
            }
            break;
        case DROITE:
            if(y >= plateau->taille.y-1){
                return false;
            }
            break;
    }
    return true;
}

void deplace_projectile(Plateau niveau, Coordonnees *coordonnees){
    
    assert(niveau != NULL);
    assert(niveau->objets[coordonnees->x][coordonnees->y].type == PROJECTILE);
    
    Deplacement* deplacement;
    
    deplacement = niveau->objets[coordonnees->x][coordonnees->y].donnee_suppl;
    
    
    niveau->objets[coordonnees->x][coordonnees->y].type = VIDE;
        
    niveau->objets[coordonnees->x][coordonnees->y].donnee_suppl = NULL;
    

    if(se_dirige_vers_mur(coordonnees->x, coordonnees->y, deplacement->direction, niveau)){
        niveau->objets[coordonnees->x][coordonnees->y].type = VIDE;
        niveau->objets[coordonnees->x][coordonnees->y].donnee_suppl = NULL;
        return;
    }
    
    switch((deplacement)->direction){

        case HAUT:
            
            coordonnees->x--; 
            remplis_projectile(&niveau->objets[coordonnees->x][coordonnees->y], deplacement);

            
            break;
        case BAS:
            
            coordonnees->x++; 
            remplis_projectile(&niveau->objets[coordonnees->x][coordonnees->y], deplacement);

            
            break;
        case DROITE:
            
            coordonnees->y++; 
            remplis_projectile(&niveau->objets[coordonnees->x][coordonnees->y], deplacement);

            
            break;
        case GAUCHE:
            
            coordonnees->y--; 
            remplis_projectile(&niveau->objets[coordonnees->x][coordonnees->y], deplacement);

            			
            break;
    }
    niveau->objets[coordonnees->x][coordonnees->y].type = PROJECTILE;
    niveau->objets[coordonnees->x][coordonnees->y].donnee_suppl = deplacement;
}

