#include "../include/niveau.h"
#include <string.h>

Plateau malloc_Niveau (Coordonnees taille){

    Plateau tmp;
    unsigned int i;

    tmp = (Plateau)malloc(sizeof(Niveau));
    tmp->taille = taille;
    tmp->est_vivant = true;
    tmp->est_niveau_termine = false;
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
            if(niveau->objets[i][j].donnee_suppl)
                free(niveau->objets[i][j].donnee_suppl);
        }
        free(niveau->objets[i]);
    }
    
    free(niveau->objets);
    free(niveau);
}


void init_niveaux(Plateau niveau, Coordonnees taille){

    unsigned int i, j;
    for(i = 0; i < taille.x; i++){
        for(j = 0; j < taille.y; j++){
            niveau->objets[i][j].type = VIDE;
            niveau->objets[i][j].donnee_suppl = NULL;
        }
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

void deplace_projectile(Plateau niveau, Coordonnees *coordonnees){
    
    assert(niveau != NULL);
    assert(niveau->objets[coordonnees->x][coordonnees->y].type == PROJECTILE);
    
    Deplacement* deplacement;
    
    deplacement = (Deplacement*)malloc(sizeof(Deplacement));

    memcpy(deplacement, niveau->objets[coordonnees->x][coordonnees->y].donnee_suppl, sizeof(Deplacement));

    if(se_dirige_vers_mur(coordonnees->x, coordonnees->y, deplacement->direction, niveau)){
        free(deplacement);
        niveau->objets[coordonnees->x][coordonnees->y].type = VIDE;
        
        return;
    }
    
    switch((deplacement)->direction){

        case HAUT:
        
            niveau->objets[--coordonnees->x][coordonnees->y].type = PROJECTILE;
            niveau->objets[coordonnees->x][coordonnees->y].donnee_suppl = deplacement;
            remplis_projectile(&niveau->objets[coordonnees->x][coordonnees->y], deplacement);
            niveau->objets[coordonnees->x + 1][coordonnees->y].type = VIDE;

            break;
        case BAS:
            
            
            niveau->objets[++coordonnees->x][coordonnees->y].type = PROJECTILE;
            niveau->objets[coordonnees->x][coordonnees->y].donnee_suppl = deplacement;
            remplis_projectile(&niveau->objets[coordonnees->x][coordonnees->y], deplacement);
            
            niveau->objets[coordonnees->x - 1][coordonnees->y].type = VIDE;

            
            break;
        case DROITE:
            
            niveau->objets[coordonnees->x][++coordonnees->y].type = PROJECTILE;
            niveau->objets[coordonnees->x][coordonnees->y].donnee_suppl = deplacement;
            remplis_projectile(&niveau->objets[coordonnees->x][coordonnees->y], deplacement);
            niveau->objets[coordonnees->x][coordonnees->y - 1].type = VIDE;

            break;
        case GAUCHE:
            
            niveau->objets[coordonnees->x][--coordonnees->y].type = PROJECTILE;
            niveau->objets[coordonnees->x][coordonnees->y].donnee_suppl = deplacement;
            remplis_projectile(&niveau->objets[coordonnees->x][coordonnees->y], deplacement);
            niveau->objets[coordonnees->x][coordonnees->y + 1].type = VIDE;
		
            break;
    }
    if(est_coordonnee_equivalent((*coordonnees), niveau->coo_perso)){
        niveau->est_vivant = false;
    }
    
}

/**
 * Déplace le joueur selon une direction donnée
 */ 
void deplace_joueur(Plateau niveau){

    assert(niveau != NULL);
    
    if(se_dirige_vers_mur(niveau->coo_perso.x, niveau->coo_perso.y, niveau->dir_perso, niveau)){
        return;
    }
    niveau->objets[niveau->coo_perso.x][niveau->coo_perso.y].type = VIDE;
    switch(niveau->dir_perso){
        case HAUT:
            niveau->coo_perso.x -= 1;
            break;
        case BAS:
            niveau->coo_perso.x += 1;
            break; 
        case DROITE:
            niveau->coo_perso.y += 1;
            break;
        case GAUCHE:
            niveau->coo_perso.y -= 1;
            break;
    }
	niveau->objets[niveau->coo_perso.x][niveau->coo_perso.y].type = PERSONNAGE;
    niveau->depl_perso_autorise = false;
    niveau->moment_depl_perso = maintenant() + niveau->allure_perso;
}

void verifie_mouvement_personnage(Plateau niveau){

	assert(NULL != niveau);

	if(maintenant() >= niveau->moment_depl_perso){
		niveau->depl_perso_autorise = true;
	}
}

bool check_level_reached(Plateau niveau){
    assert(niveau != NULL);
    
    return est_coordonnee_equivalent(niveau->coo_perso, niveau->coo_destination);
}

void affiche_Niveau (Plateau niveau) {

	unsigned int i, j;
    Deplacement *dep;
	for(i = 0; i < niveau->taille.x ; i++) {
		for(j = 0; j < niveau->taille.y; j++) {

			switch (niveau->objets[i][j].type)
			{
			case VIDE: 
				printf(".");
				break;
			case LANCEUR: 
				printf("O");
				break;
			case MUR: 
				printf("#");
				break;
			
			case PROJECTILE: 
                /* J'ai modifié ici, tu avais raison au début mais le 
                * castage se fait au début, j't'expliquerai le castage 
                * en vocal 
                */
                dep = niveau->objets[i][j].donnee_suppl;
				switch (dep->direction)
				{
				case HAUT: 
					printf("^");
					break;
				case GAUCHE:
					printf("<");
					break;
				case BAS: 
					printf("v");
					break;
				case DROITE: 
					printf(">");
					break;
				}
				break;

			case PERSONNAGE:
				printf("P");
				break;
			case DESTINATION:
				printf("D");
				break;
			default:
				printf(".");
				break;
			}
		}
		printf("\n");
	}
}
