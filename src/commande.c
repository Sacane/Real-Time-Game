#include "../include/commande.h"


Plateau niveau0() {

    Plateau niveau;
    Coordonnees taille_niveau;
    taille_niveau.x = 10;
    taille_niveau.y = 5;
    niveau = malloc_Niveau(taille_niveau);
    

    niveau->objets[0][0].type = LANCEUR;
    niveau->objets[5][3].type = LANCEUR;
    niveau->objets[9][4].type = DESTINATION;

    niveau->objets[0][1].type = MUR;
    niveau->objets[1][1].type = MUR;
    niveau->objets[2][1].type = MUR;
    niveau->objets[3][1].type = MUR;
    niveau->objets[4][1].type = MUR;
	niveau->objets[5][1].type = MUR;
    niveau->objets[6][1].type = MUR;
    niveau->objets[8][1].type = MUR;
    niveau->objets[8][2].type = MUR;
    niveau->objets[8][3].type = MUR;
    niveau->objets[8][4].type = MUR;

	/* Conditions donne_supp de Objet en fonction de l'objet donné ? 
     * Oui, en fonction de son typeObjet, si l'objet est un lanceur on lui donnera une génération,
     * Si c'est un projectile on lui donnera un déplacement.

	 * Faut ajouter des conditions alors :o 
    */
	niveau->coo_perso.x = 1;
	niveau->coo_perso.y = 5;
    
    return niveau;
}


void affiche_Niveau (Plateau niveau) {

	unsigned int i, j;
    
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
				switch ((Direction)niveau->objets[i][j].donnee_suppl)
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