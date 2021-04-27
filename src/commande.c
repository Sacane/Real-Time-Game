#include "../include/commande.h"
/* Note : 
 * Y pour aller de gauche à droite
 * X pour aller de haut en bas
 * plateau[X][Y]
*/

void init_niveaux(Plateau niveau, Coordonnees taille){

    unsigned int i, j;
    niveau->dir_perso = BAS;
    for(i = 0; i < taille.x; i++){
        for(j = 0; j < taille.y; j++){
            niveau->objets[i][j].type = VIDE;
            niveau->objets[i][j].donnee_suppl = NULL;
        }
    }
}

Plateau niveau0() {

    Plateau niveau;
    Coordonnees taille_niveau;
    taille_niveau.x = 5;
    taille_niveau.y = 10;
    niveau = malloc_Niveau(taille_niveau);
    init_niveaux(niveau, taille_niveau);

    Generation* gen;
    Generation* gen2;
    gen2 = (Generation*)malloc(sizeof(Generation));
    gen = (Generation*)malloc(sizeof(Generation));
    gen2->allure_proj = 300;
    gen2->intervalle = 1000;
    gen->allure_proj = 300;
    gen->intervalle = 1000;

    niveau->objets[0][0].type = LANCEUR;
    niveau->objets[0][0].donnee_suppl = gen;
    niveau->objets[3][5].type = LANCEUR;
    niveau->objets[3][5].donnee_suppl = gen2;
    niveau->objets[4][9].type = DESTINATION;
	
    /* init mur */
    niveau->objets[1][0].type = MUR;
    niveau->objets[1][1].type = MUR;
    niveau->objets[1][2].type = MUR;
    niveau->objets[1][3].type = MUR;
    niveau->objets[1][4].type = MUR;
    niveau->objets[1][5].type = MUR;
    niveau->objets[1][6].type = MUR;
    niveau->objets[1][8].type = MUR;
    niveau->objets[2][8].type = MUR;
    niveau->objets[3][8].type = MUR;
    niveau->objets[4][8].type = MUR;


    niveau->coo_perso.x = 4;
    niveau->coo_perso.y = 0;
    niveau->objets[niveau->coo_perso.x][niveau->coo_perso.y].type = PERSONNAGE;


    return niveau;
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